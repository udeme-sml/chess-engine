/* Pyodide worker — runs the Python engine for static hosting (GitHub Pages). */
importScripts("https://cdn.jsdelivr.net/pyodide/v0.26.4/full/pyodide.js");

const PYODIDE_INDEX = "https://cdn.jsdelivr.net/pyodide/v0.26.4/full/";

let pyodide = null;
let ready = false;

function reply(id, ok, payload) {
  postMessage({ id, ok, ...payload });
}

async function loadPythonTree() {
  const manifest = await fetch("./python-manifest.json").then((r) => r.json());
  for (const rel of manifest) {
    const text = await fetch(`./python/${rel}`).then((r) => r.text());
    const parts = rel.split("/");
    parts.pop();
    const dir = parts.join("/");
    if (dir) {
      pyodide.FS.mkdirTree(`/py/${dir}`);
    }
    pyodide.FS.writeFile(`/py/${rel}`, text);
  }
}

async function ensureReady() {
  if (ready) return;
  pyodide = await loadPyodide({ indexURL: PYODIDE_INDEX });
  await loadPythonTree();
  await pyodide.runPythonAsync(`
import sys
sys.path.insert(0, "/py")
from ui.game_session import GameSession, PlayerMode

SESSION = GameSession(cooperative_engine=True)
`);
  ready = true;
}

function sessionState() {
  return pyodide.runPython("import json; json.dumps(SESSION.to_json())");
}

async function handleState(id) {
  await pyodide.runPythonAsync(`
if SESSION.pending_engine_move and not SESSION.engine_thinking:
    SESSION.apply_pending_engine_move()
elif SESSION.engine_thinking:
    SESSION.engine_tick()
`);
  reply(id, true, { state: JSON.parse(sessionState()) });
}

async function handleNew(id, body) {
  const mode = body.mode || "human_human";
  await pyodide.runPythonAsync(`
SESSION.reset()
SESSION.mode = PlayerMode("${mode}")
`);
  reply(id, true, { state: JSON.parse(sessionState()) });
}

async function handleMove(id, body) {
  const uci = body.uci || "";
  pyodide.globals.set("_uci", uci);
  let err = null;
  try {
    await pyodide.runPythonAsync(`
_err = None
try:
    SESSION.apply_human_move(_uci)
    if SESSION.pending_engine_move and not SESSION.engine_thinking:
        SESSION.apply_pending_engine_move()
    elif SESSION.engine_thinking:
        SESSION.engine_tick()
except ValueError as e:
    _err = str(e)
`);
    err = pyodide.globals.get("_err");
  } catch (e) {
    err = String(e);
  }
  if (err) {
    reply(id, true, { state: { error: err } });
    return;
  }
  reply(id, true, { state: JSON.parse(sessionState()) });
}

onmessage = async (event) => {
  const { id, cmd, body } = event.data;
  try {
    await ensureReady();
    if (cmd === "init") {
      reply(id, true, { state: JSON.parse(sessionState()) });
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
