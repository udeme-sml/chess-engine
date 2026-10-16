const PIECES = {
  P: "♙", N: "♘", B: "♗", R: "♖", Q: "♕", K: "♔",
  p: "♟", n: "♞", b: "♝", r: "♜", q: "♛", k: "♚",
};

const FILES = "abcdefgh";
let state = null;
let selected = null;
let pollTimer = null;

function sqName(index) {
  const file = index % 8;
  const rank = index >> 3;
  return FILES[file] + (rank + 1);
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

async function fetchState() {
  const res = await fetch("/api/state");
  state = await res.json();
  render();
}

async function newGame(mode) {
  selected = null;
  await fetch("/api/new", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ mode }),
  });
  await fetchState();
  schedulePoll();
}

async function playMove(uci) {
  const res = await fetch("/api/move", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ uci }),
  });
  state = await res.json();
  if (state.error) return;
  selected = null;
  render();
  schedulePoll();
}

function schedulePoll() {
  clearInterval(pollTimer);
  if (state?.engine_thinking) {
    pollTimer = setInterval(fetchState, 400);
  }
}

function render() {
  if (!state) return;
  const boardEl = document.getElementById("board");
  const statusEl = document.getElementById("status");
  const moveList = document.getElementById("move-list");

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
      if (piece) div.textContent = PIECES[piece] || piece;
      div.addEventListener("click", () => onSquareClick(name, piece, legalFrom, legal));
      boardEl.appendChild(div);
    }
  }

  let turn = state.stm === "w" ? "White" : "Black";
  let msg = `${turn} to move`;
  if (state.engine_thinking) msg += " — engine thinking…";
  if (state.result) msg = `Game over: ${state.result.replace(/_/g, " ")}`;
  statusEl.textContent = msg;

  moveList.innerHTML = state.move_history.map((m) => `<li>${m}</li>`).join("");
}

function onSquareClick(name, piece, legalFrom, legal) {
  if (state.result || state.engine_thinking) return;
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

fetchState();
