namespace ChessEngine.Rules;

public enum GameResult
{
    Ongoing,
    Checkmate,
    Stalemate,
    Threefold,
    FiftyMove,
    InsufficientMaterial,
}

public static class Game
{
    public static int CountRepetition(Position pos) =>
        pos.HashHistory.Count(h => h == pos.Hash);

    public static bool HasInsufficientMaterial(Position pos)
    {
        var board = pos.Board;
        var white = new List<PieceType>();
        var black = new List<PieceType>();
        var whiteBishopSquares = new List<int>();
        var blackBishopSquares = new List<int>();

        for (var sq = 0; sq < 64; sq++)
        {
            var piece = board[sq];
            if (piece == 0)
                continue;
            var pt = ChessConstants.GetPieceType(piece);
            var color = (piece >> 3) & 1;
            if (pt == PieceType.King)
                continue;
            if (pt is PieceType.Pawn or PieceType.Rook or PieceType.Queen)
                return false;
            if (color == 0)
            {
                white.Add(pt);
                if (pt == PieceType.Bishop)
                    whiteBishopSquares.Add(sq);
            }
            else
            {
                black.Add(pt);
                if (pt == PieceType.Bishop)
                    blackBishopSquares.Add(sq);
            }
        }

        if (white.Count == 0 && black.Count == 0)
            return true;
        if ((white.Count == 1 && white[0] == PieceType.Bishop && black.Count == 0) ||
            (white.Count == 1 && white[0] == PieceType.Knight && black.Count == 0))
            return true;
        if ((black.Count == 1 && black[0] == PieceType.Bishop && white.Count == 0) ||
            (black.Count == 1 && black[0] == PieceType.Knight && white.Count == 0))
            return true;
        if (white.Count == 1 && white[0] == PieceType.Bishop && black.Count == 1 && black[0] == PieceType.Bishop)
        {
            if ((whiteBishopSquares[0] ^ blackBishopSquares[0]) % 2 == 0)
                return true;
        }
        return false;
    }

    public static bool SideInCheck(Position pos) => Attacks.InCheck(pos);

    public static GameResult GetResult(Position pos)
    {
        if (CountRepetition(pos) >= 3)
            return GameResult.Threefold;
        if (pos.Halfmove >= 100)
            return GameResult.FiftyMove;
        if (HasInsufficientMaterial(pos))
            return GameResult.InsufficientMaterial;

        var moves = MoveGen.GenerateLegalMoves(pos);
        if (moves.Count > 0)
            return GameResult.Ongoing;
        return SideInCheck(pos) ? GameResult.Checkmate : GameResult.Stalemate;
    }
}
