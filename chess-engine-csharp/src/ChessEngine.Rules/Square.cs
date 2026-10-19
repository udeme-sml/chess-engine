namespace ChessEngine.Rules;

public static class Square
{
    private const string Files = "abcdefgh";
    private const string Ranks = "12345678";

    public static int FileOf(int sq) => sq & 7;

    public static int RankOf(int sq) => sq >> 3;

    public static string SquareName(int sq) => $"{Files[FileOf(sq)]}{Ranks[RankOf(sq)]}";

    public static int ParseSquare(string name)
    {
        var f = Files.IndexOf(name[0]);
        var r = Ranks.IndexOf(name[1]);
        return (r << 3) | f;
    }

    public static int SqUp(int sq, bool colorWhite) => sq + (colorWhite ? 8 : -8);

    public static bool OnBoard(int sq) => sq >= 0 && sq < 64;

    public static int Distance(int sq1, int sq2)
    {
        var f1 = FileOf(sq1);
        var r1 = RankOf(sq1);
        var f2 = FileOf(sq2);
        var r2 = RankOf(sq2);
        return Math.Max(Math.Abs(f1 - f2), Math.Abs(r1 - r2));
    }
}
