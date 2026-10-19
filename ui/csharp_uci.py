"""Spawn the C# UCI executable for local human-vs-engine play."""

from __future__ import annotations

import subprocess
import threading
from pathlib import Path

_REPO_ROOT = Path(__file__).resolve().parents[1]
_UCI_DLL_NAME = "ChessEngine.Uci.dll"

_client: UciClient | None = None
_client_lock = threading.Lock()


def find_csharp_uci_dll() -> Path | None:
    base = _REPO_ROOT / "chess-engine-csharp" / "src" / "ChessEngine.Uci" / "bin"
    for config in ("Release", "Debug"):
        dll = base / config / "net9.0" / _UCI_DLL_NAME
        if dll.is_file():
            return dll
    return None


def engine_backend_name() -> str:
    if find_csharp_uci_dll() is not None:
        return "C# UCI"
    return "C# UCI (not built)"


def use_csharp_engine() -> bool:
    return find_csharp_uci_dll() is not None


class UciClient:
    def __init__(self, dll: Path) -> None:
        self._proc = subprocess.Popen(
            ["dotnet", "exec", str(dll)],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            text=True,
            bufsize=1,
        )
        self._lock = threading.Lock()
        self._send("uci")
        self._wait_line("uciok")
        self._send("isready")
        self._wait_line("readyok")

    def _send(self, line: str) -> None:
        assert self._proc.stdin is not None
        self._proc.stdin.write(line + "\n")
        self._proc.stdin.flush()

    def _wait_line(self, prefix: str) -> None:
        assert self._proc.stdout is not None
        while True:
            line = self._proc.stdout.readline()
            if not line:
                raise RuntimeError("C# UCI engine exited unexpectedly")
            if line.strip() == prefix or line.startswith(prefix):
                return

    def best_move(self, fen: str, depth: int) -> str:
        with self._lock:
            self._send(f"position fen {fen}")
            self._send(f"go depth {depth}")
            assert self._proc.stdout is not None
            while True:
                line = self._proc.stdout.readline()
                if not line:
                    raise RuntimeError("C# UCI engine exited unexpectedly")
                line = line.strip()
                if line.startswith("bestmove"):
                    parts = line.split()
                    if len(parts) < 2:
                        raise RuntimeError(f"Invalid UCI response: {line}")
                    return parts[1]


def get_csharp_uci_client() -> UciClient | None:
    global _client
    if not use_csharp_engine():
        return None
    with _client_lock:
        if _client is None:
            dll = find_csharp_uci_dll()
            if dll is None:
                return None
            _client = UciClient(dll)
        return _client
