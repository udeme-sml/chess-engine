using ChessEngine.Rules;

namespace ChessEngine.Engine.Polyglot;

/// <summary>Standard Polyglot/Crafty Zobrist key (not the engine's internal <see cref="Position.Hash"/>).</summary>
public static class PolyglotHash
{
    public static ulong Compute(Position position)
    {
        ulong key = 0;
        var board = position.Board;

        for (var sq = 0; sq < 64; sq++)
        {
            var piece = board[sq];
            if (piece == 0)
                continue;
            key ^= PieceKey(piece, sq);
        }

        key ^= CastleKey(position.Castling);
        key ^= EpKey(position);

        if (position.Stm == Color.White)
            key ^= PolyglotRandom64.Values[PolyglotRandom64.TurnOffset];

        return key;
    }

    private static ulong PieceKey(int piece, int sq)
    {
        var piece12 = PieceTo12(piece);
        return PolyglotRandom64.Values[PolyglotRandom64.PieceOffset + piece12 * 64 + sq];
    }

    /// <summary>Polyglot piece order: bP, wP, bN, wN, … bK, wK.</summary>
    internal static int PieceTo12(int piece)
    {
        var pt = (int)ChessConstants.GetPieceType(piece) - 1;
        var white = ChessConstants.PieceColor(piece) == Color.White ? 1 : 0;
        return pt * 2 + white;
    }

    private static ulong CastleKey(CastlingRights rights)
    {
        var flags = (int)rights & 0xF;
        ulong key = 0;
        for (var i = 0; i < 4; i++)
        {
            if ((flags & (1 << i)) != 0)
                key ^= PolyglotRandom64.Values[PolyglotRandom64.CastleOffset + i];
        }
        return key;
    }

    /// <summary>Match python-chess / Polyglot books: EP file only if STM has a pawn that could capture.</summary>
    private static ulong EpKey(Position position)
    {
        if (position.EpSq < 0)
            return 0;

        var ep = position.EpSq;
        var behind = position.Stm == Color.White ? ep - 8 : ep + 8;
        if (!Square.OnBoard(behind))
            return 0;

        var ownPawn = ChessConstants.MakePiece(position.Stm, PieceType.Pawn);
        var board = position.Board;
        foreach (var sq in new[] { behind - 1, behind + 1 })
        {
            if (!Square.OnBoard(sq))
                continue;
            if (Square.FileOf(sq) == Square.FileOf(ep))
                continue;
            if (board[sq] == ownPawn)
                return PolyglotRandom64.Values[PolyglotRandom64.EnPassantOffset + Square.FileOf(ep)];
        }

        return 0;
    }
}
