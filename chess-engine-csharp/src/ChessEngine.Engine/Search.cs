using System.Diagnostics;
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

    private const int LmrTableSize = 64;
    private const int LmrFullDepthMoves = 4;
    private const int LmrMinDepth = 3;

    private static readonly int[,] LmrTable = BuildLmrTable();

    private static int[,] BuildLmrTable()
    {
        var table = new int[LmrTableSize, LmrTableSize];
        for (var depth = 1; depth < LmrTableSize; depth++)
        {
            for (var moveNumber = 1; moveNumber < LmrTableSize; moveNumber++)
                table[depth, moveNumber] = (int)Math.Round(Math.Log(depth) * Math.Log(moveNumber) / 2.25);
        }

        return table;
    }

    /// <summary>
    /// Late-move reduction in plies (0 = search at full depth). Caller searches at <c>depth - 1 - R</c>.
    /// </summary>
    /// <param name="moveIndex">0-based index in the ordered move list at this node.</param>
    /// <param name="nodeInCheck">Side to move was in check at this node (before <paramref name="move"/>).</param>
    /// <param name="givesCheck">Whether <paramref name="move"/> gives check (after make).</param>
    public static int ComputeReduction(
        int depth,
        int moveIndex,
        Move move,
        bool nodeInCheck,
        bool givesCheck)
    {
        if (depth < LmrMinDepth
            || moveIndex < LmrFullDepthMoves
            || move.IsCapture()
            || move.IsPromotion()
            || givesCheck
            || nodeInCheck)
            return 0;

        var d = Math.Clamp(depth, 1, LmrTableSize - 1);
        var m = Math.Clamp(moveIndex + 1, 1, LmrTableSize - 1);
        var reduction = LmrTable[d, m];
        return Math.Clamp(reduction, 0, depth - 1);
    }

    public static int Negamax(Position position, int depth, int alpha, int beta, bool allowNull = true)
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
        if (depth <= 0)
            return Quiescence(position, alpha, beta);

        const int NullMoveReduction = 3;
        if (moves.Count > 1
            && allowNull
            && depth >= 3
            && depth - 1 - NullMoveReduction >= 0
            && !Attacks.InCheck(position)
            && position.HasNonPawns())
        {
            position.MakeNullMove();
            var score = -Negamax(position, depth - 1 - NullMoveReduction, -beta, -beta + 1, allowNull: false);
            position.UnmakeNullMove();
            if (score >= beta)
                return beta;
        }
        
        OrderMoves(position, moves, hashMove);

        var nodeInCheck = Attacks.InCheck(position);
        var moveIndex = 0;
        var bestScore = ScoreMin;
        Move? bestMove = null;

        foreach (var move in moves)
        {
            position.MakeMove(move);

            var givesCheck = Attacks.InCheck(position);
            var reduction = ComputeReduction(depth, moveIndex, move, nodeInCheck, givesCheck);

            int score;
            if (reduction > 0)
            {
                score = -Negamax(position, depth - 1 - reduction, -(alpha + 1), -alpha);
                if (score > alpha)
                    score = -Negamax(position, depth - 1, -beta, -alpha);
            }
            else
                score = -Negamax(position, depth - 1, -beta, -alpha);

            position.UnmakeMove();
            moveIndex++;

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

    /// <summary>
    /// Iterative deepening to <paramref name="maxDepth"/> (or until <paramref name="timeLimitMs"/> elapses).
    /// </summary>
    public static Move FindBestMove(
        Position position,
        int maxDepth,
        int timeLimitMs = 0,
        int alpha = ScoreMin,
        int beta = ScoreMax)
    {
        TranspositionTable.BeginSearch();

        var moves = MoveGen.GenerateLegalMoves(position);
        if (moves.Count == 0)
            return Move.Null;

        var fenBefore = position.Fen();
        var bestMove = moves[0];
        var bestScore = 0;
        var stopwatch = timeLimitMs > 0 ? Stopwatch.StartNew() : null;

        for (var depth = 1; depth <= maxDepth; depth++)
        {
            if (stopwatch is not null && stopwatch.ElapsedMilliseconds >= timeLimitMs && depth > 1)
                break;

            _ = TranspositionTable.Probe(position.Hash, depth, alpha, beta, out var hashMove);
            OrderMoves(position, moves, hashMove);

            var iterationBest = moves[0];
            var iterationScore = ScoreMin;
            var iterAlpha = alpha;
            foreach (var move in moves)
            {
                position.MakeMove(move);
                var score = -Negamax(position, depth - 1, -beta, -iterAlpha);
                position.UnmakeMove();
                if (score > iterationScore)
                {
                    iterationScore = score;
                    iterationBest = move;
                }

                if (score > iterAlpha)
                    iterAlpha = score;
            }

            bestMove = iterationBest;
            bestScore = iterationScore;

            if (Math.Abs(bestScore) >= MateScore - depth)
                break;

            if (stopwatch is not null && stopwatch.ElapsedMilliseconds >= timeLimitMs)
                break;
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
