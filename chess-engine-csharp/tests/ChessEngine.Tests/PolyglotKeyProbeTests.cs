using ChessEngine.Engine.Polyglot;
using ChessEngine.Rules;

namespace ChessEngine.Tests;

public class PolyglotKeyProbeTests
{
    [Fact]
    public void After_e4_key_matches_python_reference()
    {
        var pos = Position.FromFen(
            "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
        Assert.Equal(0x823c9b50fd114196UL, PolyglotHash.Compute(pos));
    }
}
