using ChessEngine.Rules;

namespace ChessEngine.Tests;

public class PerftTests
{
    private const string Start = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    private const string Kiwi = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    private const string Pos3 = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
    private const string Pos4 = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";

    public static TheoryData<string, int, long> PerftCases => new()
    {
        { Start, 1, 20 },
        { Start, 2, 400 },
        { Start, 3, 8902 },
        { Start, 4, 197281 },
        { Start, 5, 4865609 },
        { Kiwi, 1, 48 },
        { Kiwi, 2, 2039 },
        { Kiwi, 3, 97862 },
        { Kiwi, 4, 4085603 },
        { Pos3, 1, 14 },
        { Pos3, 2, 191 },
        { Pos3, 3, 2812 },
        { Pos3, 4, 43238 },
        { Pos3, 5, 674624 },
        { Pos4, 1, 6 },
        { Pos4, 2, 264 },
        { Pos4, 3, 9467 },
        { Pos4, 4, 422333 },
    };

    [Theory]
    [MemberData(nameof(PerftCases))]
    public void Perft_matches_reference(string fen, int depth, long expected)
    {
        var pos = Position.FromFen(fen);
        Assert.Equal(expected, Perft.PerftCount(pos, depth));
    }
}
