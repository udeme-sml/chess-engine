"""Attack and check detection."""

from __future__ import annotations

from rules.constants import Color, PieceType, make_piece, piece_color, piece_type
from rules.position import Position
from rules.square import file_of, on_board, rank_of


def sq_attacked_by(pos: Position, sq: int, by_color: Color) -> bool:
    """True if `sq` is attacked by any piece of `by_color`."""
    board = pos.board
    # Pawns
    if by_color == Color.WHITE:
        for delta in (-9, -7):
            a = sq + delta
            if on_board(a) and abs(file_of(a) - file_of(sq)) == 1:
                if board[a] == make_piece(Color.WHITE, PieceType.PAWN):
                    return True
    else:
        for delta in (7, 9):
            a = sq + delta
            if on_board(a) and abs(file_of(a) - file_of(sq)) == 1:
                if board[a] == make_piece(Color.BLACK, PieceType.PAWN):
                    return True

    # Knights
    for delta in (-17, -15, -10, -6, 6, 10, 15, 17):
        a = sq + delta
        if on_board(a) and abs(file_of(a) - file_of(sq)) <= 2:
            p = board[a]
            if p and piece_type(p) == PieceType.KNIGHT and piece_color(p) == by_color:
                return True

    # King
    for delta in (-9, -8, -7, -1, 1, 7, 8, 9):
        a = sq + delta
        if on_board(a) and abs(file_of(a) - file_of(sq)) <= 1:
            p = board[a]
            if p and piece_type(p) == PieceType.KING and piece_color(p) == by_color:
                return True

    # Rays: bishops/queens
    for delta in (-9, -7, 7, 9):
        a = sq + delta
        while on_board(a):
            if delta in (-9, 7) and file_of(a) == 7:
                break
            if delta in (-7, 9) and file_of(a) == 0:
                break
            p = board[a]
            if p:
                if piece_color(p) == by_color and piece_type(p) in (
                    PieceType.BISHOP,
                    PieceType.QUEEN,
                ):
                    return True
                break
            a += delta

    # Rays: rooks/queens
    for delta in (-8, -1, 1, 8):
        a = sq + delta
        while on_board(a):
            if delta == 1 and file_of(a) == 0:
                break
            if delta == -1 and file_of(a) == 7:
                break
            p = board[a]
            if p:
                if piece_color(p) == by_color and piece_type(p) in (
                    PieceType.ROOK,
                    PieceType.QUEEN,
                ):
                    return True
                break
            a += delta

    return False


def in_check(pos: Position, color: Color | None = None) -> bool:
    """True if given side's king is in check (default: side to move)."""
    us = pos.stm if color is None else color
    king_sq = pos.king_sq[int(us)]
    them = Color.BLACK if us == Color.WHITE else Color.WHITE
    return sq_attacked_by(pos, king_sq, them)


def mover_in_check_after(pos: Position) -> bool:
    """After make_move, True if the side that just moved is in check."""
    them = pos.stm
    us = Color.BLACK if them == Color.WHITE else Color.WHITE
    return in_check(pos, us)
