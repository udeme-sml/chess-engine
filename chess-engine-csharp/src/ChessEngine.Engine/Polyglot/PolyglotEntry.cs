namespace ChessEngine.Engine.Polyglot;

public readonly struct PolyglotEntry
{
    public ulong Key { get; init; }
    public ushort EncodedMove { get; init; }
    public ushort Weight { get; init; }
    public uint Learn { get; init; }
}
