"""Perft tests — must match known reference counts."""

import pytest

from rules.perft import perft
from rules.position import Position

START = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
KIWI = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
POS3 = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1"
POS4 = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"


@pytest.mark.parametrize(
    "fen,depth,expected",
    [
        (START, 1, 20),
        (START, 2, 400),
        (START, 3, 8902),
        (START, 4, 197281),
        (START, 5, 4865609),
        (KIWI, 1, 48),
        (KIWI, 2, 2039),
        (KIWI, 3, 97862),
        (KIWI, 4, 4085603),
        (POS3, 1, 14),
        (POS3, 2, 191),
        (POS3, 3, 2812),
        (POS3, 4, 43238),
        (POS3, 5, 674624),
        (POS4, 1, 6),
        (POS4, 2, 264),
        (POS4, 3, 9467),
        (POS4, 4, 422333),
    ],
)
def test_perft(fen: str, depth: int, expected: int) -> None:
    pos = Position.from_fen(fen)
    assert perft(pos, depth) == expected
