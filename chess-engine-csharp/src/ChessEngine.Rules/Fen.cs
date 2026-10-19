namespace ChessEngine.Rules;

public static class FenCodec
{
    private static readonly Dictionary<char, int> FenToPiece = new()
    {
        ['P'] = ChessConstants.WPawn,
        ['N'] = ChessConstants.WKnight,
        ['B'] = ChessConstants.WBishop,
        ['R'] = ChessConstants.WRook,
        ['Q'] = ChessConstants.WQueen,
        ['K'] = ChessConstants.WKing,
        ['p'] = ChessConstants.BPawn,
        ['n'] = ChessConstants.BKnight,
        ['b'] = ChessConstants.BBishop,
        ['r'] = ChessConstants.BRook,
        ['q'] = ChessConstants.BQueen,
        ['k'] = ChessConstants.BKing,
    };

    private static readonly Dictionary<int, char> PieceToFen = FenToPiece.ToDictionary(kv => kv.Value, kv => kv.Key);

    public static (int[] Board, Color Stm, CastlingRights Castling, int EpSq, int Halfmove, int Fullmove) ParseFen(string fen)
    {
        var parts = fen.Trim().Split(' ', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length < 4)
            throw new ArgumentException($"Invalid FEN: {fen}");

        var board = new int[64];
        var rank = 7;
        var file = 0;
        foreach (var ch in parts[0])
        {
            if (ch == '/')
            {
                rank--;
                file = 0;
            }
            else if (char.IsDigit(ch))
            {
                file += ch - '0';
            }
            else
            {
                var sq = (rank << 3) | file;
                board[sq] = FenToPiece[ch];
                file++;
            }
        }

        var stm = parts[1] == "w" ? Color.White : Color.Black;

        var castling = CastlingRights.None;
        if (parts.Length > 2 && parts[2] != "-")
        {
            var flags = parts[2];
            if (flags.Contains('K')) castling |= CastlingRights.WhiteKing;
            if (flags.Contains('Q')) castling |= CastlingRights.WhiteQueen;
            if (flags.Contains('k')) castling |= CastlingRights.BlackKing;
            if (flags.Contains('q')) castling |= CastlingRights.BlackQueen;
        }

        var epSq = -1;
        if (parts.Length > 3 && parts[3] != "-")
            epSq = Square.ParseSquare(parts[3]);

        var halfmove = parts.Length > 4 ? int.Parse(parts[4]) : 0;
        var fullmove = parts.Length > 5 ? int.Parse(parts[5]) : 1;

        return (board, stm, castling, epSq, halfmove, fullmove);
    }

    public static string BoardToPiecePlacement(int[] board)
    {
        var rows = new List<string>();
        for (var rank = 7; rank >= 0; rank--)
        {
            var empty = 0;
            var rowChars = new List<char>();
            for (var file = 0; file < 8; file++)
            {
                var sq = (rank << 3) | file;
                var piece = board[sq];
                if (piece == 0)
                {
                    empty++;
                }
                else
                {
                    if (empty > 0)
                    {
                        rowChars.Add((char)('0' + empty));
                        empty = 0;
                    }
                    rowChars.Add(PieceToFen[piece]);
                }
            }
            if (empty > 0)
                rowChars.Add((char)('0' + empty));
            rows.Add(string.Concat(rowChars));
        }
        return string.Join('/', rows);
    }

    public static string ToFen(int[] board, Color stm, CastlingRights castling, int epSq, int halfmove, int fullmove)
    {
        var placement = BoardToPiecePlacement(board);
        var stmCh = stm == Color.White ? "w" : "b";
        var castle = "";
        if ((castling & CastlingRights.WhiteKing) != 0) castle += "K";
        if ((castling & CastlingRights.WhiteQueen) != 0) castle += "Q";
        if ((castling & CastlingRights.BlackKing) != 0) castle += "k";
        if ((castling & CastlingRights.BlackQueen) != 0) castle += "q";
        if (castle.Length == 0) castle = "-";
        var ep = epSq < 0 ? "-" : $"{(char)('a' + Square.FileOf(epSq))}{Square.RankOf(epSq) + 1}";
        return $"{placement} {stmCh} {castle} {ep} {halfmove} {fullmove}";
    }
}
