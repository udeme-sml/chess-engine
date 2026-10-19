/* C# engine (WebAssembly) + rules — static hosting and GitHub Pages. */
import { dotnet } from "./csharp-engine/_framework/dotnet.js";

let api = null;

function reply(id, ok, payload) {
  postMessage({ id, ok, ...payload });
}

function postProgress(message) {
  postMessage({ type: "progress", message });
}

async function loadOpeningBook(game) {
  const bookUrl = new URL("./books/performance.bin", import.meta.url).href;
  try {
    const res = await fetch(bookUrl);
    if (!res.ok) return;
    postProgress("Loading opening book…");
    const data = new Uint8Array(await res.arrayBuffer());
    game.ConfigureOpeningBook(data);
  } catch {
    // Book optional — engine falls back to search.
  }
}

async function ensureReady() {
  if (api) return api;
  postProgress("Downloading C# engine (first visit only — then cached)…");
  const configSrc = new URL("./csharp-engine/_framework/blazor.boot.json", import.meta.url).href;
  const { getAssemblyExports } = await dotnet.withConfigSrc(configSrc).create();
  postProgress("Starting engine…");
  const exports = await getAssemblyExports("ChessEngine.Browser.dll");
  api = exports.ChessEngine.Browser.BrowserApi;
  await loadOpeningBook(api);
  return api;
}

function parseState(json) {
  return JSON.parse(json);
}

async function handleState(id) {
  const game = await ensureReady();
  game.Tick();
  reply(id, true, { state: parseState(game.GetState()) });
}

async function handleNew(id, body) {
  const game = await ensureReady();
  const mode = body.mode || "human_human";
  game.NewGame(mode);
  reply(id, true, { state: parseState(game.GetState()) });
}

async function handleMove(id, body) {
  const game = await ensureReady();
  const uci = body.uci || "";
  const json = game.ApplyHumanMove(uci);
  reply(id, true, { state: parseState(json) });
}

onmessage = async (event) => {
  const { id, cmd, body } = event.data;
  try {
    if (cmd === "init") {
      const game = await ensureReady();
      reply(id, true, { state: parseState(game.GetState()) });
      return;
    }
    if (cmd === "state") {
      await handleState(id);
      return;
    }
    if (cmd === "new") {
      await handleNew(id, body || {});
      return;
    }
    if (cmd === "move") {
      await handleMove(id, body || {});
      return;
    }
    reply(id, false, { error: `Unknown command: ${cmd}` });
  } catch (e) {
    reply(id, false, { error: String(e) });
  }
};
