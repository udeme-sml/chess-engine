#!/usr/bin/env python3
"""Download the Performance Polyglot book into data/books/performance.bin."""

from __future__ import annotations

import shutil
import sys
import urllib.request
import zipfile
from pathlib import Path

URL = "https://github.com/ChrisWhittington/polyglot-books/releases/download/v1.0/Performance.zip"
REPO_ROOT = Path(__file__).resolve().parents[1]
OUT = REPO_ROOT / "data" / "books" / "performance.bin"


def main() -> int:
    OUT.parent.mkdir(parents=True, exist_ok=True)
    zip_path = OUT.with_suffix(".zip")
    print(f"Downloading {URL} …")
    urllib.request.urlretrieve(URL, zip_path)
    with zipfile.ZipFile(zip_path) as zf:
        names = [n for n in zf.namelist() if n.lower().endswith(".bin")]
        if not names:
            print("No .bin in archive", file=sys.stderr)
            return 1
        with zf.open(names[0]) as src, open(OUT, "wb") as dst:
            shutil.copyfileobj(src, dst)
    zip_path.unlink(missing_ok=True)
    size = OUT.stat().st_size
    if size % 16 != 0:
        print(f"Unexpected size {size} (not multiple of 16)", file=sys.stderr)
        return 1
    print(f"Wrote {OUT} ({size} bytes)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
