using ChessEngine.Engine;
using ChessEngine.Rules;

namespace ChessEngine.Tests;

public class SearchTests
{
    [Fact]
    public void FindBestMove_does_not_mutate_position()
    {
        var pos = Position.FromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        var fen = pos.Fen();
        _ = Search.FindBestMove(pos, 4);
        Assert.Equal(fen, pos.Fen());
    }

    [Fact]
    public void Takes_hanging_queen_over_pawn_push()
    {
        var pos = Position.FromFen(
            "rnbqkb1/pppp1ppp/5n2/4p2Q/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 1 3");
        var uci = MoveUci.ToUci(Search.FindBestMove(pos, 4));
        Assert.Equal("f6h5", uci);
    }
}
