using ChessEngine.Rules;

namespace ChessEngine.Engine.Polyglot;

public static class PolyglotMove
{
    public static int FromSquare(ushort encoded) => (encoded >> 6) & 63;

    public static int ToSquare(ushort encoded) => encoded & 63;

    public static int PromotionField(ushort encoded) => (encoded >> 12) & 7;

    public static string ToUci(ushort encoded)
    {
        var from = FromSquare(encoded);
        var to = ToSquare(encoded);
        var promo = PromotionField(encoded);
        var uci = Square.SquareName(from) + Square.SquareName(to);
        if (promo != 0)
            uci += PromoChar(promo);
        return uci;
    }

    /// <summary>Match a book move against legal moves (flags/promo must agree).</summary>
    public static bool TryResolve(Position position, ushort encoded, out Move move)
    {
        var uci = ToUci(encoded);
        var legal = MoveGen.GenerateLegalMoves(position);
        try
        {
            move = MoveUci.FromUci(uci, legal);
            return true;
        }
        catch (ArgumentException)
        {
            move = Move.Null;
            return false;
        }
    }

    private static char PromoChar(int polyglotPromo) => polyglotPromo switch
    {
        1 => 'n',
        2 => 'b',
        3 => 'r',
        4 => 'q',
        _ => '\0',
    };
}
