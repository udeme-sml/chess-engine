"""Game outcome detection: mate, stalemate, draws."""

from __future__ import annotations

from enum import Enum, auto

from rules.constants import Color, PieceType, piece_type
from rules.movegen import generate_legal_moves
from rules.position import Position


class GameResult(Enum):
    ONGOING = auto()
    CHECKMATE = auto()  # side to move is mated
    STALEMATE = auto()
    THREEFOLD = auto()
    FIFTY_MOVE = auto()
    INSUFFICIENT_MATERIAL = auto()


def count_repetition(pos: Position) -> int:
    """How many times the current hash appears in hash_history (including now)."""
    h = pos.hash
    return sum(1 for x in pos.hash_history if x == h)


def has_insufficient_material(pos: Position) -> bool:
    """Draw by insufficient material (simplified exact cases)."""
    board = pos.board
    white: list[PieceType] = []
    black: list[PieceType] = []
    white_bishop_squares: list[int] = []
    black_bishop_squares: list[int] = []

    for sq, piece in enumerate(board):
        if not piece:
            continue
        pt = piece_type(piece)
        color = (piece >> 3) & 1
        if pt == PieceType.KING:
            continue
        if pt == PieceType.PAWN or pt == PieceType.ROOK or pt == PieceType.QUEEN:
            return False
        if color == 0:
            white.append(pt)
            if pt == PieceType.BISHOP:
                white_bishop_squares.append(sq)
        else:
            black.append(pt)
            if pt == PieceType.BISHOP:
                black_bishop_squares.append(sq)

    # K vs K
    if not white and not black:
        return True
    # K+B vs K or K+N vs K
    if (white == [PieceType.BISHOP] and not black) or (white == [PieceType.KNIGHT] and not black):
        return True
    if (black == [PieceType.BISHOP] and not white) or (black == [PieceType.KNIGHT] and not white):
        return True
    # K+B vs K+B same color bishops
    if white == [PieceType.BISHOP] and black == [PieceType.BISHOP]:
        if (white_bishop_squares[0] ^ black_bishop_squares[0]) & 1 == 0:
            return True
    return False


def side_in_check(pos: Position) -> bool:
    from rules.attacks import in_check

    return in_check(pos)


def game_result(pos: Position) -> GameResult:
    if count_repetition(pos) >= 3:
        return GameResult.THREEFOLD
    if pos.halfmove >= 100:
        return GameResult.FIFTY_MOVE
    if has_insufficient_material(pos):
        return GameResult.INSUFFICIENT_MATERIAL

    moves = generate_legal_moves(pos)
    if moves:
        return GameResult.ONGOING
    if side_in_check(pos):
        return GameResult.CHECKMATE
    return GameResult.STALEMATE
