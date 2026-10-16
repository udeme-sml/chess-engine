"""
Stub engine: random legal move, zero evaluation.

================================================================================
  REPLACE THIS MODULE with your search + evaluation implementation.
  Keep the same function signatures so ``engine.api`` can re-export them.
================================================================================
"""

from __future__ import annotations

import random

from rules.move import Move
from rules.movegen import generate_legal_moves
from rules.position import Position


def find_best_move(position: Position, time_limit_ms: int, max_depth: int) -> Move:
    _ = time_limit_ms, max_depth
    moves = generate_legal_moves(position)
    if not moves:
        return Move(0)
    return random.choice(moves)


def evaluate(position: Position) -> int:
    _ = position
    return 0
