using ChessEngine.Engine;
using ChessEngine.Engine.Polyglot;
using ChessEngine.Rules;

namespace ChessEngine.Tests;

public class PolyglotTests
{
    private static string RepoBookPath()
    {
        var dir = AppContext.BaseDirectory;
        for (var i = 0; i < 10; i++)
        {
            var candidate = Path.GetFullPath(Path.Combine(dir, "..", "..", "..", "..", "..", "..", "data", "books", "performance.bin"));
            if (File.Exists(candidate))
                return candidate;
            dir = Path.GetDirectoryName(dir) ?? dir;
        }
        throw new FileNotFoundException("performance.bin not found under data/books/");
    }

    [Fact]
    public void Start_position_polyglot_key()
    {
        var pos = Position.FromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        Assert.Equal(0x463b96181691fc9cUL, PolyglotHash.Compute(pos));
    }

    [Fact]
    public void Performance_book_has_start_moves()
    {
        var book = PolyglotBook.Load(RepoBookPath());
        var pos = Position.FromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        var entries = book.Probe(pos);
        Assert.NotEmpty(entries);
        var ucis = entries.Select(e => PolyglotMove.ToUci(e.EncodedMove)).ToHashSet();
        Assert.Contains("e2e4", ucis);
        Assert.Contains("d2d4", ucis);
        foreach (var e in entries)
            Assert.True(PolyglotMove.TryResolve(pos, e.EncodedMove, out _));
    }

    [Fact]
    public void Book_file_is_sorted()
    {
        var book = PolyglotBook.Load(RepoBookPath());
        Assert.True(book.Count > 1000);
    }

    [Fact]
    public void Load_from_bytes_matches_file()
    {
        var path = RepoBookPath();
        var fromFile = PolyglotBook.Load(path);
        var fromBytes = PolyglotBook.Load(File.ReadAllBytes(path));
        Assert.Equal(fromFile.Count, fromBytes.Count);
    }

    [Fact]
    public void EngineApi_picks_book_move_after_1_e4_as_black()
    {
        Environment.SetEnvironmentVariable(PolyglotBook.BookPathEnvironmentVariable, RepoBookPath());
        var pos = Position.FromFen(
            "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
        var uci = MoveUci.ToUci(EngineApi.FindBestMove(pos, 0, 4));
        Assert.Contains(uci, new[] { "e7e5", "c7c5" });
    }
}
