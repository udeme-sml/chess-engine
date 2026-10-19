namespace ChessEngine.Rules;

public static class Attacks
{
    public static bool SqAttackedBy(Position pos, int sq, Color byColor)
    {
        var board = pos.Board;

        if (byColor == Color.White)
        {
            foreach (var delta in new[] { -9, -7 })
            {
                var a = sq + delta;
                if (Square.OnBoard(a) && Math.Abs(Square.FileOf(a) - Square.FileOf(sq)) == 1)
                {
                    if (board[a] == ChessConstants.WPawn)
                        return true;
                }
            }
        }
        else
        {
            foreach (var delta in new[] { 7, 9 })
            {
                var a = sq + delta;
                if (Square.OnBoard(a) && Math.Abs(Square.FileOf(a) - Square.FileOf(sq)) == 1)
                {
                    if (board[a] == ChessConstants.BPawn)
                        return true;
                }
            }
        }

        foreach (var delta in new[] { -17, -15, -10, -6, 6, 10, 15, 17 })
        {
            var a = sq + delta;
            if (Square.OnBoard(a) && Math.Abs(Square.FileOf(a) - Square.FileOf(sq)) <= 2)
            {
                var p = board[a];
                if (p != 0 && ChessConstants.GetPieceType(p) == PieceType.Knight && ChessConstants.PieceColor(p) == byColor)
                    return true;
            }
        }

        foreach (var delta in new[] { -9, -8, -7, -1, 1, 7, 8, 9 })
        {
            var a = sq + delta;
            if (Square.OnBoard(a) && Math.Abs(Square.FileOf(a) - Square.FileOf(sq)) <= 1)
            {
                var p = board[a];
                if (p != 0 && ChessConstants.GetPieceType(p) == PieceType.King && ChessConstants.PieceColor(p) == byColor)
                    return true;
            }
        }

        foreach (var delta in new[] { -9, -7, 7, 9 })
        {
            var a = sq + delta;
            while (Square.OnBoard(a))
            {
                if (delta is -9 or 7 && Square.FileOf(a) == 7)
                    break;
                if (delta is -7 or 9 && Square.FileOf(a) == 0)
                    break;
                var p = board[a];
                if (p != 0)
                {
                    if (ChessConstants.PieceColor(p) == byColor &&
                        ChessConstants.GetPieceType(p) is PieceType.Bishop or PieceType.Queen)
                        return true;
                    break;
                }
                a += delta;
            }
        }

        foreach (var delta in new[] { -8, -1, 1, 8 })
        {
            var a = sq + delta;
            while (Square.OnBoard(a))
            {
                if (delta == 1 && Square.FileOf(a) == 0)
                    break;
                if (delta == -1 && Square.FileOf(a) == 7)
                    break;
                var p = board[a];
                if (p != 0)
                {
                    if (ChessConstants.PieceColor(p) == byColor &&
                        ChessConstants.GetPieceType(p) is PieceType.Rook or PieceType.Queen)
                        return true;
                    break;
                }
                a += delta;
            }
        }

        return false;
    }

    public static bool InCheck(Position pos, Color? color = null)
    {
        var us = color ?? pos.Stm;
        var kingSq = pos.KingSq[(int)us];
        var them = us == Color.White ? Color.Black : Color.White;
        return SqAttackedBy(pos, kingSq, them);
    }

    public static bool MoverInCheckAfter(Position pos)
    {
        var them = pos.Stm;
        var us = them == Color.White ? Color.Black : Color.White;
        return InCheck(pos, us);
    }
}
