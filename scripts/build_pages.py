#!/usr/bin/env python3
"""Assemble the static site for GitHub Pages (Python sources + UI assets)."""

from __future__ import annotations

import json
import os
import shutil
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
STATIC = ROOT / "ui" / "static"
PY_PACKAGES = ("rules", "engine")
PY_UI = ("ui/__init__.py", "ui/game_session.py")


def main() -> None:
    out = Path(os.environ.get("SITE_DIR", ROOT / "_site"))
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)

    for path in STATIC.iterdir():
        if path.is_file():
            shutil.copy2(path, out / path.name)

    py_root = out / "python"
    manifest: list[str] = []

    for pkg in PY_PACKAGES:
        src_dir = ROOT / pkg
        for path in sorted(src_dir.rglob("*.py")):
            rel = f"{pkg}/{path.relative_to(src_dir).as_posix()}"
            dest = py_root / rel
            dest.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(path, dest)
            manifest.append(rel)

    for rel in PY_UI:
        src = ROOT / rel
        dest = py_root / rel
        dest.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dest)
        manifest.append(rel)

    manifest.sort()
    (out / "python-manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    (out / ".nojekyll").write_text("", encoding="utf-8")
    print(f"Built site at {out} ({len(manifest)} Python modules)")


if __name__ == "__main__":
    main()
