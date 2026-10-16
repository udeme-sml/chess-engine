"""Zobrist hash must match full recomputation after every make/unmake."""

import random

from rules import zobrist
from rules.movegen import generate_legal_moves
from rules.position import Position

START = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


def test_hash_matches_scratch_at_start() -> None:
    pos = Position.from_fen(START)
    assert pos.hash == zobrist.compute_hash(pos.board, pos.stm, pos.castling, pos.ep_sq)


def test_hash_after_random_plies() -> None:
    random.seed(123)
    pos = Position.from_fen(START)
    for _ in range(100):
        assert pos.hash == zobrist.compute_hash(pos.board, pos.stm, pos.castling, pos.ep_sq)
        moves = generate_legal_moves(pos)
        if not moves:
            break
        pos.make_move(random.choice(moves))
    for _ in range(100):
        if not pos._undo_stack:
            break
        pos.unmake_move()
        assert pos.hash == zobrist.compute_hash(pos.board, pos.stm, pos.castling, pos.ep_sq)
