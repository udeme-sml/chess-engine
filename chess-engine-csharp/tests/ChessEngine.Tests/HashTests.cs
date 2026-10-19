using ChessEngine.Rules;

namespace ChessEngine.Tests;

public class HashTests
{
    private const string Start = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    [Fact]
    public void Hash_matches_scratch_at_start()
    {
        var pos = Position.FromFen(Start);
        Assert.Equal(
            Zobrist.ComputeHash(pos.Board, pos.Stm, pos.Castling, pos.EpSq),
            pos.Hash);
    }

    [Fact]
    public void Hash_after_random_plies()
    {
        var rng = new Random(123);
        var pos = Position.FromFen(Start);
        for (var i = 0; i < 100; i++)
        {
            Assert.Equal(
                Zobrist.ComputeHash(pos.Board, pos.Stm, pos.Castling, pos.EpSq),
                pos.Hash);
            var moves = MoveGen.GenerateLegalMoves(pos);
            if (moves.Count == 0)
                break;
            pos.MakeMove(moves[rng.Next(moves.Count)]);
        }
        for (var i = 0; i < 100; i++)
        {
            if (pos.UndoStack.Count == 0)
                break;
            pos.UnmakeMove();
            Assert.Equal(
                Zobrist.ComputeHash(pos.Board, pos.Stm, pos.Castling, pos.EpSq),
                pos.Hash);
        }
    }
}
