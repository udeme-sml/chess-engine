using ChessEngine.Engine.Polyglot;
using ChessEngine.Rules;

namespace ChessEngine.Engine;

/// <summary>
/// Public engine API — UI and UCI should call only through this type.
/// </summary>
public static class EngineApi
{
    private static PolyglotBook? _book;
    private static bool _skipFileBook;

    /// <summary>Load opening book from raw bytes (browser WASM). Disables file-based book lookup.</summary>
    public static void SetBookData(byte[]? data)
    {
        _skipFileBook = true;
        _book = data is { Length: > 0 } ? PolyglotBook.Load(data) : null;
    }

    private static PolyglotBook? Book
    {
        get
        {
            if (_book is not null)
                return _book;
            if (_skipFileBook)
                return null;
            var path = PolyglotBook.DefaultBookPath();
            if (!File.Exists(path))
                return null;
            _book = PolyglotBook.Load(path);
            return _book;
        }
    }

    public static Move FindBestMove(Position position, int timeLimitMs, int maxDepth)
    {
        _ = timeLimitMs;

        var book = Book;
        if (book is not null)
        {
            var entries = book.Probe(position);
            if (entries.Count > 0)
            {
                var entry = entries[Random.Shared.Next(entries.Count)];
                if (PolyglotMove.TryResolve(position, entry.EncodedMove, out var bookMove))
                    return bookMove;
            }
        }

        return Search.FindBestMove(position, maxDepth);
    }

    public static int Evaluate(Position position) => Eval.Evaluate(position);
}
