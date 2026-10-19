using System.Text.Json;
using System.Text.Json.Serialization;

namespace ChessEngine.Browser;

internal sealed class GameStateJson
{
    [JsonPropertyName("fen")]
    public string Fen { get; set; } = "";

    [JsonPropertyName("placement")]
    public string Placement { get; set; } = "";

    [JsonPropertyName("stm")]
    public string Stm { get; set; } = "w";

    [JsonPropertyName("legal_moves")]
    public string[] LegalMoves { get; set; } = [];

    [JsonPropertyName("in_check")]
    public bool InCheck { get; set; }

    [JsonPropertyName("result")]
    public string? Result { get; set; }

    [JsonPropertyName("mode")]
    public string Mode { get; set; } = "human_human";

    [JsonPropertyName("engine_thinking")]
    public bool EngineThinking { get; set; }

    [JsonPropertyName("engine_think_depth")]
    public int EngineThinkDepth { get; set; }

    [JsonPropertyName("pending_engine_move")]
    public string? PendingEngineMove { get; set; }

    [JsonPropertyName("move_history")]
    public string[] MoveHistory { get; set; } = [];

    [JsonPropertyName("engine_backend")]
    public string EngineBackend { get; set; } = "csharp";

    [JsonPropertyName("error")]
    [JsonIgnore(Condition = JsonIgnoreCondition.WhenWritingNull)]
    public string? Error { get; set; }
}

[JsonSerializable(typeof(GameStateJson))]
internal partial class GameStateJsonContext : JsonSerializerContext;
