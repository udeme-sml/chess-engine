using ChessEngine.Rules;

namespace ChessEngine.Engine;

/// <summary>
/// Public engine API — UI and UCI should call only through this type.
/// </summary>
public static class EngineApi
{
    public static Move FindBestMove(Position position, int timeLimitMs, int maxDepth)
    {
        _ = timeLimitMs;
        return Search.FindBestMove(position, maxDepth);
    }

    public static int Evaluate(Position position) => Eval.Evaluate(position);
}
