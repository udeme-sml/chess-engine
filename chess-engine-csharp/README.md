# Chess Engine (C#)

C# search and evaluation for the parent repo. Same rules layer (64-square array, packed moves, Zobrist hashing, negamax + material/PST eval) with perft and hash tests aligned to the Python `rules/` package.

## Requirements

- [.NET 9 SDK](https://dotnet.microsoft.com/download) or newer

## Build and test

```bash
cd chess-engine-csharp
dotnet test
```

## Run UCI engine

```bash
dotnet run --project src/ChessEngine.Uci
```

Pipe UCI commands on stdin (e.g. `uci`, `isready`, `position startpos`, `go depth 4`).

## Layout

| Project | Role |
|---------|------|
| `ChessEngine.Rules` | Board, FEN, movegen, attacks, game outcome, perft |
| `ChessEngine.Engine` | Evaluation, negamax search, `EngineApi` |
| `ChessEngine.Uci` | UCI console wrapper |
| `ChessEngine.Tests` | Perft and Zobrist tests (parity with Python `tests/`) |

## Performance

Search uses the same algorithm as Python but benefits from JIT/AOT and value types. For maximum throughput, build Release and consider `Span<T>` move lists, transposition tables, and bitboards as follow-ups.

## Play in the web UI (local server)

1. Build the UCI executable once:

   ```bash
   cd chess-engine-csharp
   dotnet build -c Release
   ```

2. From the repo root, start the Python UI server (it auto-detects the C# DLL):

   ```bash
   python -m ui.server
   ```

3. Open http://127.0.0.1:8765/ and click **New game vs engine**.

The server and the static site both use the C# engine only (UCI subprocess for `python -m ui.server`, WebAssembly for GitHub Pages / `_site`). Build the UCI DLL and the browser bundle:

```bash
cd chess-engine-csharp
dotnet build -c Release
dotnet publish -c Release src/ChessEngine.Browser/ChessEngine.Browser.csproj
```

`python scripts/build_pages.py` publishes the WASM `AppBundle` into `_site/csharp-engine/`.
