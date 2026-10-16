"""Zobrist hashing keys (fixed seed for reproducible tests)."""

from __future__ import annotations

import random

from rules.constants import CastlingRights, Color, PieceType, make_piece

# piece on square: 12 piece types (6 white + 6 black) * 64
PIECE_KEYS: list[list[int]] = [[0] * 64 for _ in range(16)]
SIDE_KEY: int = 0
CASTLE_KEYS: list[int] = [0] * 16
EP_FILE_KEYS: list[int] = [0] * 8


def _init_keys() -> None:
    rng = random.Random(0xC0FFEE00)
    for pt in range(1, 7):
        for color in (Color.WHITE, Color.BLACK):
            idx = (int(color) << 3) | pt
            for sq in range(64):
                PIECE_KEYS[idx][sq] = rng.getrandbits(64)
    global SIDE_KEY
    SIDE_KEY = rng.getrandbits(64)
    for i in range(16):
        CASTLE_KEYS[i] = rng.getrandbits(64)
    for f in range(8):
        EP_FILE_KEYS[f] = rng.getrandbits(64)


_init_keys()


def hash_piece(piece: int, sq: int) -> int:
    if piece == 0:
        return 0
    return PIECE_KEYS[piece][sq]


def hash_castling(rights: CastlingRights) -> int:
    return CASTLE_KEYS[int(rights)]


def hash_ep_file(file_index: int) -> int:
    return EP_FILE_KEYS[file_index]


def compute_hash(
    board: list[int],
    stm: Color,
    castling: CastlingRights,
    ep_sq: int,
) -> int:
    """Full position hash from scratch (for tests)."""
    h = 0
    for sq, piece in enumerate(board):
        h ^= hash_piece(piece, sq)
    if stm == Color.BLACK:
        h ^= SIDE_KEY
    h ^= hash_castling(castling)
    if ep_sq >= 0:
        h ^= hash_ep_file(ep_sq & 7)
    return h
