namespace ChessEngine.Rules;

public static class Zobrist
{
    public static ulong HashPiece(int piece, int sq) =>
        piece == 0 ? 0 : ZobristKeys.PieceKeys[piece][sq];

    public static ulong HashCastling(CastlingRights rights) => ZobristKeys.CastleKeys[(int)rights];

    public static ulong HashEpFile(int fileIndex) => ZobristKeys.EpFileKeys[fileIndex];

    public static ulong ComputeHash(int[] board, Color stm, CastlingRights castling, int epSq)
    {
        ulong h = 0;
        for (var sq = 0; sq < 64; sq++)
            h ^= HashPiece(board[sq], sq);
        if (stm == Color.Black)
            h ^= ZobristKeys.SideKey;
        h ^= HashCastling(castling);
        if (epSq >= 0)
            h ^= HashEpFile(epSq & 7);
        return h;
    }
}
