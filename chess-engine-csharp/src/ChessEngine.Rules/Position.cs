namespace ChessEngine.Rules;

public sealed class Position
{
    private const int W = 0;
    private const int B = 1;

    private static readonly int[] CastleKRook = [7, 63];
    private static readonly int[] CastleQRook = [0, 56];
    private static readonly int[] CastleKRookTo = [5, 61];
    private static readonly int[] CastleQRookTo = [3, 59];

    public int[] Board { get; }
    public Color Stm { get; set; }
    public CastlingRights Castling { get; set; }
    public int EpSq { get; set; }
    public int Halfmove { get; set; }
    public int Fullmove { get; set; }
    public ulong Hash { get; set; }
    public List<ulong> HashHistory { get; }
    public int[] KingSq { get; }
    public Stack<UndoInfo> UndoStack { get; }

    public Position()
    {
        Board = new int[64];
        Stm = Color.White;
        Castling = CastlingRights.All;
        EpSq = -1;
        Halfmove = 0;
        Fullmove = 1;
        Hash = 0;
        HashHistory = [];
        UndoStack = new Stack<UndoInfo>();
        KingSq = [4, 60];
    }

    public static Position FromFen(string fen)
    {
        var pos = new Position();
        var (board, stm, castling, epSq, halfmove, fullmove) = FenCodec.ParseFen(fen);
        Array.Copy(board, pos.Board, 64);
        pos.Stm = stm;
        pos.Castling = castling;
        pos.EpSq = epSq;
        pos.Halfmove = halfmove;
        pos.Fullmove = fullmove;
        pos.RefreshKingSq();
        pos.Hash = Zobrist.ComputeHash(pos.Board, pos.Stm, pos.Castling, pos.EpSq);
        pos.HashHistory.Clear();
        pos.HashHistory.Add(pos.Hash);
        return pos;
    }

    public string Fen() => FenCodec.ToFen(Board, Stm, Castling, EpSq, Halfmove, Fullmove);

    private void RefreshKingSq()
    {
        foreach (Color color in Enum.GetValues<Color>())
        {
            var kingPiece = ChessConstants.MakePiece(color, PieceType.King);
            for (var sq = 0; sq < 64; sq++)
            {
                if (Board[sq] == kingPiece)
                {
                    KingSq[(int)color] = sq;
                    break;
                }
            }
        }
    }

    public int PieceAt(int sq) => Board[sq];

    /// <summary>
    /// True if <paramref name="color"/> has a knight, bishop, rook, or queen (null-move / zugzwang guard).
    /// </summary>
    public bool HasNonPawns(Color color)
    {
        for (var sq = 0; sq < 64; sq++)
        {
            var piece = Board[sq];
            if (piece == 0 || ChessConstants.PieceColor(piece) != color)
                continue;
            var pt = ChessConstants.GetPieceType(piece);
            if (pt is not PieceType.Pawn and not PieceType.King)
                return true;
        }

        return false;
    }

    public bool HasNonPawns() => HasNonPawns(Stm);

    private int RemovePiece(int sq)
    {
        var piece = Board[sq];
        if (piece != 0)
        {
            Hash ^= Zobrist.HashPiece(piece, sq);
            Board[sq] = 0;
        }
        return piece;
    }

    private void PutPiece(int piece, int sq)
    {
        Board[sq] = piece;
        if (piece != 0)
            Hash ^= Zobrist.HashPiece(piece, sq);
    }

    private void MovePiece(int fromSq, int toSq)
    {
        var piece = RemovePiece(fromSq);
        PutPiece(piece, toSq);
    }

    public void MakeMove(Move move)
    {
        var us = Stm;
        var them = us == Color.White ? Color.Black : Color.White;
        var fromSq = move.FromSq;
        var toSq = move.ToSq;
        var flag = move.Flag;
        var promo = move.Promo;

        var piece = Board[fromSq];
        if (piece == 0)
            throw new InvalidOperationException($"make_move: empty from square {fromSq}");

        var undo = new UndoInfo
        {
            Move = move,
            Captured = 0,
            CapturedSq = toSq,
            Castling = Castling,
            EpSq = EpSq,
            Halfmove = Halfmove,
            Hash = Hash,
            Fullmove = Fullmove,
            KingSqWhite = KingSq[W],
            KingSqBlack = KingSq[B],
        };

        var oldCastle = Castling;
        var oldEp = EpSq;

        var captured = 0;
        var capturedSq = toSq;

        if (flag == MoveFlag.EnPassant)
        {
            capturedSq = toSq + (us == Color.White ? -8 : 8);
            captured = RemovePiece(capturedSq);
        }
        else if (flag is MoveFlag.Capture or MoveFlag.Promotion)
        {
            captured = RemovePiece(toSq);
        }
        else if (Board[toSq] != 0)
        {
            captured = RemovePiece(toSq);
        }

        undo.Captured = captured;
        undo.CapturedSq = capturedSq;

        if (ChessConstants.GetPieceType(piece) == PieceType.Pawn || captured != 0)
            Halfmove = 0;
        else
            Halfmove++;

        var newCastle = Castling;
        if (ChessConstants.GetPieceType(piece) == PieceType.King)
        {
            if (us == Color.White)
                newCastle &= ~CastlingRights.White;
            else
                newCastle &= ~CastlingRights.Black;
        }
        if (fromSq is 0 or 7 or 56 or 63)
            newCastle &= ~RookRightForSquare(fromSq);
        if (capturedSq is 0 or 7 or 56 or 63)
            newCastle &= ~RookRightForSquare(capturedSq);

        var newEp = -1;
        if (flag == MoveFlag.DoublePawn)
            newEp = (fromSq + toSq) / 2;

        RemovePiece(fromSq);

        if (flag == MoveFlag.CastleK)
        {
            PutPiece(ChessConstants.MakePiece(us, PieceType.King), toSq);
            KingSq[(int)us] = toSq;
            var c = (int)us;
            MovePiece(CastleKRook[c], CastleKRookTo[c]);
        }
        else if (flag == MoveFlag.CastleQ)
        {
            PutPiece(ChessConstants.MakePiece(us, PieceType.King), toSq);
            KingSq[(int)us] = toSq;
            var c = (int)us;
            MovePiece(CastleQRook[c], CastleQRookTo[c]);
        }
        else if (flag == MoveFlag.Promotion || promo != ChessConstants.PromoNone)
        {
            var promoType = promo switch
            {
                ChessConstants.PromoQueen => PieceType.Queen,
                ChessConstants.PromoRook => PieceType.Rook,
                ChessConstants.PromoBishop => PieceType.Bishop,
                ChessConstants.PromoKnight => PieceType.Knight,
                _ => throw new InvalidOperationException($"invalid promotion id {promo}"),
            };
            PutPiece(ChessConstants.MakePiece(us, promoType), toSq);
        }
        else
        {
            PutPiece(piece, toSq);
            if (ChessConstants.GetPieceType(piece) == PieceType.King)
                KingSq[(int)us] = toSq;
        }

        if (oldCastle != newCastle)
        {
            Hash ^= Zobrist.HashCastling(oldCastle);
            Hash ^= Zobrist.HashCastling(newCastle);
            Castling = newCastle;
        }

        if (oldEp != newEp)
        {
            if (oldEp >= 0)
                Hash ^= Zobrist.HashEpFile(oldEp & 7);
            if (newEp >= 0)
                Hash ^= Zobrist.HashEpFile(newEp & 7);
            EpSq = newEp;
        }

        Hash ^= ZobristKeys.SideKey;
        Stm = them;
        if (us == Color.Black)
            Fullmove++;

        UndoStack.Push(undo);
        HashHistory.Add(Hash);
    }

    /// <summary>Pass the turn (search-only). Pair with <see cref="UnmakeNullMove"/>.</summary>
    public void MakeNullMove()
    {
        var us = Stm;
        var undo = new UndoInfo
        {
            IsNullMove = true,
            Move = Move.Null,
            Castling = Castling,
            EpSq = EpSq,
            Halfmove = Halfmove,
            Hash = Hash,
            Fullmove = Fullmove,
            KingSqWhite = KingSq[W],
            KingSqBlack = KingSq[B],
        };

        var oldEp = EpSq;
        Halfmove++;

        if (oldEp >= 0)
        {
            Hash ^= Zobrist.HashEpFile(oldEp & 7);
            EpSq = -1;
        }

        Hash ^= ZobristKeys.SideKey;
        Stm = us == Color.White ? Color.Black : Color.White;
        if (us == Color.Black)
            Fullmove++;

        UndoStack.Push(undo);
        HashHistory.Add(Hash);
    }

    public void UnmakeNullMove()
    {
        if (UndoStack.Count == 0)
            throw new InvalidOperationException("unmake_null_move: empty stack");

        var undo = UndoStack.Pop();
        if (!undo.IsNullMove)
            throw new InvalidOperationException("unmake_null_move: top of stack is not a null move");

        HashHistory.RemoveAt(HashHistory.Count - 1);

        Stm = Stm == Color.White ? Color.Black : Color.White;
        Hash = undo.Hash;
        Castling = undo.Castling;
        EpSq = undo.EpSq;
        Halfmove = undo.Halfmove;
        Fullmove = undo.Fullmove;
        KingSq[W] = undo.KingSqWhite;
        KingSq[B] = undo.KingSqBlack;
    }

    public void UnmakeMove()
    {
        if (UndoStack.Count == 0)
            throw new InvalidOperationException("unmake_move: empty stack");

        var undo = UndoStack.Pop();
        if (undo.IsNullMove)
            throw new InvalidOperationException("unmake_move: null move on stack; use UnmakeNullMove");

        HashHistory.RemoveAt(HashHistory.Count - 1);

        var move = undo.Move;
        var us = Stm == Color.White ? Color.Black : Color.White;
        Stm = us;
        Hash = undo.Hash;
        Castling = undo.Castling;
        EpSq = undo.EpSq;
        Halfmove = undo.Halfmove;
        Fullmove = undo.Fullmove;
        KingSq[W] = undo.KingSqWhite;
        KingSq[B] = undo.KingSqBlack;

        var fromSq = move.FromSq;
        var toSq = move.ToSq;
        var flag = move.Flag;
        var promo = move.Promo;

        if (flag == MoveFlag.CastleK)
        {
            var c = (int)us;
            Board[toSq] = 0;
            Board[CastleKRookTo[c]] = 0;
            Board[fromSq] = ChessConstants.MakePiece(us, PieceType.King);
            Board[CastleKRook[c]] = ChessConstants.MakePiece(us, PieceType.Rook);
        }
        else if (flag == MoveFlag.CastleQ)
        {
            var c = (int)us;
            Board[toSq] = 0;
            Board[CastleQRookTo[c]] = 0;
            Board[fromSq] = ChessConstants.MakePiece(us, PieceType.King);
            Board[CastleQRook[c]] = ChessConstants.MakePiece(us, PieceType.Rook);
        }
        else if (flag == MoveFlag.EnPassant)
        {
            Board[toSq] = 0;
            Board[undo.CapturedSq] = undo.Captured;
            Board[fromSq] = ChessConstants.MakePiece(us, PieceType.Pawn);
        }
        else if (flag == MoveFlag.Promotion || promo != ChessConstants.PromoNone)
        {
            Board[toSq] = undo.Captured;
            Board[fromSq] = ChessConstants.MakePiece(us, PieceType.Pawn);
        }
        else
        {
            var pieceOnTo = Board[toSq];
            Board[toSq] = undo.Captured;
            Board[fromSq] = pieceOnTo;
        }
    }

    private static CastlingRights RookRightForSquare(int sq) => sq switch
    {
        0 => CastlingRights.WhiteQueen,
        7 => CastlingRights.WhiteKing,
        56 => CastlingRights.BlackQueen,
        63 => CastlingRights.BlackKing,
        _ => CastlingRights.None,
    };
}
