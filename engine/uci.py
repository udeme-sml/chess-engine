"""Minimal UCI protocol wrapper (stdin/stdout)."""

from __future__ import annotations

import sys

from engine.api import find_best_move
from rules.move import move_to_uci
from rules.movegen import generate_legal_moves
from rules.position import Position

START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


class UciEngine:
    def __init__(self) -> None:
        self.position = Position.from_fen(START_FEN)
        self._stop = False

    def loop(self) -> None:
        for line in sys.stdin:
            line = line.strip()
            if not line:
                continue
            if self._handle(line):
                break

    def _handle(self, line: str) -> bool:
        parts = line.split()
        cmd = parts[0]
        if cmd == "uci":
            print("id name ChessEngineStub")
            print("id author You")
            print("uciok", flush=True)
        elif cmd == "isready":
            print("readyok", flush=True)
        elif cmd == "ucinewgame":
            self.position = Position.from_fen(START_FEN)
        elif cmd == "position":
            self._position(parts[1:])
        elif cmd == "go":
            self._go(parts[1:])
        elif cmd == "stop":
            self._stop = True
        elif cmd == "quit":
            return True
        return False

    def _position(self, args: list[str]) -> None:
        idx = 0
        if args[0] == "startpos":
            self.position = Position.from_fen(START_FEN)
            idx = 1
        elif args[0] == "fen":
            fen_parts: list[str] = []
            idx = 1
            while idx < len(args) and args[idx] != "moves":
                fen_parts.append(args[idx])
                idx += 1
            self.position = Position.from_fen(" ".join(fen_parts))
        else:
            return
        if idx < len(args) and args[idx] == "moves":
            for uci in args[idx + 1 :]:
                legal = generate_legal_moves(self.position)
                from rules.move import move_from_uci

                self.position.make_move(move_from_uci(uci, legal))

    def _go(self, args: list[str]) -> None:
        self._stop = False
        depth = 64
        movetime = 2000
        for i, a in enumerate(args):
            if a == "depth" and i + 1 < len(args):
                depth = int(args[i + 1])
            if a == "movetime" and i + 1 < len(args):
                movetime = int(args[i + 1])
        mv = find_best_move(self.position, movetime, depth)
        print(f"bestmove {move_to_uci(mv)}", flush=True)


def main() -> None:
    UciEngine().loop()


if __name__ == "__main__":
    main()
