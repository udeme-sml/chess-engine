#!/usr/bin/env python
"""Play two UCI engine processes against each other from opening FENs."""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

OPENINGS = [
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
    "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1",
]


class UciProcess:
    def __init__(self, cmd: list[str]) -> None:
        self.proc = subprocess.Popen(
            cmd,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            text=True,
            bufsize=1,
        )

    def send(self, line: str) -> None:
        assert self.proc.stdin
        self.proc.stdin.write(line + "\n")
        self.proc.stdin.flush()

    def read_until(self, prefix: str) -> str:
        assert self.proc.stdout
        while True:
            line = self.proc.stdout.readline()
            if line.startswith(prefix):
                return line.strip()


def play_game(engine_a: UciProcess, engine_b: UciProcess, fen: str, max_plies: int = 200) -> str:
    for eng in (engine_a, engine_b):
        eng.send("uci")
        eng.read_until("uciok")
        eng.send("isready")
        eng.read_until("readyok")

    moves: list[str] = []
    for ply in range(max_plies):
        eng = engine_a if ply % 2 == 0 else engine_b
        eng.send("ucinewgame")
        eng.send(f"position fen {fen} moves {' '.join(moves)}")
        eng.send("go depth 6")
        line = eng.read_until("bestmove")
        token = line.split()[1]
        if token == "(none)":
            return "1/2-1/2"
        moves.append(token)

    return "1/2-1/2 (move limit)"


def main() -> None:
    if len(sys.argv) < 3:
        print("Usage: engine_match.py <engine_cmd_a...> <engine_cmd_b...>")
        print(
            "Example: python scripts/engine_match.py "
            "dotnet exec chess-engine-csharp/src/ChessEngine.Uci/bin/Release/net9.0/ChessEngine.Uci.dll "
            "dotnet exec chess-engine-csharp/src/ChessEngine.Uci/bin/Release/net9.0/ChessEngine.Uci.dll"
        )
        sys.exit(1)
    mid = len(sys.argv) // 2
    cmd_a = sys.argv[1 : mid + 1]
    cmd_b = sys.argv[mid + 1 :]
    a = UciProcess(cmd_a)
    b = UciProcess(cmd_b)
    root = Path(__file__).resolve().parents[1]
    for i, fen in enumerate(OPENINGS):
        result = play_game(a, b, fen)
        print(f"Game {i + 1}: {result}")


if __name__ == "__main__":
    main()
