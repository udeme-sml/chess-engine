# Chess Engine Implementation Reference

This document describes the **current** codebase under `chess-engine`: how the board and moves are represented, what APIs exist in `rules/`, and how you plug in **search** and **evaluation** via `engine/`.

---

## 1. Project layout

| Package / path | Role |
|----------------|------|
| **`rules/`** | Rules layer: board, FEN, moves, movegen, attacks, Zobrist, perft, game outcome. **No search or eval.** |
| **`engine/`** | Engine layer: public API + UCI. **Search/eval are stubs** (`engine/stub.py`). |
| **`ui/`** | Web UI and `GameSession`; calls `engine.api.find_best_move`. |
| **`tests/`** | Perft, make/unmake, hash, rules tests. |
| **`scripts/engine_match.py`** | Engine vs engine helper. |

Python **3.11+**, no runtime dependencies (pytest optional).

**Design split:** UI and UCI must only use `engine.api` for playing moves. Your search should live under `engine/` (e.g. `engine/search.py`, `engine/eval.py`) and be wired from `engine/api.py`.

---

## 2. Board representation: **64-square array, not bitboards**

The board is **not** a bitboard engine today.

- **`Position.board`**: `list[int]` of length **64**.
- Index **0 = a1** … **63 = h8** (`rules/constants.py`, `rules/square.py`).
- **Rank 0** in the array is **white’s back rank** (FEN rank 1); **rank 7** is black’s back rank (FEN rank 8).
- **Empty square** = `0`.
- **Occupied square** = packed **4-bit** piece id (not a separate object).

```text
file:  0 1 2 3 4 5 6 7
       a b c d e f g h
rank 7: 56..............63  (8th rank)
...
rank 0:  0............... 7  (1st rank)
```

`constants.py` defines `NOT_A_FILE = 0xFEFEFEFEFEFEFEFE` as a comment-style nod to bitboards; **bounds are checked with arithmetic** (`on_board`, file/rank checks in movegen), not with bit masks.

---

## 3. Piece encoding

Pieces are **integers**, not enums on the board.

| Concept | API |
|---------|-----|
| Pack color + type | `make_piece(color: Color, piece_type: PieceType) -> int` |
| Decode | `piece_color(piece) -> Color`, `piece_type(piece) -> PieceType` |

**Layout:** color in **bit 3** (`0` = white, `1` = black), type in **bits 0–2** (`PieceType` 1–6).

**Constants:** `W_PAWN`, `B_KING`, etc. in `rules/constants.py`.

**`PieceType`:** `EMPTY=0`, `PAWN=1` … `KING=6` (EMPTY is only used as type; board empty is `0`).

**`Color`:** `WHITE=0`, `BLACK=1`.

---

## 4. `Position`: mutable game state

**Class:** `rules.position.Position` (not a dataclass; uses `__slots__`).

### Fields

| Field | Type | Meaning |
|-------|------|---------|
| `board` | `list[int]` | 64 squares |
| `stm` | `Color` | Side to move |
| `castling` | `CastlingRights` (`IntFlag`) | `WHITE_KING`, `WHITE_QUEEN`, `BLACK_KING`, `BLACK_QUEEN` |
| `ep_sq` | `int` | En passant target square, or **`-1`** |
| `halfmove` | `int` | Halfmove clock (50-move rule uses `>= 100`) |
| `fullmove` | `int` | Fullmove number |
| `hash` | `int` | Incremental Zobrist hash |
| `hash_history` | `list[int]` | Hash after each ply (includes start); used for **threefold** |
| `king_sq` | `list[int]` | `[white_king_sq, black_king_sq]` — updated on king moves / castling |
| `_undo_stack` | `list[UndoInfo]` | Private; drives `unmake_move` |

### Construction

- **`Position.from_fen(fen: str) -> Position`**: parses FEN, refreshes king squares, sets `hash`, initializes `hash_history = [hash]`.
- **`pos.fen() -> str`**: full FEN string.

### Piece / hash helpers (internal but useful to know)

- `piece_at(sq)` → `board[sq]`
- `_remove_piece` / `_put_piece` / `_move_piece` — update board **and** XOR `hash` via Zobrist

### Make / unmake (core for search)

- **`make_move(move: Move) -> None`**
  - Handles quiet, capture, double pawn, en passant, castling K/Q, promotion (4 promo types).
  - Updates castling rights (king move, rook corner captures/moves).
  - Updates `ep_sq` (only on double pawn).
  - Toggles `stm`, XORs side key, updates `halfmove` / `fullmove`.
  - Pushes `UndoInfo` and appends to `hash_history`.

- **`unmake_move() -> None`**
  - Pops undo stack; restores board, hash, castling, ep, clocks, kings.
  - **Does not** recompute hash from scratch — restores saved `hash`.

**`UndoInfo`** (dataclass): `move`, `captured`, `captured_sq`, `castling`, `ep_sq`, `halfmove`, `hash`, `fullmove`, `king_sq_white`, `king_sq_black`.

**Castling constants** (white / black index 0 / 1):

- K-side rook from/to: `(7, 63)` → rook to `(5, 61)`; king to g1/g8 (sq 6 / 62).
- Q-side: rook `(0, 56)` → rook to `(3, 59)`; king to c1/c8 (sq 2 / 58).

**Search pattern:** copy root position if you need parallelism; on the search tree use **`make_move` / `unmake_move`** only (see `rules/perft.py`).

---

## 5. `Move`: packed 32-bit move

**Class:** `rules.move.Move` — frozen dataclass wrapping one `int` `data`.

| Bits | Field |
|------|--------|
| 0–5 | `from_sq` |
| 6–11 | `to_sq` |
| 12–14 | promotion id (`PROMO_*`) |
| 15–17 | `MoveFlag` |

**Factory:** `Move.pack(from_sq, to_sq, flag=MoveFlag.QUIET, promo=PROMO_NONE)`.

**`MoveFlag`:** `QUIET`, `CAPTURE`, `DOUBLE_PAWN`, `EN_PASSANT`, `CASTLE_K`, `CASTLE_Q`, `PROMOTION`.

**Helpers:**

- `is_capture()` — capture, en passant, or promotion with promo set.
- `is_promotion()`
- `MOVE_NULL` / `Move(0)` — null move (UCI `0000`); stub returns this if no legal moves.

**UCI:** `move_to_uci(m)`, `move_from_uci(uci, legal_moves=None)`.

If `legal_moves` is passed, UCI is matched against that list (needed to disambiguate flag/promo). **Always pass legal moves** when parsing in-game moves.

---

## 6. Square utilities (`rules/square.py`)

- `file_of(sq) = sq & 7`, `rank_of(sq) = sq >> 3`
- `square_name(sq)`, `parse_square("e4")`
- `on_board(sq)` → `0 <= sq < 64`
- `sq_up(sq, color_white)` — one step “forward” for that color
- `distance(sq1, sq2)` — Chebyshev distance

**Ray deltas** (used in movegen/attacks): defined in `constants.py` as `DIRS_*` but movegen mostly inlines deltas.

---

## 7. Move generation (`rules/movegen.py`)

### Functions

| Function | Behavior |
|----------|----------|
| `generate_pseudo_legal_moves(pos, captures_only=False)` | All pseudo-legal moves; uses module-level **`_MOVE_BUF`** (cleared each call). **Not thread-safe.** |
| `generate_legal_moves(pos)` | Pseudo-legal → filter by make/unmake + not leaving own king in check |
| `generate_captures(pos)` | Captures + promotions only; legal-filtered — intended for **quiescence** |
| `generate_legal_moves_copy(pos)` | Fresh `list` if you must store moves across `make_move` |

### Legal filtering

```text
for m in pseudo:
    pos.make_move(m)
    if not mover_in_check_after(pos):  # side that moved is NOT in check
        legal.append(m)
    pos.unmake_move()
```

`mover_in_check_after` = after the move, the **previous** side to move (the mover) must not be in check (detects moving into check / illegal king moves).

### Castling

Generated only if not in check, rights set, squares empty, rook on corner, and **king path squares not attacked** (`sq_attacked_by`).

### Promotions

Four moves per (from, to): queen, rook, bishop, knight; flag always `MoveFlag.PROMOTION`.

---

## 8. Attacks and check (`rules/attacks.py`)

- **`sq_attacked_by(pos, sq, by_color) -> bool`**  
  Full board scan style: pawn attacks, knights, king, bishop/queen rays, rook/queen rays. File-wrap guards on rays.

- **`in_check(pos, color=None) -> bool`**  
  Default `color = stm`. Uses **`pos.king_sq[int(color)]`**, not a scan.

- **`mover_in_check_after(pos) -> bool`**  
  After `make_move`, checks whether the **mover** is in check (STM has flipped).

There is **no** attack bitboard, pin detection, or check evasion generator yet — legality is “try move + see if king attacked.”

---

## 9. Zobrist hashing (`rules/zobrist.py`)

- Fixed seed `Random(0xC0FFEE00)` for reproducible tests.
- `PIECE_KEYS[piece][sq]`, `SIDE_KEY`, `CASTLE_KEYS[rights]`, `EP_FILE_KEYS[file]`.
- **`compute_hash(board, stm, castling, ep_sq)`** — full recompute (tests).
- Position maintains **`hash` incrementally** on make/unmake.

**EP in hash:** only the **file** of `ep_sq` (if `ep_sq >= 0`), not the full square.

**Transposition table:** not implemented — you can key TT on `pos.hash` (mind collision handling if you add one).

---

## 10. Game outcome (`rules/game.py`)

**`GameResult`:** `ONGOING`, `CHECKMATE`, `STALEMATE`, `THREEFOLD`, `FIFTY_MOVE`, `INSUFFICIENT_MATERIAL`.

**`game_result(pos)`** order:

1. `count_repetition(pos) >= 3` (counts current hash in `hash_history`)
2. `halfmove >= 100`
3. `has_insufficient_material(pos)` (K/K, K+B/K, K+N/K, K+B vs K+B same-color bishops)
4. No legal moves → checkmate if in check else stalemate
5. Else ongoing

**`side_in_check(pos)`** → `in_check(pos)`.

For search: at nodes with no legal moves, combine with `in_check` for mate vs stalemate scores.

---

## 11. FEN (`rules/fen.py`)

- **`parse_fen(fen)`** → `(board, stm, castling, ep_sq, halfmove, fullmove)`
- **`to_fen(...)`**, **`board_to_fen_piece_placement(board)`**

---

## 12. Perft (`rules/perft.py`)

- **`perft(pos, depth)`** — depth 0 = 1 node; depth 1 returns move count.
- **`perft_divide(pos, depth)`** → `(total, [(uci, nodes), ...])`

Used to validate movegen (`tests/test_perft.py` — standard positions through depth 4–5).

---

## 13. Public `rules` exports (`rules/__init__.py`)

```python
GameResult, game_result, Move, Position,
generate_captures, generate_legal_moves,
move_from_uci, move_to_uci, perft, perft_divide
```

Lower-level modules (`attacks`, `zobrist`, `fen`, `constants`) are imported by path when needed.

---

## 14. Engine integration (where **you** implement search/eval)

### Public API (`engine/api.py`)

```python
def find_best_move(position: Position, time_limit_ms: int, max_depth: int) -> Move
def evaluate(position: Position) -> int
```

- **`evaluate`**: centipawns from **side to move’s** perspective (positive = good for STM).
- **`find_best_move`**: must return a **legal** `Move`, or `Move(0)` if none.

**Current implementation:** `engine/stub.py` — random legal move, eval `0`.

**Wiring:** replace imports in `api.py` to point at your modules; keep signatures.

### UCI (`engine/uci.py`)

- Reads `position` / `go depth` / `go movetime`.
- Calls `find_best_move(self.position, movetime, depth)`.
- Applies moves with `generate_legal_moves` + `move_from_uci(uci, legal)`.
- **`stop` sets a flag but is not passed into search yet** — you’ll need shared stop flag / threading for real time management.

### UI (`ui/game_session.py`)

- Engine thread: `Position.from_fen(self.position.fen())` copy, then `find_best_move(pos_copy, 2000, 8)`.

---

## 15. Recommended search/eval workflow

### Tree search

1. Root: `Position` from caller (do not assume thread-safe movegen buffer).
2. Loop: `moves = generate_legal_moves(pos)` or `generate_captures` in QS.
3. `pos.make_move(m)` → recurse → `pos.unmake_move()`.
4. Terminal: `game_result`, or no moves + `in_check` for mate/stalemate.

### Evaluation

- Read `pos.board`, `pos.stm`, `pos.king_sq`, optionally `pos.castling` / `pos.ep_sq`.
- Return score **for `pos.stm`** to match API contract.
- Material-only eval is enough to beat the random stub.

### Quiescence

- Use **`generate_captures(pos)`** (already legal, includes promotions).

### Repetition / draws in search

- `pos.hash` and `pos.hash_history` exist; search typically tracks hashes along the current path (not the full game history list unless at root).
- `halfmove` on position for 50-move.

### What is **not** in the codebase yet

- Bitboards, magic bitboards, attack tables
- Transposition table, killer/history, MVV-LVA (you sort moves yourself)
- Null move, LMR, aspiration windows
- Incremental eval / phased material+PSQT
- SEE, pin-aware movegen
- Parallel search
- UCI `stop` wired to search

---

## 16. Thread safety and performance notes

- **`generate_pseudo_legal_moves`** reuses `_MOVE_BUF`; concurrent calls race. Options: use `generate_legal_moves_copy`, generate on one thread, or add a per-thread buffer.
- **Legal filtering** does one make/unmake per pseudo move — simple, correct, slower than dedicated check evasion.
- **King location** is cached — use `pos.king_sq` in eval/attacks instead of scanning for kings.
- **Copying position:** no `Position.clone()`; UI uses **`Position.from_fen(pos.fen())`** (allocates new board + history). Search should prefer make/unmake.

---

## 17. Move / flag quick reference for `make_move`

| User-visible idea | Typical `MoveFlag` | Notes |
|-------------------|-------------------|--------|
| Quiet | `QUIET` | |
| Capture | `CAPTURE` | |
| Double push | `DOUBLE_PAWN` | sets `ep_sq` to skipped square |
| En passant | `EN_PASSANT` | captured pawn square stored in undo |
| Castle short | `CASTLE_K` | king `to_sq` g1/g8 |
| Castle long | `CASTLE_Q` | king `to_sq` c1/c8 |
| Promote | `PROMOTION` + `promo` | `PROMO_QUEEN` etc. |

---

## 18. Sanity checks while developing

```bash
pytest tests/test_perft.py tests/test_make_unmake.py tests/test_hash.py tests/test_rules.py
```

If perft passes, movegen + make/unmake + hash are consistent with reference counts.

---

## 19. Minimal alpha-beta sketch (fits this API)

```python
from rules.attacks import in_check
from rules.movegen import generate_legal_moves
from rules.position import Position

MATE_SCORE = 30_000

def alphabeta(pos: Position, depth: int, alpha: int, beta: int) -> int:
    if depth == 0:
        return evaluate(pos)  # your engine.eval

    moves = generate_legal_moves(pos)
    if not moves:
        return -MATE_SCORE if in_check(pos) else 0

    for m in moves:
        pos.make_move(m)
        score = -alphabeta(pos, depth - 1, -beta, -alpha)
        pos.unmake_move()
        alpha = max(alpha, score)
        if alpha >= beta:
            break
    return alpha
```

Wire `evaluate` and move ordering into `engine/stub.py` (or new modules) and export through `engine/api.py`.

---

## Summary

| Question | Answer |
|----------|--------|
| Board type? | **`list[int]` length 64**, square index a1=0 |
| Bitboards? | **No** (only an unused mask constant) |
| Position updates? | **`make_move` / `unmake_move`** + Zobrist |
| Moves? | **Packed `Move.data`**, 32-bit |
| Legal moves? | **`generate_legal_moves`** |
| Captures for QS? | **`generate_captures`** |
| Position hash? | **`pos.hash`** (Zobrist) |
| Engine entrypoint? | **`engine.api.find_best_move`**, **`evaluate`** |
| Eval sign? | **Positive = good for side to move** |
