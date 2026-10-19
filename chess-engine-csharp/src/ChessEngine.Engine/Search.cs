using ChessEngine.Rules;

namespace ChessEngine.Engine;

public static class Search
{
    public const int MateScore = 30000;
    private const int ScoreMin = -MateScore * 2;
    private const int ScoreMax = MateScore * 2;

    private static readonly int[] PieceValue =
    [
        0,
        100, 320, 330, 500, 900, 0, // white pawn..king (type index)
    ];

    public static int Negamax(Position position, int depth, int alpha, int beta)
    {
        var alphaOrig = alpha;
        var key = position.Hash;

        // TT probe: may return immediately or supply a hash move for ordering.
        var ttScore = TranspositionTable.Probe(key, depth, alpha, beta, out var hashMove);
        if (ttScore is not null)
            return ttScore.Value;

        var moves = MoveGen.GenerateLegalMoves(position);
        if (moves.Count == 0)
            return Attacks.InCheck(position) ? -MateScore : 0;
        if (depth == 0)
            return Quiescence(position, alpha, beta);

        OrderMoves(position, moves, hashMove);

        var bestScore = ScoreMin;
        Move? bestMove = null;
        foreach (var move in moves)
        {
            position.MakeMove(move);
            var score = -Negamax(position, depth - 1, -beta, -alpha);
            position.UnmakeMove();

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }

            if (score > alpha)
                alpha = score;
            if (alpha >= beta)
                break;
        }

        var bound = bestScore <= alphaOrig
            ? TranspositionTable.BoundUpper
            : bestScore >= beta
                ? TranspositionTable.BoundLower
                : TranspositionTable.BoundExact;
        TranspositionTable.Store(key, depth, bestScore, bound, bestMove ?? Move.Null);

        return bestScore;
    }

    public static int Quiescence(Position position, int alpha, int beta)
    {
        var standPat = Eval.Evaluate(position);

        if (standPat >= beta)
            return beta;
        if (standPat > alpha)
            alpha = standPat;

        var captures = MoveGen.GenerateCaptures(position);
        OrderMoves(position, captures, Move.Null);

        if (captures.Count == 0)
            return alpha;
        
        var bestScore = alpha;
        foreach (var move in captures)
        {
            position.MakeMove(move);
            var score = -Quiescence(position, -beta, -alpha);
            position.UnmakeMove();

            if (score >= bestScore)
                bestScore = score;
            if (score > alpha)
                alpha = score;
            if (alpha >= beta)
                break;
        }

        return bestScore;
    }

    public static Move FindBestMove(Position position, int depth, int alpha = ScoreMin, int beta = ScoreMax)
    {
        TranspositionTable.BeginSearch();

        var moves = MoveGen.GenerateLegalMoves(position);
        if (moves.Count == 0)
            return Move.Null;

        var fenBefore = position.Fen();
        _ = TranspositionTable.Probe(position.Hash, depth, alpha, beta, out var hashMove);
        OrderMoves(position, moves, hashMove);

        var bestMove = moves[0];
        var bestScore = ScoreMin;
        foreach (var move in moves)
        {
            position.MakeMove(move);
            var score = -Negamax(position, depth - 1, -beta, -alpha);
            position.UnmakeMove();
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
            if (score > alpha)
                alpha = score;
        }

        if (position.Fen() != fenBefore)
            throw new InvalidOperationException("search left position mutated");

        return bestMove;
    }

    /// <summary>Hash move first, then captures (MVV-LVA), then quiets.</summary>
    private static void OrderMoves(Position position, List<Move> moves, Move hashMove)
    {
        var board = position.Board;
        moves.Sort((a, b) =>
        {
            var sa = MoveOrderScore(position, board, a, hashMove);
            var sb = MoveOrderScore(position, board, b, hashMove);
            return sb.CompareTo(sa);
        });
    }

    private static int MoveOrderScore(Position position, int[] board, Move move, Move hashMove)
    {
        if (hashMove.Data != 0 && move.Data == hashMove.Data)
            return 2_000_000;
        if (!move.IsCapture())
            return 0;

        var attacker = board[move.FromSq];
        var attackerVal = PieceValue[(int)ChessConstants.GetPieceType(attacker)];
        var victimVal = move.Flag == MoveFlag.EnPassant
            ? PieceValue[(int)PieceType.Pawn]
            : PieceValue[(int)ChessConstants.GetPieceType(board[move.ToSq])];
        return 1_000_000 + victimVal * 16 - attackerVal;
    }
}
