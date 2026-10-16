"""Shared chess constants: squares, pieces, and castling flags."""

from enum import IntEnum, IntFlag

# Square index: a1=0 .. h8=63 (rank 0 = first rank in array = white's back rank)
FILE_A, FILE_H = 0, 7
RANK_1, RANK_8 = 0, 7

NUM_SQUARES = 64


class Color(IntEnum):
    WHITE = 0
    BLACK = 1


class PieceType(IntEnum):
    EMPTY = 0
    PAWN = 1
    KNIGHT = 2
    BISHOP = 3
    ROOK = 4
    QUEEN = 5
    KING = 6


# Packed piece: color in high bit (0=white, 1=black), type in low 3 bits
def make_piece(color: Color, piece_type: PieceType) -> int:
    if piece_type == PieceType.EMPTY:
        return 0
    return (int(color) << 3) | int(piece_type)


def piece_color(piece: int) -> Color:
    return Color((piece >> 3) & 1)


def piece_type(piece: int) -> PieceType:
    return PieceType(piece & 7)


# Convenience piece constants (white then black offset by 8 in raw encoding)
W_PAWN = make_piece(Color.WHITE, PieceType.PAWN)
W_KNIGHT = make_piece(Color.WHITE, PieceType.KNIGHT)
W_BISHOP = make_piece(Color.WHITE, PieceType.BISHOP)
W_ROOK = make_piece(Color.WHITE, PieceType.ROOK)
W_QUEEN = make_piece(Color.WHITE, PieceType.QUEEN)
W_KING = make_piece(Color.WHITE, PieceType.KING)

B_PAWN = make_piece(Color.BLACK, PieceType.PAWN)
B_KNIGHT = make_piece(Color.BLACK, PieceType.KNIGHT)
B_BISHOP = make_piece(Color.BLACK, PieceType.BISHOP)
B_ROOK = make_piece(Color.BLACK, PieceType.ROOK)
B_QUEEN = make_piece(Color.BLACK, PieceType.QUEEN)
B_KING = make_piece(Color.BLACK, PieceType.KING)


class CastlingRights(IntFlag):
    NONE = 0
    WHITE_KING = 1
    WHITE_QUEEN = 2
    BLACK_KING = 4
    BLACK_QUEEN = 8
    WHITE = WHITE_KING | WHITE_QUEEN
    BLACK = BLACK_KING | BLACK_QUEEN
    ALL = WHITE | BLACK


# Move flags (stored in packed move)
class MoveFlag(IntEnum):
    QUIET = 0
    CAPTURE = 1
    DOUBLE_PAWN = 2
    EN_PASSANT = 3
    CASTLE_K = 4
    CASTLE_Q = 5
    PROMOTION = 6  # capture promotions use CAPTURE | promo piece in promo field


PROMO_NONE = 0
PROMO_QUEEN = 1
PROMO_ROOK = 2
PROMO_BISHOP = 3
PROMO_KNIGHT = 4

PROMO_CHARS = {PROMO_QUEEN: "q", PROMO_ROOK: "r", PROMO_BISHOP: "b", PROMO_KNIGHT: "n"}
CHAR_TO_PROMO = {v: k for k, v in PROMO_CHARS.items()}

# Ray directions (delta on 0..63 board, file = sq % 8)
DIRS_N = (-8, 8, -1, 1, -9, -7, 7, 9)
DIRS_KNIGHT = (-17, -15, -10, -6, 6, 10, 15, 17)
DIRS_BISHOP = (-9, -7, 7, 9)
DIRS_ROOK = (-8, 8, -1, 1)
DIRS_KING = DIRS_N + DIRS_BISHOP  # king uses all 8 adjacent

NOT_A_FILE = 0xFEFEFEFEFEFEFEFE  # masks for bitboard-style bounds; we use arithmetic checks instead
