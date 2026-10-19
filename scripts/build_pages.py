#!/usr/bin/env python3
"""Assemble the static site for GitHub Pages (UI assets + C# WASM engine)."""

from __future__ import annotations

import os
import shutil
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STATIC = ROOT / "ui" / "static"
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

    shutil.copytree(BROWSER_BUNDLE, out / "csharp-engine", dirs_exist_ok=True)
    (out / ".nojekyll").write_text("", encoding="utf-8")
    print(f"Built site at {out} (C# WASM engine in csharp-engine/)")


if __name__ == "__main__":
    main()
