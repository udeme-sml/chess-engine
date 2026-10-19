/**
 * Game API: optional local Python UI server, otherwise C# WebAssembly in a worker.
 */
const chessApi = (() => {
  let mode = null; // "http" | "wasm"
  let httpBase = null;
  let worker = null;
  let msgId = 0;
  const pending = new Map();

  function siteRoot() {
    let path = window.location.pathname;
    if (path.endsWith(".html")) {
      path = path.replace(/\/[^/]+$/, "/");
    } else if (!path.endsWith("/")) {
      path += "/";
    }
    return path;
  }

  function apiUrl(path) {
    const p = path.replace(/^\//, "");
    const root = mode === "http" && httpBase ? httpBase : siteRoot();
    return root + p;
  }

  async function probeStateApi(base) {
    try {
      const url = base.endsWith("/") ? `${base}api/state` : `${base}/api/state`;
      const res = await fetch(url, { method: "GET" });
      const ct = res.headers.get("content-type") || "";
      return res.ok && ct.includes("application/json");
    } catch {
      return false;
    }
  }

  async function resolveHttpBase() {
    if (await probeStateApi(siteRoot())) {
      return siteRoot();
    }
    const host = window.location.hostname;
    if (host === "localhost" || host === "127.0.0.1") {
      const local = "http://127.0.0.1:8765/";
      if (await probeStateApi(local)) {
        return local;
      }
    }
    return null;
  }

  function workerCall(cmd, body = {}) {
    const id = ++msgId;
    return new Promise((resolve, reject) => {
      pending.set(id, { resolve, reject });
      worker.postMessage({ id, cmd, body });
    });
  }

  function onWorkerMessage(event) {
    const { id, ok, state, error } = event.data;
    const entry = pending.get(id);
    if (!entry) return;
    pending.delete(id);
    if (ok) entry.resolve(state);
    else entry.reject(new Error(error || "Worker error"));
  }

  async function initWasmWorker() {
    worker = new Worker(new URL("./engine-worker.js", import.meta.url), { type: "module" });
    worker.addEventListener("message", onWorkerMessage);
    await workerCall("init");
  }

  async function init() {
    if (mode) return mode;
    const base = await resolveHttpBase();
    if (base) {
      mode = "http";
      httpBase = base;
    } else {
      mode = "wasm";
      await initWasmWorker();
    }
    return mode;
  }

  async function fetchState() {
    await init();
    if (mode === "http") {
      const res = await fetch(apiUrl("api/state"));
      return res.json();
    }
    return workerCall("state");
  }

  async function newGame(gameMode) {
    await init();
    if (mode === "http") {
      await fetch(apiUrl("api/new"), {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ mode: gameMode }),
      });
      return fetchState();
    }
    return workerCall("new", { mode: gameMode });
  }

  async function playMove(uci) {
    await init();
    if (mode === "http") {
      const res = await fetch(apiUrl("api/move"), {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ uci }),
      });
      return res.json();
    }
    return workerCall("move", { uci });
  }

  return { init, fetchState, newGame, playMove };
})();

window.chessApi = chessApi;
