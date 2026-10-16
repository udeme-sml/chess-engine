"""Unit tests for special rules and game outcomes."""

import pytest

from rules.constants import Color
from rules.game import GameResult, count_repetition, game_result, has_insufficient_material
from rules.move import move_from_uci
from rules.movegen import generate_legal_moves
from rules.position import Position


def test_checkmate_fools_mate() -> None:
    # After 1.f3 e5 2.g4 Qh4#
    fen = "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3"
    pos = Position.from_fen(fen)
    assert game_result(pos) == GameResult.CHECKMATE
    assert not generate_legal_moves(pos)


def test_stalemate() -> None:
    fen = "k7/P7/K7/8/8/8/8/8 b - - 0 1"
    pos = Position.from_fen(fen)
    assert game_result(pos) == GameResult.STALEMATE


def test_en_passant_capture() -> None:
    # After ...d5 vs e4/e5, white may capture en passant on d6
    fen = "rnbqkbnr/ppp2ppp/8/3pP3/8/5N2/PPPP1PPP/RNBQKBNR w KQkq d6 0 3"
    pos = Position.from_fen(fen)
    ep = move_from_uci("e5d6", generate_legal_moves(pos))
    assert ep.flag.name == "EN_PASSANT"


def test_castling_blocked_through_check() -> None:
    # King in check cannot castle
    fen = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
    pos = Position.from_fen(fen)
    castles = [m for m in generate_legal_moves(pos) if m.flag.name.startswith("CASTLE")]
    assert len(castles) == 2
    fen2 = "r3k2r/8/8/8/8/4q3/8/R3K2R w KQkq - 0 1"  # queen on e3 gives check on e1
    pos2 = Position.from_fen(fen2)
    castles2 = [m for m in generate_legal_moves(pos2) if m.flag.name.startswith("CASTLE")]
    assert castles2 == []


def test_castling_through_attacked_square() -> None:
    fen = "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
    pos = Position.from_fen(fen)
    # Place black rook attacking f1 square path for O-O
    board = pos.board.copy()
    board[61] = 0  # clear f8
    board[5] = 0  # f1 empty for white O-O — white king e1, need attack on f1
    # Rook on f8 attacks f1... f8 is 61 black rook
    from rules.constants import B_ROOK

    board[61] = B_ROOK
    pos.board = board
    pos._refresh_king_sq()
    castles = [m for m in generate_legal_moves(pos) if m.flag.name == "CASTLE_K"]
    assert castles == []


def test_promotion_all_pieces() -> None:
    fen = "8/P7/8/8/8/8/8/4K2k w - - 0 1"
    pos = Position.from_fen(fen)
    promos = [m for m in generate_legal_moves(pos) if m.is_promotion()]
    assert len(promos) == 4


def test_threefold_repetition() -> None:
    fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    pos = Position.from_fen(fen)
    seq = ["b1c3", "b8c6", "c3b1", "c6b8"] * 3
    for uci in seq:
        moves = generate_legal_moves(pos)
        pos.make_move(move_from_uci(uci, moves))
    assert count_repetition(pos) >= 3
    assert game_result(pos) == GameResult.THREEFOLD


def test_fifty_move_rule() -> None:
    fen = "k7/8/8/8/8/8/8/K7 w - - 100 1"
    pos = Position.from_fen(fen)
    assert game_result(pos) == GameResult.FIFTY_MOVE


def test_insufficient_material() -> None:
    fen = "8/8/8/8/8/8/8/Kk3B1b w - - 0 1"  # bishops on same color squares
    pos = Position.from_fen(fen)
    assert has_insufficient_material(pos)
