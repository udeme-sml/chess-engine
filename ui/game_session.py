"""In-memory game state for the web UI."""

from __future__ import annotations

import threading
from dataclasses import dataclass, field
from enum import Enum

from ui.csharp_uci import get_csharp_uci_client
from rules.constants import Color
from rules.fen import board_to_fen_piece_placement
from rules.game import GameResult, game_result
from rules.move import move_from_uci, move_to_uci
from rules.movegen import generate_legal_moves
from rules.position import Position


class PlayerMode(str, Enum):
    HUMAN_VS_HUMAN = "human_human"
    HUMAN_VS_ENGINE = "human_engine"


ENGINE_SEARCH_DEPTH = 4


@dataclass
class GameSession:
    mode: PlayerMode = PlayerMode.HUMAN_VS_HUMAN
    position: Position = field(default_factory=lambda: Position.from_fen(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    ))
    human_color: Color = Color.WHITE
    engine_thinking: bool = False
    engine_think_depth: int = 0
    _engine_thread: threading.Thread | None = field(default=None, repr=False)
    pending_engine_move: str | None = None
    move_history_uci: list[str] = field(default_factory=list)

    def reset(self) -> None:
        self.position = Position.from_fen(
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
        )
        self.move_history_uci.clear()
        self.pending_engine_move = None
        self.engine_thinking = False
        self.engine_think_depth = 0

    def legal_moves_uci(self) -> list[str]:
        return [move_to_uci(m) for m in generate_legal_moves(self.position)]

    def apply_human_move(self, uci: str) -> None:
        if self.engine_thinking:
            raise ValueError("Engine is thinking")
        moves = generate_legal_moves(self.position)
        m = move_from_uci(uci, moves)
        self.position.make_move(m)
        self.move_history_uci.append(uci)
        if self.mode == PlayerMode.HUMAN_VS_ENGINE:
            self._maybe_start_engine()

    def _maybe_start_engine(self) -> None:
        if game_result(self.position) != GameResult.ONGOING:
            return
        if self.position.stm != self.human_color:
            self._start_engine_thread()

    def _start_engine_thread(self) -> None:
        if self.engine_thinking:
            return
        uci_client = get_csharp_uci_client()
        if uci_client is None:
            raise RuntimeError(
                "C# engine not available. Build it with: "
                "cd chess-engine-csharp && dotnet build -c Release"
            )
        self.engine_thinking = True
        fen = self.position.fen()

        def run() -> None:
            try:
                self.engine_think_depth = ENGINE_SEARCH_DEPTH
                self.pending_engine_move = uci_client.best_move(fen, ENGINE_SEARCH_DEPTH)
            finally:
                self.engine_thinking = False
                self.engine_think_depth = 0

        self._engine_thread = threading.Thread(target=run, daemon=True)
        self._engine_thread.start()

    def apply_pending_engine_move(self) -> bool:
        if not self.pending_engine_move or self.engine_thinking:
            return False
        uci = self.pending_engine_move
        self.pending_engine_move = None
        moves = generate_legal_moves(self.position)
        m = move_from_uci(uci, moves)
        self.position.make_move(m)
        self.move_history_uci.append(uci)
        return True

    def to_json(self) -> dict:
        res = game_result(self.position)
        return {
            "fen": self.position.fen(),
            "placement": board_to_fen_piece_placement(self.position.board),
            "stm": "w" if self.position.stm == Color.WHITE else "b",
            "legal_moves": self.legal_moves_uci(),
            "in_check": self._side_in_check(),
            "result": res.name if res != GameResult.ONGOING else None,
            "mode": self.mode.value,
            "engine_thinking": self.engine_thinking,
            "engine_think_depth": self.engine_think_depth,
            "pending_engine_move": self.pending_engine_move,
            "move_history": self.move_history_uci,
            "engine_backend": "csharp",
        }

    def _side_in_check(self) -> bool:
        from rules.attacks import in_check

        return in_check(self.position)
