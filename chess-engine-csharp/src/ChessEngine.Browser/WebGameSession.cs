using System.Text.Json;
using ChessEngine.Engine;
using ChessEngine.Rules;

namespace ChessEngine.Browser;

internal sealed class WebGameSession
{
    public const int EngineSearchDepth = 6;
    private const string StartFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    private string _mode = "human_human";
    private Position _position = Position.FromFen(StartFen);
    private readonly Color _humanColor = Color.White;
    private bool _engineThinking;
    private int _engineThinkDepth;
    private string? _pendingEngineMove;
    private readonly List<string> _moveHistory = [];

    public void Reset(string mode)
    {
        _mode = mode is "human_engine" ? "human_engine" : "human_human";
        _position = Position.FromFen(StartFen);
        _moveHistory.Clear();
        _pendingEngineMove = null;
        _engineThinking = false;
        _engineThinkDepth = 0;
    }

    public string? ApplyHumanMove(string uci)
    {
        if (_engineThinking)
            return "Engine is thinking";

        try
        {
            var legal = MoveGen.GenerateLegalMoves(_position);
            var move = MoveUci.FromUci(uci, legal);
            _position.MakeMove(move);
            _moveHistory.Add(uci);
            if (_mode == "human_engine")
                MaybeStartEngine();
            return null;
        }
        catch (Exception ex)
        {
            return ex.Message;
        }
    }

    public void Tick()
    {
        if (_pendingEngineMove is not null && !_engineThinking)
            ApplyPendingEngineMove();
        else if (_engineThinking)
            RunEngineSearch();
    }

    private Color EngineColor => _humanColor == Color.White ? Color.Black : Color.White;

    private void MaybeStartEngine()
    {
        if (Game.GetResult(_position) != GameResult.Ongoing)
            return;
        if (_position.Stm == _humanColor)
            return;
        if (_engineThinking)
            return;
        _engineThinking = true;
        _engineThinkDepth = EngineSearchDepth;
    }

    private void RunEngineSearch()
    {
        var searchPos = Position.FromFen(_position.Fen());
        var best = EngineApi.FindBestMove(searchPos, 0, EngineSearchDepth);
        _pendingEngineMove = MoveUci.ToUci(best);
        _engineThinking = false;
        _engineThinkDepth = 0;
    }

    private void ApplyPendingEngineMove()
    {
        if (_pendingEngineMove is null || _engineThinking)
            return;
        var uci = _pendingEngineMove;
        _pendingEngineMove = null;
        var legal = MoveGen.GenerateLegalMoves(_position);
        var move = MoveUci.FromUci(uci, legal);
        _position.MakeMove(move);
        _moveHistory.Add(uci);
    }

    public string ToJson(string? error = null)
    {
        var result = Game.GetResult(_position);
        var payload = new Dictionary<string, object?>
        {
            ["fen"] = _position.Fen(),
            ["placement"] = FenCodec.BoardToPiecePlacement(_position.Board),
            ["stm"] = _position.Stm == Color.White ? "w" : "b",
            ["legal_moves"] = MoveGen.GenerateLegalMoves(_position).Select(MoveUci.ToUci).ToArray(),
            ["in_check"] = Game.SideInCheck(_position),
            ["result"] = result == GameResult.Ongoing ? null : result.ToString(),
            ["mode"] = _mode,
            ["engine_thinking"] = _engineThinking,
            ["engine_think_depth"] = _engineThinkDepth,
            ["pending_engine_move"] = _pendingEngineMove,
            ["move_history"] = _moveHistory.ToArray(),
            ["engine_backend"] = "csharp",
        };
        if (error is not null)
            payload["error"] = error;
        return JsonSerializer.Serialize(payload);
    }
}
