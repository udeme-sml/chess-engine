"""Simple HTTP server for the chess UI."""

from __future__ import annotations

import json
import mimetypes
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import parse_qs, urlparse

from ui.game_session import GameSession, PlayerMode

STATIC = Path(__file__).parent / "static"
SESSION = GameSession()


class Handler(BaseHTTPRequestHandler):
    def log_message(self, format: str, *args) -> None:  # noqa: A003
        pass

    def _send_json(self, data: dict, status: int = 200) -> None:
        body = json.dumps(data).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def _read_json(self) -> dict:
        length = int(self.headers.get("Content-Length", 0))
        if length == 0:
            return {}
        return json.loads(self.rfile.read(length).decode("utf-8"))

    def do_GET(self) -> None:  # noqa: N802
        path = urlparse(self.path).path
        if path == "/api/state":
            if SESSION.pending_engine_move and not SESSION.engine_thinking:
                SESSION.apply_pending_engine_move()
            return self._send_json(SESSION.to_json())
        if path in ("", "/"):
            path = "/index.html"
        file_path = STATIC / path.lstrip("/")
        if not file_path.is_file():
            self.send_error(404)
            return
        data = file_path.read_bytes()
        ctype = mimetypes.guess_type(str(file_path))[0] or "application/octet-stream"
        self.send_response(200)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def do_POST(self) -> None:  # noqa: N802
        path = urlparse(self.path).path
        body = self._read_json()
        if path == "/api/new":
            SESSION.reset()
            SESSION.mode = PlayerMode(body.get("mode", "human_human"))
            return self._send_json(SESSION.to_json())
        if path == "/api/move":
            try:
                SESSION.apply_human_move(body["uci"])
                if SESSION.pending_engine_move and not SESSION.engine_thinking:
                    SESSION.apply_pending_engine_move()
            except (KeyError, ValueError) as e:
                return self._send_json({"error": str(e)}, 400)
            return self._send_json(SESSION.to_json())
        self.send_error(404)


def main() -> None:
    port = 8765
    server = ThreadingHTTPServer(("127.0.0.1", port), Handler)
    print(f"Chess UI: http://127.0.0.1:{port}/")
    server.serve_forever()


if __name__ == "__main__":
    main()
