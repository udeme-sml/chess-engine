"""FEN parsing and serialization."""

from __future__ import annotations

from rules.constants import (
    B_BISHOP,
    B_KING,
    B_KNIGHT,
    B_PAWN,
    B_QUEEN,
    B_ROOK,
    CastlingRights,
    Color,
    W_BISHOP,
    W_KING,
    W_KNIGHT,
    W_PAWN,
    W_QUEEN,
    W_ROOK,
)
from rules.square import file_of, parse_square, rank_of

FEN_TO_PIECE = {
    "P": W_PAWN,
    "N": W_KNIGHT,
    "B": W_BISHOP,
    "R": W_ROOK,
    "Q": W_QUEEN,
    "K": W_KING,
    "p": B_PAWN,
    "n": B_KNIGHT,
    "b": B_BISHOP,
    "r": B_ROOK,
    "q": B_QUEEN,
    "k": B_KING,
}

PIECE_TO_FEN = {v: k for k, v in FEN_TO_PIECE.items()}


def parse_fen(fen: str) -> tuple[list[int], Color, CastlingRights, int, int, int]:
    """
    Parse FEN into board, side to move, castling, ep square (-1 if none),
    halfmove clock, fullmove number.
    """
    parts = fen.strip().split()
    if len(parts) < 4:
        raise ValueError(f"Invalid FEN: {fen}")

    board = [0] * 64
    rank = 7
    file = 0
    for ch in parts[0]:
        if ch == "/":
            rank -= 1
            file = 0
        elif ch.isdigit():
            file += int(ch)
        else:
            sq = (rank << 3) | file
            board[sq] = FEN_TO_PIECE[ch]
            file += 1

    stm = Color.WHITE if parts[1] == "w" else Color.BLACK

    castling = CastlingRights.NONE
    if len(parts) > 2 and parts[2] != "-":
        flags = parts[2]
        if "K" in flags:
            castling |= CastlingRights.WHITE_KING
        if "Q" in flags:
            castling |= CastlingRights.WHITE_QUEEN
        if "k" in flags:
            castling |= CastlingRights.BLACK_KING
        if "q" in flags:
            castling |= CastlingRights.BLACK_QUEEN

    ep_sq = -1
    if len(parts) > 3 and parts[3] != "-":
        ep_sq = parse_square(parts[3])

    halfmove = int(parts[4]) if len(parts) > 4 else 0
    fullmove = int(parts[5]) if len(parts) > 5 else 1

    return board, stm, castling, ep_sq, halfmove, fullmove


def board_to_fen_piece_placement(board: list[int]) -> str:
    rows: list[str] = []
    for rank in range(7, -1, -1):
        empty = 0
        row_chars: list[str] = []
        for file in range(8):
            sq = (rank << 3) | file
            piece = board[sq]
            if piece == 0:
                empty += 1
            else:
                if empty:
                    row_chars.append(str(empty))
                    empty = 0
                row_chars.append(PIECE_TO_FEN[piece])
        if empty:
            row_chars.append(str(empty))
        rows.append("".join(row_chars))
    return "/".join(rows)


def to_fen(
    board: list[int],
    stm: Color,
    castling: CastlingRights,
    ep_sq: int,
    halfmove: int,
    fullmove: int,
) -> str:
    placement = board_to_fen_piece_placement(board)
    stm_ch = "w" if stm == Color.WHITE else "b"
    castle = ""
    if castling & CastlingRights.WHITE_KING:
        castle += "K"
    if castling & CastlingRights.WHITE_QUEEN:
        castle += "Q"
    if castling & CastlingRights.BLACK_KING:
        castle += "k"
    if castling & CastlingRights.BLACK_QUEEN:
        castle += "q"
    if not castle:
        castle = "-"
    ep = "-" if ep_sq < 0 else f"{chr(ord('a') + file_of(ep_sq))}{rank_of(ep_sq) + 1}"
    return f"{placement} {stm_ch} {castle} {ep} {halfmove} {fullmove}"
