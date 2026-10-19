namespace ChessEngine.Rules;

public enum Color : byte
{
    White = 0,
    Black = 1,
}

public enum PieceType : byte
{
    Empty = 0,
    Pawn = 1,
    Knight = 2,
    Bishop = 3,
    Rook = 4,
    Queen = 5,
    King = 6,
}

[Flags]
public enum CastlingRights : byte
{
    None = 0,
    WhiteKing = 1,
    WhiteQueen = 2,
    BlackKing = 4,
    BlackQueen = 8,
    White = WhiteKing | WhiteQueen,
    Black = BlackKing | BlackQueen,
    All = White | Black,
}

public enum MoveFlag : byte
{
    Quiet = 0,
    Capture = 1,
    DoublePawn = 2,
    EnPassant = 3,
    CastleK = 4,
    CastleQ = 5,
    Promotion = 6,
}

public static class ChessConstants
{
    public const int NumSquares = 64;

    public const int PromoNone = 0;
    public const int PromoQueen = 1;
    public const int PromoRook = 2;
    public const int PromoBishop = 3;
    public const int PromoKnight = 4;

    public const int WPawn = 1;
    public const int WKnight = 2;
    public const int WBishop = 3;
    public const int WRook = 4;
    public const int WQueen = 5;
    public const int WKing = 6;

    public const int BPawn = 9;
    public const int BKnight = 10;
    public const int BBishop = 11;
    public const int BRook = 12;
    public const int BQueen = 13;
    public const int BKing = 14;

    public static int MakePiece(Color color, PieceType pieceType) =>
        pieceType == PieceType.Empty ? 0 : ((int)color << 3) | (int)pieceType;

    public static Color PieceColor(int piece) => (Color)((piece >> 3) & 1);

    public static PieceType GetPieceType(int piece) => (PieceType)(piece & 7);
}
