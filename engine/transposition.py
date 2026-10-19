"""Transposition table for alpha-beta search (keyed by Zobrist hash)."""

from __future__ import annotations

from dataclasses import dataclass

from rules.move import Move

# Bound flags stored with each TT entry (standard alpha-beta semantics).
BOUND_EXACT = 0
BOUND_LOWER = 1  # fail-high: true score >= stored score
BOUND_UPPER = 2  # fail-low: true score <= stored score

# Power-of-two bucket count; index = hash & (TT_SIZE - 1).
TT_SIZE = 1 << 20


@dataclass(slots=True)
class _TTEntry:
    key: int = 0
    depth: int = -1
    score: int = 0
    bound: int = BOUND_EXACT
    move_data: int = 0
    generation: int = -1


_table: list[_TTEntry] = [_TTEntry() for _ in range(TT_SIZE)]
_search_generation: int = 0


def begin_search() -> None:
    """Call once per root search (e.g. each find_best_move)."""
    global _search_generation
    _search_generation += 1


def _index(key: int) -> int:
    return key & (TT_SIZE - 1)


def probe(
    key: int,
    depth: int,
    alpha: int,
    beta: int,
) -> tuple[int | None, Move | None]:
    """
    Look up ``key``. Returns (score, best_move) if the entry allows a cutoff or
    exact return; otherwise (None, hash_move) where hash_move may still be used
    for move ordering.
    """
    entry = _table[_index(key)]
    hash_move = Move(entry.move_data) if entry.key == key and entry.move_data else None
    if entry.key != key or entry.depth < depth:
        return None, hash_move

    score = entry.score
    if entry.bound == BOUND_EXACT:
        return score, hash_move
    if entry.bound == BOUND_LOWER and score >= beta:
        return score, hash_move
    if entry.bound == BOUND_UPPER and score <= alpha:
        return score, hash_move
    return None, hash_move


def store(
    key: int,
    depth: int,
    score: int,
    bound: int,
    move: Move | None,
) -> None:
    """Replace bucket if empty, different key, or this result is deeper."""
    idx = _index(key)
    entry = _table[idx]
    move_data = move.data if move else 0
    if (
        entry.key != key
        or depth >= entry.depth
        or entry.generation != _search_generation
    ):
        entry.key = key
        entry.depth = depth
        entry.score = score
        entry.bound = bound
        entry.move_data = move_data
        entry.generation = _search_generation
