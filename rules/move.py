"""Compact move representation and UCI conversion."""

from __future__ import annotations

from dataclasses import dataclass

from rules.constants import CHAR_TO_PROMO, PROMO_CHARS, PROMO_NONE, MoveFlag
from rules.square import parse_square, square_name

# Packed layout (32-bit int):
#   bits 0-5:   from square
#   bits 6-11:  to square
#   bits 12-14: promotion piece (PROMO_*)
#   bits 15-17: MoveFlag
MOVE_SHIFT_FROM = 0
MOVE_SHIFT_TO = 6
MOVE_SHIFT_PROMO = 12
MOVE_SHIFT_FLAG = 15


@dataclass(frozen=True, slots=True)
class Move:
    """Logical move; stored as a packed int internally in lists for speed."""

    data: int

    @staticmethod
    def pack(from_sq: int, to_sq: int, flag: MoveFlag = MoveFlag.QUIET, promo: int = PROMO_NONE) -> Move:
        data = (
            (from_sq & 63)
            | ((to_sq & 63) << MOVE_SHIFT_TO)
            | ((promo & 7) << MOVE_SHIFT_PROMO)
            | ((int(flag) & 7) << MOVE_SHIFT_FLAG)
        )
        return Move(data)

    @property
    def from_sq(self) -> int:
        return (self.data >> MOVE_SHIFT_FROM) & 63

    @property
    def to_sq(self) -> int:
        return (self.data >> MOVE_SHIFT_TO) & 63

    @property
    def promo(self) -> int:
        return (self.data >> MOVE_SHIFT_PROMO) & 7

    @property
    def flag(self) -> MoveFlag:
        return MoveFlag((self.data >> MOVE_SHIFT_FLAG) & 7)

    def is_capture(self) -> bool:
        f = self.flag
        return f in (MoveFlag.CAPTURE, MoveFlag.EN_PASSANT) or (
            f == MoveFlag.PROMOTION and self.promo != PROMO_NONE
        )

    def is_promotion(self) -> bool:
        return self.flag == MoveFlag.PROMOTION or self.promo != PROMO_NONE

    def __eq__(self, other: object) -> bool:
        if isinstance(other, Move):
            return self.data == other.data
        return NotImplemented

    def __hash__(self) -> int:
        return self.data


MOVE_NULL = Move(0)


def move_to_uci(m: Move) -> str:
    if m.data == 0:
        return "0000"
    s = square_name(m.from_sq) + square_name(m.to_sq)
    if m.promo != PROMO_NONE:
        s += PROMO_CHARS[m.promo]
    return s


def move_from_uci(uci: str, legal_moves: list[Move] | None = None) -> Move:
    """Parse UCI; if legal_moves given, match flag/promo from list."""
    if uci in ("0000", "null"):
        return MOVE_NULL
    from_sq = parse_square(uci[0:2])
    to_sq = parse_square(uci[2:4])
    promo = CHAR_TO_PROMO.get(uci[4], PROMO_NONE) if len(uci) > 4 else PROMO_NONE
    if legal_moves is not None:
        for m in legal_moves:
            if m.from_sq == from_sq and m.to_sq == to_sq and m.promo == promo:
                return m
        raise ValueError(f"UCI move not in legal list: {uci}")
    # Without context, assume quiet or capture by flag unknown — promotion only
    flag = MoveFlag.PROMOTION if promo else MoveFlag.QUIET
    return Move.pack(from_sq, to_sq, flag, promo)
