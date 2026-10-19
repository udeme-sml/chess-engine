namespace ChessEngine.Rules;

public static class MoveGen
{
    private static void AddPromotions(List<Move> moves, int fromSq, int toSq)
    {
        foreach (var promo in new[]
                 {
                     ChessConstants.PromoQueen, ChessConstants.PromoRook, ChessConstants.PromoBishop,
                     ChessConstants.PromoKnight,
                 })
            moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Promotion, promo));
    }

    public static List<Move> GeneratePseudoLegalMoves(Position pos, bool capturesOnly = false)
    {
        var moves = new List<Move>(64);
        var us = pos.Stm;
        var them = us == Color.White ? Color.Black : Color.White;
        var board = pos.Board;
        var ep = pos.EpSq;

        for (var fromSq = 0; fromSq < 64; fromSq++)
        {
            var piece = board[fromSq];
            if (piece == 0 || ChessConstants.PieceColor(piece) != us)
                continue;
            var pt = ChessConstants.GetPieceType(piece);

            if (pt == PieceType.Pawn)
            {
                var step = us == Color.White ? 8 : -8;
                var startRank = us == Color.White ? 1 : 6;
                var promoRank = us == Color.White ? 7 : 0;

                var toSq = fromSq + step;
                if (Square.OnBoard(toSq) && board[toSq] == 0)
                {
                    if (Square.RankOf(toSq) == promoRank)
                    {
                        if (!capturesOnly)
                            AddPromotions(moves, fromSq, toSq);
                    }
                    else if (!capturesOnly)
                    {
                        moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Quiet));
                        var to2 = fromSq + 2 * step;
                        if (Square.RankOf(fromSq) == startRank && Square.OnBoard(to2) && board[to2] == 0)
                            moves.Add(Move.Pack(fromSq, to2, MoveFlag.DoublePawn));
                    }
                }

                foreach (var delta in new[] { step - 1, step + 1 })
                {
                    toSq = fromSq + delta;
                    if (!Square.OnBoard(toSq) || Math.Abs(Square.FileOf(toSq) - Square.FileOf(fromSq)) != 1)
                        continue;
                    var target = board[toSq];
                    if (target != 0 && ChessConstants.PieceColor(target) == them)
                    {
                        if (Square.RankOf(toSq) == promoRank)
                            AddPromotions(moves, fromSq, toSq);
                        else
                            moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Capture));
                    }
                    else if (toSq == ep)
                    {
                        if (Square.RankOf(toSq) == promoRank)
                            AddPromotions(moves, fromSq, toSq);
                        else
                            moves.Add(Move.Pack(fromSq, toSq, MoveFlag.EnPassant));
                    }
                }
            }
            else if (pt == PieceType.Knight)
            {
                foreach (var delta in new[] { -17, -15, -10, -6, 6, 10, 15, 17 })
                {
                    var toSq = fromSq + delta;
                    if (!Square.OnBoard(toSq) || Math.Abs(Square.FileOf(toSq) - Square.FileOf(fromSq)) > 2)
                        continue;
                    var target = board[toSq];
                    if (target == 0)
                    {
                        if (!capturesOnly)
                            moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Quiet));
                    }
                    else if (ChessConstants.PieceColor(target) == them)
                        moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Capture));
                }
            }
            else if (pt == PieceType.King)
            {
                foreach (var delta in new[] { -9, -8, -7, -1, 1, 7, 8, 9 })
                {
                    var toSq = fromSq + delta;
                    if (!Square.OnBoard(toSq) || Math.Abs(Square.FileOf(toSq) - Square.FileOf(fromSq)) > 1)
                        continue;
                    var target = board[toSq];
                    if (target == 0)
                    {
                        if (!capturesOnly)
                            moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Quiet));
                    }
                    else if (ChessConstants.PieceColor(target) == them)
                        moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Capture));
                }

                if (!capturesOnly)
                    GenCastling(pos, moves, fromSq, us);
            }
            else if (pt is PieceType.Bishop or PieceType.Rook or PieceType.Queen)
            {
                var deltas = new List<int>();
                if (pt is PieceType.Bishop or PieceType.Queen)
                    deltas.AddRange([-9, -7, 7, 9]);
                if (pt is PieceType.Rook or PieceType.Queen)
                    deltas.AddRange([-8, -1, 1, 8]);

                foreach (var delta in deltas)
                {
                    var toSq = fromSq + delta;
                    while (Square.OnBoard(toSq))
                    {
                        if (delta == 1 && Square.FileOf(toSq) == 0)
                            break;
                        if (delta == -1 && Square.FileOf(toSq) == 7)
                            break;
                        if (delta is -9 or 7 && Square.FileOf(toSq) == 7)
                            break;
                        if (delta is -7 or 9 && Square.FileOf(toSq) == 0)
                            break;

                        var target = board[toSq];
                        if (target == 0)
                        {
                            if (!capturesOnly)
                                moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Quiet));
                        }
                        else
                        {
                            if (ChessConstants.PieceColor(target) == them)
                                moves.Add(Move.Pack(fromSq, toSq, MoveFlag.Capture));
                            break;
                        }
                        toSq += delta;
                    }
                }
            }
        }

        return moves;
    }

    private static void GenCastling(Position pos, List<Move> moves, int kingSq, Color us)
    {
        if (Attacks.InCheck(pos))
            return;

        var rights = pos.Castling;
        var board = pos.Board;
        var them = us == Color.White ? Color.Black : Color.White;

        if (us == Color.White)
        {
            if ((rights & CastlingRights.WhiteKing) != 0)
            {
                if (board[5] == 0 && board[6] == 0 &&
                    board[7] == ChessConstants.MakePiece(Color.White, PieceType.Rook) &&
                    !Attacks.SqAttackedBy(pos, 5, them) &&
                    !Attacks.SqAttackedBy(pos, 6, them))
                    moves.Add(Move.Pack(kingSq, 6, MoveFlag.CastleK));
            }
            if ((rights & CastlingRights.WhiteQueen) != 0)
            {
                if (board[1] == 0 && board[2] == 0 && board[3] == 0 &&
                    board[0] == ChessConstants.MakePiece(Color.White, PieceType.Rook) &&
                    !Attacks.SqAttackedBy(pos, 2, them) &&
                    !Attacks.SqAttackedBy(pos, 3, them))
                    moves.Add(Move.Pack(kingSq, 2, MoveFlag.CastleQ));
            }
        }
        else
        {
            if ((rights & CastlingRights.BlackKing) != 0)
            {
                if (board[61] == 0 && board[62] == 0 &&
                    board[63] == ChessConstants.MakePiece(Color.Black, PieceType.Rook) &&
                    !Attacks.SqAttackedBy(pos, 61, them) &&
                    !Attacks.SqAttackedBy(pos, 62, them))
                    moves.Add(Move.Pack(kingSq, 62, MoveFlag.CastleK));
            }
            if ((rights & CastlingRights.BlackQueen) != 0)
            {
                if (board[57] == 0 && board[58] == 0 && board[59] == 0 &&
                    board[56] == ChessConstants.MakePiece(Color.Black, PieceType.Rook) &&
                    !Attacks.SqAttackedBy(pos, 58, them) &&
                    !Attacks.SqAttackedBy(pos, 59, them))
                    moves.Add(Move.Pack(kingSq, 58, MoveFlag.CastleQ));
            }
        }
    }

    private static List<Move> LegalFilter(Position pos, List<Move> pseudo)
    {
        var legal = new List<Move>(pseudo.Count);
        foreach (var m in pseudo)
        {
            pos.MakeMove(m);
            if (!Attacks.MoverInCheckAfter(pos))
                legal.Add(m);
            pos.UnmakeMove();
        }
        return legal;
    }

    public static List<Move> GenerateLegalMoves(Position pos) =>
        LegalFilter(pos, GeneratePseudoLegalMoves(pos, capturesOnly: false));

    public static List<Move> GenerateCaptures(Position pos)
    {
        var pseudo = GeneratePseudoLegalMoves(pos, capturesOnly: true);
        var full = GeneratePseudoLegalMoves(pos, capturesOnly: false);
        var promoMoves = full.Where(m => m.IsPromotion()).ToList();
        var seen = new HashSet<uint>(pseudo.Select(m => m.Data));
        var combined = new List<Move>(pseudo);
        foreach (var m in promoMoves)
        {
            if (seen.Add(m.Data))
                combined.Add(m);
        }
        return LegalFilter(pos, combined);
    }

    public static List<Move> GenerateLegalMovesCopy(Position pos) => GenerateLegalMoves(pos);
}
