# Opening books (Polyglot)

`performance.bin` is Marc Lacrosse’s **Performance** [Polyglot](https://hgm.nubati.net/book_format.html) book (~1.4 MB, ~93k entries), from the [polyglot-books](https://github.com/ChrisWhittington/polyglot-books) release assets.

## Reload

```bash
python scripts/fetch_performance_book.py
```

## Engine API (C#)

```csharp
using ChessEngine.Engine.Polyglot;

var book = PolyglotBook.Load(PolyglotBook.DefaultBookPath());
var moves = book.Probe(position); // IReadOnlyList<PolyglotEntry>
var uci = PolyglotMove.ToUci(moves[0].EncodedMove);
ulong key = PolyglotHash.Compute(position);
```

Book keys use **Polyglot Zobrist**, not `Position.Hash`.

## GitHub Pages / WASM

`scripts/build_pages.py` copies `performance.bin` to `_site/books/` and `ui/static/books/`. The WASM worker fetches it on startup and calls `BrowserApi.ConfigureOpeningBook`.
