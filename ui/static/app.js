const PIECES = {
  P: "♙", N: "♘", B: "♗", R: "♖", Q: "♕", K: "♔",
  p: "♟", n: "♞", b: "♝", r: "♜", q: "♛", k: "♚",
};

const FILES = "abcdefgh";
const MOVE_ANIM_MS = 220;

let state = null;
let selected = null;
let pollTimer = null;
let thinkUiTimer = null;
let animating = false;

function sqName(index) {
  const file = index % 8;
  const rank = index >> 3;
  return FILES[file] + (rank + 1);
}

function nameToIdx(name) {
  const file = FILES.indexOf(name[0]);
  const rank = parseInt(name[1], 10) - 1;
  return (rank << 3) | file;
}

function parsePlacement(placement) {
  const board = Array(64).fill(null);
  let rank = 7;
  let file = 0;
  for (const ch of placement) {
    if (ch === "/") {
      rank--;
      file = 0;
    } else if (ch >= "1" && ch <= "8") {
      file += parseInt(ch, 10);
    } else {
      board[(rank << 3) | file] = ch;
      file++;
    }
  }
  return board;
}

function uciTargets(legal, fromUci) {
  return legal
    .filter((m) => m.startsWith(fromUci))
    .map((m) => m.slice(2, 4));
}

function promoPieceChar(uci, movingPiece) {
  const promo = uci.length > 4 ? uci[4] : null;
  if (!promo) return movingPiece;
  const white = movingPiece === movingPiece.toUpperCase();
  return white ? promo.toUpperCase() : promo;
}

function rookCastleSquares(uci, boardBefore) {
  const from = nameToIdx(uci.slice(0, 2));
  const to = nameToIdx(uci.slice(2, 4));
  const piece = boardBefore[from];
  if (!piece || piece.toLowerCase() !== "k") return null;
  const fromFile = from % 8;
  const toFile = to % 8;
  if (Math.abs(toFile - fromFile) !== 2) return null;
  const rank = from >> 3;
  if (toFile > fromFile) return { from: (rank << 3) | 7, to: (rank << 3) | 5 };
  return { from: (rank << 3) | 0, to: (rank << 3) | 3 };
}

function enPassantCaptureIdx(uci, boardBefore) {
  const from = nameToIdx(uci.slice(0, 2));
  const to = nameToIdx(uci.slice(2, 4));
  const piece = boardBefore[from];
  if (!piece || piece.toLowerCase() !== "p") return null;
  if (boardBefore[to]) return null;
  if ((from >> 3) === (to >> 3)) return null;
  return to + (piece === "P" ? -8 : 8);
}

function squareCenter(boardEl, sq) {
  const el = boardEl.querySelector(`[data-sq="${sq}"]`);
  if (!el) return null;
  const boardRect = boardEl.getBoundingClientRect();
  const r = el.getBoundingClientRect();
  return {
    x: r.left + r.width / 2 - boardRect.left,
    y: r.top + r.height / 2 - boardRect.top,
  };
}

function flyPiece(boardEl, fromSq, toSq, pieceChar, durationMs) {
  return new Promise((resolve) => {
    const from = squareCenter(boardEl, fromSq);
    const to = squareCenter(boardEl, toSq);
    if (!from || !to) {
      resolve();
      return;
    }
    const ghost = document.createElement("div");
    ghost.className = "piece-fly";
    ghost.textContent = PIECES[pieceChar] || pieceChar;
    ghost.style.left = `${from.x}px`;
    ghost.style.top = `${from.y}px`;
    ghost.style.transitionDuration = `${durationMs}ms`;
    boardEl.appendChild(ghost);
    requestAnimationFrame(() => {
      ghost.style.left = `${to.x}px`;
      ghost.style.top = `${to.y}px`;
    });
    const done = () => {
      ghost.remove();
      resolve();
    };
    ghost.addEventListener("transitionend", done, { once: true });
    setTimeout(done, durationMs + 40);
  });
}

async function animateMove(uci, boardBefore) {
  if (!uci || uci.length < 4) return;
  const boardEl = document.getElementById("board");
  const fromSq = uci.slice(0, 2);
  const toSq = uci.slice(2, 4);
  const moving = boardBefore[nameToIdx(fromSq)];
  if (!moving) return;

  animating = true;
  const hidden = new Set([fromSq, toSq]);
  const ep = enPassantCaptureIdx(uci, boardBefore);
  if (ep !== null) hidden.add(sqName(ep));
  const castle = rookCastleSquares(uci, boardBefore);
  if (castle) {
    hidden.add(sqName(castle.from));
    hidden.add(sqName(castle.to));
  }

  render({ hideSquares: hidden });

  const promoChar = promoPieceChar(uci, moving);
  const flights = [flyPiece(boardEl, fromSq, toSq, promoChar, MOVE_ANIM_MS)];
  if (castle) {
    const rook = boardBefore[castle.from];
    if (rook) {
      flights.push(
        flyPiece(boardEl, sqName(castle.from), sqName(castle.to), rook, MOVE_ANIM_MS)
      );
    }
  }
  await Promise.all(flights);
  boardEl.querySelectorAll(".piece-fly").forEach((n) => n.remove());
  animating = false;
}

async function fetchState() {
  if (animating) return;
  const prevPlacement = state ? parsePlacement(state.placement) : null;
  const prevLen = state?.move_history?.length ?? 0;
  const next = await chessApi.fetchState();
  if (next.move_history.length > prevLen && prevPlacement) {
    const uci = next.move_history[next.move_history.length - 1];
    state = next;
    await animateMove(uci, prevPlacement);
  } else {
    state = next;
  }
  render();
  schedulePoll();
}

async function newGame(mode) {
  selected = null;
  await chessApi.newGame(mode);
  await fetchState();
  schedulePoll();
}

async function playMove(uci) {
  const prevPlacement = parsePlacement(state.placement);
  const next = await chessApi.playMove(uci);
  if (next.error) {
    state = next;
    render();
    return;
  }
  state = next;
  selected = null;
  await animateMove(uci, prevPlacement);
  render();
  schedulePoll();
}

function schedulePoll() {
  clearInterval(pollTimer);
  if (state?.engine_thinking) {
    pollTimer = setInterval(fetchState, 250);
  }
  scheduleThinkUi();
}

function scheduleThinkUi() {
  clearInterval(thinkUiTimer);
  if (state?.engine_thinking) {
    thinkUiTimer = setInterval(() => {
      if (state?.engine_thinking && !animating) updateStatusText();
    }, 350);
  }
}

function updateStatusText() {
  const statusEl = document.getElementById("status");
  if (!state) return;

  let msg;
  if (state.result) {
    msg = `Game over: ${state.result.replace(/_/g, " ")}`;
    statusEl.classList.remove("thinking");
  } else if (state.engine_thinking) {
    const depth = state.engine_think_depth || 0;
    const dots = ".".repeat((Math.floor(Date.now() / 400) % 3) + 1);
    const depthPart = depth > 0 ? ` — depth ${depth}` : " — searching";
    msg = `Engine thinking${depthPart}${dots}`;
    statusEl.classList.add("thinking");
  } else {
    const turn = state.stm === "w" ? "White" : "Black";
    msg = `${turn} to move`;
    statusEl.classList.remove("thinking");
  }
  statusEl.textContent = msg;
}

function render(opts = {}) {
  if (!state) return;
  const boardEl = document.getElementById("board");
  const moveList = document.getElementById("move-list");
  const hideSquares = opts.hideSquares || null;

  const pieces = parsePlacement(state.placement);
  const legal = state.legal_moves || [];
  const legalFrom = new Set(legal.map((m) => m.slice(0, 2)));
  const highlights = selected ? new Set(uciTargets(legal, selected)) : new Set();

  let kingSq = null;
  for (let i = 0; i < 64; i++) {
    const p = pieces[i];
    if (p === (state.stm === "w" ? "K" : "k")) kingSq = sqName(i);
  }

  boardEl.innerHTML = "";
  for (let displayRank = 0; displayRank < 8; displayRank++) {
    for (let file = 0; file < 8; file++) {
      const rank = 7 - displayRank;
      const idx = rank * 8 + file;
      const name = sqName(idx);
      const div = document.createElement("div");
      div.className = "square " + ((file + rank) % 2 === 0 ? "light" : "dark");
      div.dataset.sq = name;
      if (selected === name) div.classList.add("selected");
      if (highlights.has(name)) div.classList.add("legal");
      if (state.in_check && name === kingSq) div.classList.add("check");
      const piece = pieces[idx];
      const hide = hideSquares && hideSquares.has(name);
      if (piece && !hide) div.textContent = PIECES[piece] || piece;
      div.addEventListener("click", () => onSquareClick(name, piece, legalFrom, legal));
      boardEl.appendChild(div);
    }
  }

  updateStatusText();
  moveList.innerHTML = state.move_history.map((m) => `<li>${m}</li>`).join("");
}

function onSquareClick(name, piece, legalFrom, legal) {
  if (state.result || state.engine_thinking || animating) return;
  if (state.mode === "human_engine") {
    const humanIsWhite = true;
    const stmWhite = state.stm === "w";
    if (stmWhite !== humanIsWhite) return;
  }
  if (selected && uciTargets(legal, selected).includes(name)) {
    const promo = legal.find((m) => m.startsWith(selected + name) && m.length > 4);
    playMove(selected + name + (promo ? promo[4] : ""));
    return;
  }
  if (piece && legalFrom.has(name)) {
    selected = name;
    render();
    return;
  }
  selected = null;
  render();
}

document.getElementById("btn-new-human").addEventListener("click", () => newGame("human_human"));
document.getElementById("btn-new-engine").addEventListener("click", () => newGame("human_engine"));

(async () => {
  const statusEl = document.getElementById("status");
  statusEl.textContent = "Loading… (first visit downloads the engine)";
  try {
    await chessApi.init();
    await fetchState();
  } catch (e) {
    statusEl.textContent = `Failed to load: ${e.message}`;
  }
})();
