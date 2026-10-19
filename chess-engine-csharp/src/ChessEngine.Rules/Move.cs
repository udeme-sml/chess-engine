namespace ChessEngine.Rules;

public readonly struct Move : IEquatable<Move>
{
    private const int ShiftFrom = 0;
    private const int ShiftTo = 6;
    private const int ShiftPromo = 12;
    private const int ShiftFlag = 15;

    public readonly uint Data;

    public Move(uint data) => Data = data;

    public static Move Pack(int fromSq, int toSq, MoveFlag flag = MoveFlag.Quiet, int promo = ChessConstants.PromoNone)
    {
        var data =
            (uint)(fromSq & 63)
            | (uint)((toSq & 63) << ShiftTo)
            | (uint)((promo & 7) << ShiftPromo)
            | (uint)(((int)flag & 7) << ShiftFlag);
        return new Move(data);
    }

    public int FromSq => (int)((Data >> ShiftFrom) & 63);
    public int ToSq => (int)((Data >> ShiftTo) & 63);
    public int Promo => (int)((Data >> ShiftPromo) & 7);
    public MoveFlag Flag => (MoveFlag)((Data >> ShiftFlag) & 7);

    public bool IsCapture()
    {
        var f = Flag;
        return f is MoveFlag.Capture or MoveFlag.EnPassant
            || (f == MoveFlag.Promotion && Promo != ChessConstants.PromoNone);
    }

    public bool IsPromotion() => Flag == MoveFlag.Promotion || Promo != ChessConstants.PromoNone;

    public bool Equals(Move other) => Data == other.Data;
    public override bool Equals(object? obj) => obj is Move other && Equals(other);
    public override int GetHashCode() => (int)Data;

    public static readonly Move Null = new(0);
}

public static class MoveUci
{
    private static readonly Dictionary<char, int> CharToPromo = new()
    {
        ['q'] = ChessConstants.PromoQueen,
        ['r'] = ChessConstants.PromoRook,
        ['b'] = ChessConstants.PromoBishop,
        ['n'] = ChessConstants.PromoKnight,
    };

    public static string ToUci(Move m)
    {
        if (m.Data == 0)
            return "0000";
        var s = Square.SquareName(m.FromSq) + Square.SquareName(m.ToSq);
        if (m.Promo != ChessConstants.PromoNone)
            s += PromoChar(m.Promo);
        return s;
    }

    private static char PromoChar(int promo) => promo switch
    {
        ChessConstants.PromoQueen => 'q',
        ChessConstants.PromoRook => 'r',
        ChessConstants.PromoBishop => 'b',
        ChessConstants.PromoKnight => 'n',
        _ => '\0',
    };

    public static Move FromUci(string uci, IReadOnlyList<Move>? legalMoves = null)
    {
        if (uci is "0000" or "null")
            return Move.Null;

        var fromSq = Square.ParseSquare(uci[..2]);
        var toSq = Square.ParseSquare(uci[2..4]);
        var promo = uci.Length > 4 && CharToPromo.TryGetValue(uci[4], out var p) ? p : ChessConstants.PromoNone;

        if (legalMoves is not null)
        {
            foreach (var m in legalMoves)
            {
                if (m.FromSq == fromSq && m.ToSq == toSq && m.Promo == promo)
                    return m;
            }
            throw new ArgumentException($"UCI move not in legal list: {uci}");
        }

        var flag = promo != ChessConstants.PromoNone ? MoveFlag.Promotion : MoveFlag.Quiet;
        return Move.Pack(fromSq, toSq, flag, promo);
    }
}
