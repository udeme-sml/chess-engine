#!/usr/bin/env python3
"""Assemble the static site for GitHub Pages (UI assets + C# WASM engine)."""

from __future__ import annotations

import os
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STATIC = ROOT / "ui" / "static"
BOOK_SRC = ROOT / "data" / "books" / "performance.bin"
BROWSER_PROJECT = ROOT / "chess-engine-csharp" / "src" / "ChessEngine.Browser" / "ChessEngine.Browser.csproj"
BROWSER_BUNDLE = (
    ROOT
    / "chess-engine-csharp"
    / "src"
    / "ChessEngine.Browser"
    / "bin"
    / "Release"
    / "net9.0"
    / "browser-wasm"
    / "AppBundle"
)


def publish_browser_wasm() -> None:
    subprocess.run(
        ["dotnet", "publish", "-c", "Release", str(BROWSER_PROJECT)],
        cwd=ROOT,
        check=True,
    )
    if not BROWSER_BUNDLE.is_dir():
        raise RuntimeError(f"WASM AppBundle not found at {BROWSER_BUNDLE}")


def prepare_site_dir(out: Path) -> None:
    if not out.exists():
        out.mkdir(parents=True)
        return
    try:
        shutil.rmtree(out)
    except PermissionError:
        print(
            f"Could not remove {out} (folder in use — close any server or Explorer window using it). "
            "Updating files in place."
        )
        for child in out.iterdir():
            if child.is_dir():
                shutil.rmtree(child, ignore_errors=True)
            else:
                child.unlink(missing_ok=True)
    out.mkdir(parents=True, exist_ok=True)


def main() -> None:
    out = Path(os.environ.get("SITE_DIR", ROOT / "_site"))
    prepare_site_dir(out)

    publish_browser_wasm()

    for path in STATIC.iterdir():
        if path.is_file():
            shutil.copy2(path, out / path.name)
        elif path.is_dir() and path.name != "csharp-engine":
            shutil.copytree(path, out / path.name, dirs_exist_ok=True)

    if BOOK_SRC.is_file():
        for dest_dir in (out / "books", STATIC / "books"):
            dest_dir.mkdir(parents=True, exist_ok=True)
            shutil.copy2(BOOK_SRC, dest_dir / "performance.bin")
    else:
        print(f"Warning: opening book not found at {BOOK_SRC} — run scripts/fetch_performance_book.py")

    shutil.copytree(BROWSER_BUNDLE, out / "csharp-engine", dirs_exist_ok=True)
    (out / ".nojekyll").write_text("", encoding="utf-8")
    print(f"Built site at {out} (C# WASM engine in csharp-engine/)")


if __name__ == "__main__":
    main()
