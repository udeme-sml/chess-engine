"""Mutable chess position with make_move / unmake_move."""

from __future__ import annotations

from dataclasses import dataclass

from rules.constants import (
    CastlingRights,
    Color,
    MoveFlag,
    PieceType,
    PROMO_BISHOP,
    PROMO_KNIGHT,
    PROMO_QUEEN,
    PROMO_ROOK,
    make_piece,
    piece_color,
    piece_type,
)
from rules.fen import parse_fen, to_fen
from rules.move import Move
from rules.square import file_of, rank_of
from rules import zobrist


@dataclass(slots=True)
class UndoInfo:
    move: Move
    captured: int
    captured_sq: int
    castling: CastlingRights
    ep_sq: int
    halfmove: int
    hash: int
    fullmove: int
    king_sq_white: int
    king_sq_black: int


# White indices 0, black indices 1
_W = 0
_B = 1
CASTLE_K_ROOK = (7, 63)
CASTLE_Q_ROOK = (0, 56)
CASTLE_K_ROOK_TO = (5, 61)
CASTLE_Q_ROOK_TO = (3, 59)


class Position:
    """
    Single mutable position. Board is a length-64 list of packed pieces.
    hash_history records Zobrist hash after each make_move (includes current).
    """

    __slots__ = (
        "board",
        "stm",
        "castling",
        "ep_sq",
        "halfmove",
        "fullmove",
        "hash",
        "hash_history",
        "_undo_stack",
        "king_sq",
    )

    def __init__(self) -> None:
        self.board: list[int] = [0] * 64
        self.stm: Color = Color.WHITE
        self.castling: CastlingRights = CastlingRights.ALL
        self.ep_sq: int = -1
        self.halfmove: int = 0
        self.fullmove: int = 1
        self.hash: int = 0
        self.hash_history: list[int] = []
        self._undo_stack: list[UndoInfo] = []
        self.king_sq: list[int] = [4, 60]

    @classmethod
    def from_fen(cls, fen: str) -> Position:
        pos = cls()
        board, stm, castling, ep_sq, halfmove, fullmove = parse_fen(fen)
        pos.board = board
        pos.stm = stm
        pos.castling = castling
        pos.ep_sq = ep_sq
        pos.halfmove = halfmove
        pos.fullmove = fullmove
        pos._refresh_king_sq()
        pos.hash = zobrist.compute_hash(pos.board, pos.stm, pos.castling, pos.ep_sq)
        pos.hash_history = [pos.hash]
        return pos

    def fen(self) -> str:
        return to_fen(self.board, self.stm, self.castling, self.ep_sq, self.halfmove, self.fullmove)

    def _refresh_king_sq(self) -> None:
        for color in (Color.WHITE, Color.BLACK):
            king_piece = make_piece(color, PieceType.KING)
            for sq in range(64):
                if self.board[sq] == king_piece:
                    self.king_sq[int(color)] = sq
                    break

    def piece_at(self, sq: int) -> int:
        return self.board[sq]

    def _remove_piece(self, sq: int) -> int:
        piece = self.board[sq]
        if piece:
            self.hash ^= zobrist.hash_piece(piece, sq)
            self.board[sq] = 0
        return piece

    def _put_piece(self, piece: int, sq: int) -> None:
        self.board[sq] = piece
        if piece:
            self.hash ^= zobrist.hash_piece(piece, sq)

    def _move_piece(self, from_sq: int, to_sq: int) -> None:
        piece = self._remove_piece(from_sq)
        self._put_piece(piece, to_sq)

    def make_move(self, move: Move) -> None:
        us = self.stm
        them = Color.BLACK if us == Color.WHITE else Color.WHITE
        from_sq = move.from_sq
        to_sq = move.to_sq
        flag = move.flag
        promo = move.promo

        piece = self.board[from_sq]
        if not piece:
            raise ValueError(f"make_move: empty from square {from_sq}")

        undo = UndoInfo(
            move=move,
            captured=0,
            captured_sq=to_sq,
            castling=self.castling,
            ep_sq=self.ep_sq,
            halfmove=self.halfmove,
            hash=self.hash,
            fullmove=self.fullmove,
            king_sq_white=self.king_sq[_W],
            king_sq_black=self.king_sq[_B],
        )

        old_castle = self.castling
        old_ep = self.ep_sq

        captured = 0
        captured_sq = to_sq

        if flag == MoveFlag.EN_PASSANT:
            captured_sq = to_sq + (-8 if us == Color.WHITE else 8)
            captured = self._remove_piece(captured_sq)
        elif flag in (MoveFlag.CAPTURE, MoveFlag.PROMOTION):
            captured = self._remove_piece(to_sq)
        else:
            if self.board[to_sq]:
                captured = self._remove_piece(to_sq)

        undo.captured = captured
        undo.captured_sq = captured_sq

        if piece_type(piece) == PieceType.PAWN or captured:
            self.halfmove = 0
        else:
            self.halfmove += 1

        new_castle = self.castling
        if piece_type(piece) == PieceType.KING:
            if us == Color.WHITE:
                new_castle &= ~CastlingRights.WHITE
            else:
                new_castle &= ~CastlingRights.BLACK
        if from_sq in (0, 7, 56, 63):
            new_castle &= ~_rook_right_for_square(from_sq)
        if captured_sq in (0, 7, 56, 63):
            new_castle &= ~_rook_right_for_square(captured_sq)

        new_ep = -1
        if flag == MoveFlag.DOUBLE_PAWN:
            new_ep = (from_sq + to_sq) // 2

        self._remove_piece(from_sq)

        if flag == MoveFlag.CASTLE_K:
            self._put_piece(make_piece(us, PieceType.KING), to_sq)
            self.king_sq[int(us)] = to_sq
            rook_from, rook_to = CASTLE_K_ROOK[int(us)], CASTLE_K_ROOK_TO[int(us)]
            self._move_piece(rook_from, rook_to)
        elif flag == MoveFlag.CASTLE_Q:
            self._put_piece(make_piece(us, PieceType.KING), to_sq)
            self.king_sq[int(us)] = to_sq
            rook_from, rook_to = CASTLE_Q_ROOK[int(us)], CASTLE_Q_ROOK_TO[int(us)]
            self._move_piece(rook_from, rook_to)
        elif flag == MoveFlag.PROMOTION or promo:
            promo_type = {
                PROMO_QUEEN: PieceType.QUEEN,
                PROMO_ROOK: PieceType.ROOK,
                PROMO_BISHOP: PieceType.BISHOP,
                PROMO_KNIGHT: PieceType.KNIGHT,
            }[promo]
            self._put_piece(make_piece(us, promo_type), to_sq)
        else:
            self._put_piece(piece, to_sq)
            if piece_type(piece) == PieceType.KING:
                self.king_sq[int(us)] = to_sq

        if old_castle != new_castle:
            self.hash ^= zobrist.hash_castling(old_castle)
            self.hash ^= zobrist.hash_castling(new_castle)
            self.castling = new_castle

        if old_ep != new_ep:
            if old_ep >= 0:
                self.hash ^= zobrist.hash_ep_file(old_ep & 7)
            if new_ep >= 0:
                self.hash ^= zobrist.hash_ep_file(new_ep & 7)
            self.ep_sq = new_ep

        self.hash ^= zobrist.SIDE_KEY
        self.stm = them
        if us == Color.BLACK:
            self.fullmove += 1

        self._undo_stack.append(undo)
        self.hash_history.append(self.hash)

    def unmake_move(self) -> None:
        if not self._undo_stack:
            raise RuntimeError("unmake_move: empty stack")
        undo = self._undo_stack.pop()
        self.hash_history.pop()

        move = undo.move
        us = Color.BLACK if self.stm == Color.WHITE else Color.WHITE
        self.stm = us
        self.hash = undo.hash
        self.castling = undo.castling
        self.ep_sq = undo.ep_sq
        self.halfmove = undo.halfmove
        self.fullmove = undo.fullmove
        self.king_sq[_W] = undo.king_sq_white
        self.king_sq[_B] = undo.king_sq_black

        from_sq = move.from_sq
        to_sq = move.to_sq
        flag = move.flag
        promo = move.promo

        if flag == MoveFlag.CASTLE_K:
            c = int(us)
            self.board[to_sq] = 0
            self.board[CASTLE_K_ROOK_TO[c]] = 0
            self.board[from_sq] = make_piece(us, PieceType.KING)
            self.board[CASTLE_K_ROOK[c]] = make_piece(us, PieceType.ROOK)
        elif flag == MoveFlag.CASTLE_Q:
            c = int(us)
            self.board[to_sq] = 0
            self.board[CASTLE_Q_ROOK_TO[c]] = 0
            self.board[from_sq] = make_piece(us, PieceType.KING)
            self.board[CASTLE_Q_ROOK[c]] = make_piece(us, PieceType.ROOK)
        elif flag == MoveFlag.EN_PASSANT:
            self.board[to_sq] = 0
            self.board[undo.captured_sq] = undo.captured
            self.board[from_sq] = make_piece(us, PieceType.PAWN)
        elif flag == MoveFlag.PROMOTION or promo:
            self.board[to_sq] = undo.captured
            self.board[from_sq] = make_piece(us, PieceType.PAWN)
        else:
            piece_on_to = self.board[to_sq]
            self.board[to_sq] = undo.captured
            self.board[from_sq] = piece_on_to


def _rook_right_for_square(sq: int) -> CastlingRights:
    return {
        0: CastlingRights.WHITE_QUEEN,
        7: CastlingRights.WHITE_KING,
        56: CastlingRights.BLACK_QUEEN,
        63: CastlingRights.BLACK_KING,
    }.get(sq, CastlingRights.NONE)
