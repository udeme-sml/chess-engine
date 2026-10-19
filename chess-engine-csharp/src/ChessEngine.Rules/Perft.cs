namespace ChessEngine.Rules;

public static class Perft
{
    public static long PerftCount(Position pos, int depth)
    {
        if (depth == 0)
            return 1;
        var moves = MoveGen.GenerateLegalMoves(pos);
        if (depth == 1)
            return moves.Count;

        long total = 0;
        foreach (var m in moves)
        {
            pos.MakeMove(m);
            total += PerftCount(pos, depth - 1);
            pos.UnmakeMove();
        }
        return total;
    }

    public static (long Total, List<(string Uci, long Nodes)> Lines) PerftDivide(Position pos, int depth)
    {
        var moves = MoveGen.GenerateLegalMoves(pos);
        var lines = new List<(string, long)>();
        long total = 0;
        foreach (var m in moves)
        {
            pos.MakeMove(m);
            var n = PerftCount(pos, depth - 1);
            pos.UnmakeMove();
            lines.Add((MoveUci.ToUci(m), n));
            total += n;
        }
        return (total, lines);
    }
}
