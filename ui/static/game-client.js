/**
 * Game API: optional local Python UI server, otherwise C# WebAssembly in a worker.
 */
export const chessApi = (() => {
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

  function stateApiUrl(base) {
    const root = base.endsWith("/") ? base : `${base}/`;
    if (/^https?:\/\//i.test(root)) {
      return `${root}api/state`;
    }
    return new URL("api/state", new URL(root, window.location.origin)).href;
  }

  async function probeStateApi(base) {
    try {
      const res = await fetch(stateApiUrl(base), { method: "GET" });
      if (!res.ok) return false;
      const ct = res.headers.get("content-type") || "";
      if (!ct.includes("application/json")) return false;
      const data = await res.json();
      return typeof data.placement === "string" && Array.isArray(data.legal_moves);
    } catch {
      return false;
    }
  }

  async function resolveHttpBase() {
    const host = window.location.hostname;
    const onLocal = host === "localhost" || host === "127.0.0.1";

    // Only the Python ui.server (port 8765) exposes /api/* — never probe on static hosts (e.g. GitHub Pages).
    if (onLocal && window.location.port === "8765") {
      const base = siteRoot();
      if (await probeStateApi(base)) return base;
    }
    if (onLocal) {
      const remote = `http://${host}:8765/`;
      if (await probeStateApi(remote)) return remote;
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
