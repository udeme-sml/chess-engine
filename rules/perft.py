"""Perft (move tree counting) for correctness testing."""

from __future__ import annotations

from rules.move import move_to_uci
from rules.movegen import generate_legal_moves
from rules.position import Position


def perft(pos: Position, depth: int) -> int:
    if depth == 0:
        return 1
    moves = generate_legal_moves(pos)
    if depth == 1:
        return len(moves)
    total = 0
    for m in moves:
        pos.make_move(m)
        total += perft(pos, depth - 1)
        pos.unmake_move()
    return total


def perft_divide(pos: Position, depth: int) -> tuple[int, list[tuple[str, int]]]:
    """Return total nodes and per-root-move counts (UCI names)."""
    moves = generate_legal_moves(pos)
    lines: list[tuple[str, int]] = []
    total = 0
    for m in moves:
        pos.make_move(m)
        n = perft(pos, depth - 1)
        pos.unmake_move()
        lines.append((move_to_uci(m), n))
        total += n
    return total, lines
