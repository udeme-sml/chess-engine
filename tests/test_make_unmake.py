"""Long random make/unmake must restore exact state."""

import random

from rules import zobrist
from rules.movegen import generate_legal_moves
from rules.position import Position

START = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


def test_make_unmake_round_trip() -> None:
    random.seed(99)
    pos = Position.from_fen(START)
    snapshot = (
        pos.fen(),
        pos.hash,
        pos.castling,
        pos.ep_sq,
        pos.halfmove,
        pos.fullmove,
        pos.hash_history.copy(),
        pos.king_sq.copy(),
        pos.board.copy(),
    )
    depth = 0
    for _ in range(300):
        moves = generate_legal_moves(pos)
        if not moves:
            break
        pos.make_move(random.choice(moves))
        depth += 1
    for _ in range(depth):
        pos.unmake_move()
    assert pos.fen() == snapshot[0]
    assert pos.hash == snapshot[1]
    assert pos.castling == snapshot[2]
    assert pos.ep_sq == snapshot[3]
    assert pos.halfmove == snapshot[4]
    assert pos.fullmove == snapshot[5]
    assert pos.hash_history == snapshot[6]
    assert pos.king_sq == snapshot[7]
    assert pos.board == snapshot[8]
    assert pos.hash == zobrist.compute_hash(pos.board, pos.stm, pos.castling, pos.ep_sq)
