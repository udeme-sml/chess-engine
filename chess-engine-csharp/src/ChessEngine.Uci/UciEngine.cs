using ChessEngine.Engine;
using ChessEngine.Rules;

namespace ChessEngine.Uci;

public sealed class UciEngine
{
    private const string StartFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    private Position _position = Position.FromFen(StartFen);
    private bool _stop;

    public void Loop()
    {
        string? line;
        while ((line = Console.ReadLine()) is not null)
        {
            line = line.Trim();
            if (line.Length == 0)
                continue;
            if (Handle(line))
                break;
        }
    }

    private bool Handle(string line)
    {
        var parts = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        var cmd = parts[0];
        switch (cmd)
        {
            case "uci":
                Console.WriteLine("id name ChessEngineCSharp");
                Console.WriteLine("id author You");
                Console.WriteLine("uciok");
                Console.Out.Flush();
                break;
            case "isready":
                Console.WriteLine("readyok");
                Console.Out.Flush();
                break;
            case "ucinewgame":
                _position = Position.FromFen(StartFen);
                break;
            case "position":
                SetPosition(parts[1..]);
                break;
            case "go":
                Go(parts[1..]);
                break;
            case "stop":
                _stop = true;
                break;
            case "quit":
                return true;
        }
        return false;
    }

    private void SetPosition(string[] args)
    {
        var idx = 0;
        if (args[0] == "startpos")
        {
            _position = Position.FromFen(StartFen);
            idx = 1;
        }
        else if (args[0] == "fen")
        {
            var fenParts = new List<string>();
            idx = 1;
            while (idx < args.Length && args[idx] != "moves")
            {
                fenParts.Add(args[idx]);
                idx++;
            }
            _position = Position.FromFen(string.Join(' ', fenParts));
        }
        else
            return;

        if (idx < args.Length && args[idx] == "moves")
        {
            for (var i = idx + 1; i < args.Length; i++)
            {
                var legal = MoveGen.GenerateLegalMoves(_position);
                _position.MakeMove(MoveUci.FromUci(args[i], legal));
            }
        }
    }

    private void Go(string[] args)
    {
        _stop = false;
        var depth = 64;
        var movetime = 2000;
        for (var i = 0; i < args.Length; i++)
        {
            if (args[i] == "depth" && i + 1 < args.Length)
                depth = int.Parse(args[i + 1]);
            if (args[i] == "movetime" && i + 1 < args.Length)
                movetime = int.Parse(args[i + 1]);
        }
        _ = movetime;
        var mv = EngineApi.FindBestMove(_position, movetime, depth);
        Console.WriteLine($"bestmove {MoveUci.ToUci(mv)}");
        Console.Out.Flush();
    }
}
