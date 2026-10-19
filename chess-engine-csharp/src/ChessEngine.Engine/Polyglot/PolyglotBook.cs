using System.Buffers.Binary;
using ChessEngine.Rules;

namespace ChessEngine.Engine.Polyglot;

/// <summary>Read-only Polyglot opening book (.bin).</summary>
public sealed class PolyglotBook
{
    public const int EntrySizeBytes = 16;

    private readonly PolyglotEntry[] _entries;

    private PolyglotBook(PolyglotEntry[] entries) => _entries = entries;

    public int Count => _entries.Length;

    public static PolyglotBook Load(string path)
    {
        if (!File.Exists(path))
            throw new FileNotFoundException("Polyglot book not found.", path);
        return Load(File.ReadAllBytes(path));
    }

    public static PolyglotBook Load(byte[] bytes)
    {
        if (bytes.Length % EntrySizeBytes != 0)
            throw new InvalidDataException($"Polyglot book size {bytes.Length} is not a multiple of {EntrySizeBytes}.");

        var count = bytes.Length / EntrySizeBytes;
        var entries = new PolyglotEntry[count];
        for (var i = 0; i < count; i++)
        {
            var offset = i * EntrySizeBytes;
            // Polyglot on-disk layout is big-endian (>QHHI), per python-chess and common tools.
            entries[i] = new PolyglotEntry
            {
                Key = BinaryPrimitives.ReadUInt64BigEndian(bytes.AsSpan(offset)),
                EncodedMove = BinaryPrimitives.ReadUInt16BigEndian(bytes.AsSpan(offset + 8)),
                Weight = BinaryPrimitives.ReadUInt16BigEndian(bytes.AsSpan(offset + 10)),
                Learn = BinaryPrimitives.ReadUInt32BigEndian(bytes.AsSpan(offset + 12)),
            };
        }

        Array.Sort(entries, static (a, b) => a.Key.CompareTo(b.Key));

        return new PolyglotBook(entries);
    }

    public ulong ComputeKey(Position position) => PolyglotHash.Compute(position);

    public IReadOnlyList<PolyglotEntry> Probe(Position position) => Probe(ComputeKey(position));

    public IReadOnlyList<PolyglotEntry> Probe(ulong key)
    {
        var lo = 0;
        var hi = _entries.Length - 1;
        while (lo <= hi)
        {
            var mid = lo + (hi - lo) / 2;
            var midKey = _entries[mid].Key;
            if (midKey < key)
                lo = mid + 1;
            else if (midKey > key)
                hi = mid - 1;
            else
            {
                var start = mid;
                while (start > 0 && _entries[start - 1].Key == key)
                    start--;
                var end = mid;
                while (end + 1 < _entries.Length && _entries[end + 1].Key == key)
                    end++;
                var length = end - start + 1;
                var slice = new PolyglotEntry[length];
                Array.Copy(_entries, start, slice, 0, length);
                return slice;
            }
        }

        return Array.Empty<PolyglotEntry>();
    }

    public const string BookPathEnvironmentVariable = "CHESS_ENGINE_BOOK_PATH";

    /// <summary>Default book path relative to repo root when running from chess-engine-csharp/.</summary>
    public static string DefaultBookPath()
    {
        var fromEnv = Environment.GetEnvironmentVariable(BookPathEnvironmentVariable);
        if (!string.IsNullOrWhiteSpace(fromEnv))
            return Path.GetFullPath(fromEnv);

        var dir = AppContext.BaseDirectory;
        for (var i = 0; i < 8; i++)
        {
            var candidate = Path.GetFullPath(Path.Combine(dir, "data", "books", "performance.bin"));
            if (File.Exists(candidate))
                return candidate;
            var parent = Directory.GetParent(dir);
            if (parent is null)
                break;
            dir = parent.FullName;
        }

        return Path.GetFullPath(Path.Combine(
            Directory.GetCurrentDirectory(),
            "..",
            "data",
            "books",
            "performance.bin"));
    }
}
