/* C# engine (WebAssembly) + rules — static hosting and GitHub Pages. */
import { dotnet } from "./csharp-engine/_framework/dotnet.js";

let api = null;

function reply(id, ok, payload) {
  postMessage({ id, ok, ...payload });
}

async function ensureReady() {
  if (api) return api;
  const configSrc = new URL("./csharp-engine/_framework/blazor.boot.json", import.meta.url).href;
  const { getAssemblyExports } = await dotnet.withConfigSrc(configSrc).create();
  const exports = await getAssemblyExports("ChessEngine.Browser.dll");
  api = exports.ChessEngine.Browser.BrowserApi;
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
  const state = parseState(json);
  if (!state.error) {
    game.Tick();
    if (parseState(game.GetState()).engine_thinking) {
      game.Tick();
    }
    Object.assign(state, parseState(game.GetState()));
    if (!state.error && state.pending_engine_move && !state.engine_thinking) {
      game.Tick();
      Object.assign(state, parseState(game.GetState()));
    }
  }
  reply(id, true, { state });
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
