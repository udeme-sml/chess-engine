"""
Public engine API — UI and UCI talk to the engine only through this module.

Replace the stub implementations in ``engine/stub.py`` with your search and eval.
"""

from __future__ import annotations

from rules.move import Move
from rules.position import Position

from engine import eval as eval
from engine.search import find_best_move as _find_best_move

def find_best_move(position: Position, time_limit_ms: int, max_depth: int) -> Move:
    """
    Choose a move for ``position`` (side to move is read from the position).

    ``time_limit_ms`` and ``max_depth`` are hints for iterative deepening / time
    management — the stub ignores them.
    """
    _ = time_limit_ms
    return _find_best_move(position, max_depth)


def evaluate(position: Position) -> int:
    """Centipawns from the side-to-move perspective."""
    return eval.evaluate(position)
