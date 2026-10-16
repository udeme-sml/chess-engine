/**
 * Game API: local Python server when available, otherwise Pyodide in a worker (GitHub Pages).
 */
const chessApi = (() => {
  let mode = null; // "http" | "pyodide"
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
    return siteRoot() + p;
  }

  async function probeHttp() {
    try {
      const res = await fetch(apiUrl("api/state"), { method: "GET" });
      const ct = res.headers.get("content-type") || "";
      return res.ok && ct.includes("application/json");
    } catch {
      return false;
    }
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

  async function initPyodide() {
    worker = new Worker(new URL("./engine-worker.js", import.meta.url));
    worker.addEventListener("message", onWorkerMessage);
    await workerCall("init");
  }

  async function init() {
    if (mode) return mode;
    if (await probeHttp()) {
      mode = "http";
    } else {
      mode = "pyodide";
      await initPyodide();
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
