namespace ChessEngine.Rules;

public sealed class UndoInfo
{
    public bool IsNullMove { get; init; }
    public required Move Move { get; init; }
    public int Captured { get; set; }
    public int CapturedSq { get; set; }
    public CastlingRights Castling { get; init; }
    public int EpSq { get; init; }
    public int Halfmove { get; init; }
    public ulong Hash { get; init; }
    public int Fullmove { get; init; }
    public int KingSqWhite { get; init; }
    public int KingSqBlack { get; init; }
}
