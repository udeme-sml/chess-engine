"""Square helpers: naming, distance, and attack tables."""

from __future__ import annotations

FILES = "abcdefgh"
RANKS = "12345678"


def file_of(sq: int) -> int:
    return sq & 7


def rank_of(sq: int) -> int:
    return sq >> 3


def square_name(sq: int) -> str:
    return FILES[file_of(sq)] + RANKS[rank_of(sq)]


def parse_square(name: str) -> int:
    f = FILES.index(name[0])
    r = RANKS.index(name[1])
    return (r << 3) | f


def sq_up(sq: int, color_white: bool) -> int:
    return sq + (8 if color_white else -8)


def on_board(sq: int) -> bool:
    return 0 <= sq < 64


def distance(sq1: int, sq2: int) -> int:
    f1, r1 = file_of(sq1), rank_of(sq1)
    f2, r2 = file_of(sq2), rank_of(sq2)
    return max(abs(f1 - f2), abs(r1 - r2))
