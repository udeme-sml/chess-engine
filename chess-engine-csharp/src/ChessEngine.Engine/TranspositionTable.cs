using ChessEngine.Rules;

namespace ChessEngine.Engine;

/// <summary>
/// Fixed-size transposition table keyed by <see cref="Position.Hash"/> (Zobrist).
/// One bucket per index; replace on key mismatch or when the new entry is deeper.
/// </summary>
internal static class TranspositionTable
{
    internal const int BoundExact = 0;
    internal const int BoundLower = 1;
    internal const int BoundUpper = 2;

    private const int Size = 1 << 20;

    private static readonly TtEntry[] Table = new TtEntry[Size];
    private static int _searchGeneration;

    static TranspositionTable()
    {
        for (var i = 0; i < Size; i++)
            Table[i] = new TtEntry();
    }

    internal static void BeginSearch() => _searchGeneration++;

    /// <summary>
    /// Returns a cutoff/exact score if available; otherwise null. Always outputs a hash move when the key matches.
    /// </summary>
    internal static int? Probe(ulong key, int depth, int alpha, int beta, out Move hashMove)
    {
        hashMove = Move.Null;
        var entry = Table[Index(key)];
        if (entry.Key == key && entry.MoveData != 0)
            hashMove = new Move(entry.MoveData);

        if (entry.Key != key || entry.Depth < depth)
            return null;

        var score = entry.Score;
        return entry.Bound switch
        {
            BoundExact => score,
            BoundLower when score >= beta => score,
            BoundUpper when score <= alpha => score,
            _ => null,
        };
    }

    internal static void Store(ulong key, int depth, int score, int bound, Move bestMove)
    {
        var idx = Index(key);
        var entry = Table[idx];
        if (entry.Key != key || depth >= entry.Depth || entry.Generation != _searchGeneration)
        {
            entry.Key = key;
            entry.Depth = depth;
            entry.Score = score;
            entry.Bound = bound;
            entry.MoveData = bestMove.Data;
            entry.Generation = _searchGeneration;
        }
    }

    private static int Index(ulong key) => (int)(key & (ulong)(Size - 1));

    private sealed class TtEntry
    {
        public ulong Key;
        public int Depth = -1;
        public int Score;
        public int Bound = BoundExact;
        public uint MoveData;
        public int Generation = -1;
    }
}
