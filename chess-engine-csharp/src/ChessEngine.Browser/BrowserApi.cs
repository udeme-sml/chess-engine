using System.Runtime.InteropServices.JavaScript;
using ChessEngine.Engine;

namespace ChessEngine.Browser;

public static partial class BrowserApi
{
    private static readonly WebGameSession Session = new();

    [JSExport]
    public static void ConfigureOpeningBook(byte[] data) => EngineApi.SetBookData(data);

    [JSExport]
    public static void NewGame(string mode) => Session.Reset(mode);

    [JSExport]
    public static string ApplyHumanMove(string uci)
    {
        var err = Session.ApplyHumanMove(uci);
        return Session.ToJson(err);
    }

    [JSExport]
    public static string Tick()
    {
        Session.Tick();
        return Session.ToJson();
    }

    [JSExport]
    public static string GetState() => Session.ToJson();
}
