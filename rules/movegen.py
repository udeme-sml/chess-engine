"""Pseudo-legal and legal move generation."""

from __future__ import annotations

from rules.attacks import in_check, mover_in_check_after, sq_attacked_by
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
from rules.move import Move
from rules.position import Position
from rules.square import file_of, on_board, rank_of

def _add_promotions(moves: list[Move], from_sq: int, to_sq: int, capture: bool) -> None:
    flag = MoveFlag.PROMOTION
    for promo in (PROMO_QUEEN, PROMO_ROOK, PROMO_BISHOP, PROMO_KNIGHT):
        moves.append(Move.pack(from_sq, to_sq, flag, promo))


def generate_pseudo_legal_moves(pos: Position, captures_only: bool = False) -> list[Move]:
    moves: list[Move] = []
    us = pos.stm
    them = Color.BLACK if us == Color.WHITE else Color.WHITE
    board = pos.board
    ep = pos.ep_sq

    for from_sq in range(64):
        piece = board[from_sq]
        if not piece or piece_color(piece) != us:
            continue
        pt = piece_type(piece)

        if pt == PieceType.PAWN:
            step = 8 if us == Color.WHITE else -8
            start_rank = 1 if us == Color.WHITE else 6
            promo_rank = 7 if us == Color.WHITE else 0

            to_sq = from_sq + step
            if on_board(to_sq) and not board[to_sq]:
                if rank_of(to_sq) == promo_rank:
                    if not captures_only:
                        _add_promotions(moves, from_sq, to_sq, False)
                elif not captures_only:
                    moves.append(Move.pack(from_sq, to_sq, MoveFlag.QUIET))
                    to2 = from_sq + 2 * step
                    if rank_of(from_sq) == start_rank and on_board(to2) and not board[to2]:
                        moves.append(Move.pack(from_sq, to2, MoveFlag.DOUBLE_PAWN))

            for delta in (step - 1, step + 1):
                to_sq = from_sq + delta
                if not on_board(to_sq) or abs(file_of(to_sq) - file_of(from_sq)) != 1:
                    continue
                target = board[to_sq]
                if target and piece_color(target) == them:
                    if rank_of(to_sq) == promo_rank:
                        _add_promotions(moves, from_sq, to_sq, True)
                    else:
                        moves.append(Move.pack(from_sq, to_sq, MoveFlag.CAPTURE))
                elif to_sq == ep:
                    if rank_of(to_sq) == promo_rank:
                        _add_promotions(moves, from_sq, to_sq, True)
                    else:
                        moves.append(Move.pack(from_sq, to_sq, MoveFlag.EN_PASSANT))

        elif pt == PieceType.KNIGHT:
            for delta in (-17, -15, -10, -6, 6, 10, 15, 17):
                to_sq = from_sq + delta
                if not on_board(to_sq) or abs(file_of(to_sq) - file_of(from_sq)) > 2:
                    continue
                target = board[to_sq]
                if not target:
                    if not captures_only:
                        moves.append(Move.pack(from_sq, to_sq, MoveFlag.QUIET))
                elif piece_color(target) == them:
                    moves.append(Move.pack(from_sq, to_sq, MoveFlag.CAPTURE))

        elif pt == PieceType.KING:
            for delta in (-9, -8, -7, -1, 1, 7, 8, 9):
                to_sq = from_sq + delta
                if not on_board(to_sq) or abs(file_of(to_sq) - file_of(from_sq)) > 1:
                    continue
                target = board[to_sq]
                if not target:
                    if not captures_only:
                        moves.append(Move.pack(from_sq, to_sq, MoveFlag.QUIET))
                elif piece_color(target) == them:
                    moves.append(Move.pack(from_sq, to_sq, MoveFlag.CAPTURE))

            if not captures_only:
                _gen_castling(pos, moves, from_sq, us)

        elif pt in (PieceType.BISHOP, PieceType.ROOK, PieceType.QUEEN):
            deltas = []
            if pt in (PieceType.BISHOP, PieceType.QUEEN):
                deltas.extend((-9, -7, 7, 9))
            if pt in (PieceType.ROOK, PieceType.QUEEN):
                deltas.extend((-8, -1, 1, 8))
            for delta in deltas:
                to_sq = from_sq + delta
                while on_board(to_sq):
                    # Prevent wrap-around (e.g. h1 + 1 -> a2)
                    if delta == 1 and file_of(to_sq) == 0:
                        break
                    if delta == -1 and file_of(to_sq) == 7:
                        break
                    if delta in (-9, 7) and file_of(to_sq) == 7:
                        break
                    if delta in (-7, 9) and file_of(to_sq) == 0:
                        break
                    target = board[to_sq]
                    if not target:
                        if not captures_only:
                            moves.append(Move.pack(from_sq, to_sq, MoveFlag.QUIET))
                    else:
                        if piece_color(target) == them:
                            moves.append(Move.pack(from_sq, to_sq, MoveFlag.CAPTURE))
                        break
                    to_sq += delta

    return moves


def _gen_castling(pos: Position, moves: list[Move], king_sq: int, us: Color) -> None:
    if in_check(pos):
        return
    rights = pos.castling
    board = pos.board
    them = Color.BLACK if us == Color.WHITE else Color.WHITE
    c = int(us)

    if us == Color.WHITE:
        if rights & CastlingRights.WHITE_KING:
            if (
                board[5] == 0
                and board[6] == 0
                and board[7] == make_piece(Color.WHITE, PieceType.ROOK)
                and not sq_attacked_by(pos, 5, them)
                and not sq_attacked_by(pos, 6, them)
            ):
                moves.append(Move.pack(king_sq, 6, MoveFlag.CASTLE_K))
        if rights & CastlingRights.WHITE_QUEEN:
            if (
                board[1] == 0
                and board[2] == 0
                and board[3] == 0
                and board[0] == make_piece(Color.WHITE, PieceType.ROOK)
                and not sq_attacked_by(pos, 2, them)
                and not sq_attacked_by(pos, 3, them)
            ):
                moves.append(Move.pack(king_sq, 2, MoveFlag.CASTLE_Q))
    else:
        if rights & CastlingRights.BLACK_KING:
            if (
                board[61] == 0
                and board[62] == 0
                and board[63] == make_piece(Color.BLACK, PieceType.ROOK)
                and not sq_attacked_by(pos, 61, them)
                and not sq_attacked_by(pos, 62, them)
            ):
                moves.append(Move.pack(king_sq, 62, MoveFlag.CASTLE_K))
        if rights & CastlingRights.BLACK_QUEEN:
            if (
                board[57] == 0
                and board[58] == 0
                and board[59] == 0
                and board[56] == make_piece(Color.BLACK, PieceType.ROOK)
                and not sq_attacked_by(pos, 58, them)
                and not sq_attacked_by(pos, 59, them)
            ):
                moves.append(Move.pack(king_sq, 58, MoveFlag.CASTLE_Q))


def _legal_filter(pos: Position, pseudo: list[Move]) -> list[Move]:
    legal: list[Move] = []
    for m in pseudo:
        pos.make_move(m)
        if not mover_in_check_after(pos):
            legal.append(m)
        pos.unmake_move()
    return legal


def generate_legal_moves(pos: Position) -> list[Move]:
    return _legal_filter(pos, generate_pseudo_legal_moves(pos, captures_only=False))


def generate_captures(pos: Position) -> list[Move]:
    """Captures and promotions only (for quiescence search)."""
    pseudo = list(generate_pseudo_legal_moves(pos, captures_only=True))
    full = generate_pseudo_legal_moves(pos, captures_only=False)
    promo_moves = [m for m in full if m.is_promotion()]
    seen = {m.data for m in pseudo}
    combined = pseudo + [m for m in promo_moves if m.data not in seen]
    return _legal_filter(pos, combined)


def generate_legal_moves_copy(pos: Position) -> list[Move]:
    """Return a new list (safe if caller stores moves across make_move)."""
    return list(generate_legal_moves(pos))
