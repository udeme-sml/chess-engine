from __future__ import annotations

from math import inf

from rules.attacks import in_check
from rules.move import Move
from rules.movegen import generate_legal_moves
from rules.position import Position

from engine.eval import evaluate

MATE_SCORE = 30000


def negamax(position: Position, depth: int, alpha: int, beta: int) -> int:
    moves = generate_legal_moves(position)
    if not moves:
        return -MATE_SCORE if in_check(position) else 0
    if depth == 0:
        return evaluate(position)

    best = -float('inf')
    for move in moves:
        position.make_move(move)
        score = -negamax(position, depth - 1, -beta, -alpha)
        position.unmake_move()
        best = max(best, score)

        if score > alpha:
            alpha = score
        if alpha >= beta:
            break
    return best


def find_best_move(
    position: Position,
    depth: int,
    alpha: float = -inf,
    beta: float = inf,
) -> Move:
    moves = generate_legal_moves(position)
    if not moves:
        return Move(0)
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
