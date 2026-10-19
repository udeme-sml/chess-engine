from __future__ import annotations

from math import inf

from rules.attacks import in_check
from rules.constants import MoveFlag, PieceType, piece_type
from rules.move import Move
from rules.movegen import generate_legal_moves
from rules.position import Position

from engine.eval import evaluate
from engine import transposition as tt

MATE_SCORE = 30000

# Centipawn values for capture ordering (MVV-LVA).
_PIECE_VALUE = {
    PieceType.PAWN: 100,
    PieceType.KNIGHT: 320,
    PieceType.BISHOP: 330,
    PieceType.ROOK: 500,
    PieceType.QUEEN: 900,
    PieceType.KING: 0,
}


def _capture_order_score(position: Position, move: Move) -> int:
    """Higher = search earlier. Captures only."""
    board = position.board
    attacker = board[move.from_sq]
    if move.flag == MoveFlag.EN_PASSANT:
        victim_val = _PIECE_VALUE[PieceType.PAWN]
    else:
        victim = board[move.to_sq]
        victim_val = _PIECE_VALUE.get(piece_type(victim), 0)
    attacker_val = _PIECE_VALUE.get(piece_type(attacker), 0)
    return victim_val * 16 - attacker_val


def _order_moves(position: Position, moves: list[Move], hash_move: Move | None) -> list[Move]:
    """Hash move first, then captures (MVV-LVA), then quiets (stable order)."""
    scored: list[tuple[int, int, Move]] = []
    for i, move in enumerate(moves):
        if hash_move is not None and move.data == hash_move.data:
            score = 2_000_000
        elif move.is_capture():
            score = 1_000_000 + _capture_order_score(position, move)
        else:
            score = 0
        scored.append((score, i, move))
    scored.sort(key=lambda t: (-t[0], t[1]))
    return [m for _, _, m in scored]


def negamax(position: Position, depth: int, alpha: int, beta: int) -> int:
    alpha_orig = alpha
    key = position.hash

    # --- Transposition table probe (may return a score and/or a hash move) ---
    tt_score, hash_move = tt.probe(key, depth, alpha, beta)
    if tt_score is not None:
        return tt_score

    moves = generate_legal_moves(position)
    if not moves:
        return -MATE_SCORE if in_check(position) else 0
    if depth == 0:
        return evaluate(position)

    moves = _order_moves(position, moves, hash_move)

    best_score = -inf
    best_move: Move | None = None
    for move in moves:
        position.make_move(move)
        score = -negamax(position, depth - 1, -beta, -alpha)
        position.unmake_move()

        if score > best_score:
            best_score = score
            best_move = move

        if score > alpha:
            alpha = score
        if alpha >= beta:
            break

    # --- Store result so transpositions and move ordering can reuse it ---
    if best_score <= alpha_orig:
        bound = tt.BOUND_UPPER
    elif best_score >= beta:
        bound = tt.BOUND_LOWER
    else:
        bound = tt.BOUND_EXACT
    tt.store(key, depth, int(best_score), bound, best_move)

    return int(best_score)


def find_best_move(
    position: Position,
    depth: int,
    alpha: float = -inf,
    beta: float = inf,
) -> Move:
    tt.begin_search()
    moves = generate_legal_moves(position)
    if not moves:
        return Move(0)

    # Wide window at root: we only want a hash move for ordering, not a TT cutoff.
    _, hash_move = tt.probe(position.hash, depth, -MATE_SCORE * 2, MATE_SCORE * 2)
    moves = _order_moves(position, moves, hash_move)

    best_move = moves[0]
    best_score = -inf
    for move in moves:
        position.make_move(move)
        score = -negamax(position, depth - 1, -beta, -alpha)
        position.unmake_move()
        if score > best_score:
            best_score = score
            best_move = move
        if score > alpha:
            alpha = score
    return best_move
