/* ========================================================
   games_f.js
   Controlador de Jogos Web (21 Palitos & Campo Minado)
   Lógicas portadas do C nativo para ES6
   ======================================================== */

/* ========================================================
   1. JOGO DOS 21 PALITOS
   ======================================================== */
let currentSticks = 21;

function updateDisplay() {
    const sticksDisplay = document.getElementById('sticks-display');
    const stickCount = document.getElementById('stick-count');
    if (sticksDisplay && stickCount) {
        sticksDisplay.innerText = '| '.repeat(currentSticks).trim();
        stickCount.innerText = currentSticks;
    }
}

function playSticks() {
    const input = document.getElementById('stick-input');
    const msg = document.getElementById('sticks-msg');
    let u = parseInt(input.value);

    if (isNaN(u) || u < 1 || u > 4 || u > currentSticks) {
        msg.innerText = "⚠️ Jogada inválida! Escolha de 1 a 4 palitos.";
        msg.style.color = "#ff4444";
        return;
    }
    msg.style.color = "inherit";

    currentSticks -= u;
    if (currentSticks === 0) {
        msg.innerText = `Você tirou ${u} e pegou o último palito. VOCÊ PERDEU! 😭`;
        updateDisplay();
        createResetButtonSticks();
        return;
    }

    // Chama IA do math_f.js
    let pc = typeof calculaJogadaIA === 'function' ? calculaJogadaIA(currentSticks) : 1;
    currentSticks -= pc;

    if (currentSticks === 0) {
        msg.innerText = `Você tirou ${u}. O PC tirou ${pc} e perdeu! VOCÊ VENCEU! 🎉`;
        updateDisplay();
        createResetButtonSticks();
    } else {
        msg.innerText = `Você tirou ${u}. O computador retirou ${pc}. Sua vez!`;
        updateDisplay();
    }
}

function createResetButtonSticks() {
    const container = document.getElementById('sticks-msg').parentElement;
    if (!document.getElementById('reset-btn-sticks')) {
        const btn = document.createElement('button');
        btn.id = 'reset-btn-sticks';
        btn.innerText = "Jogar Novamente";
        btn.style.marginTop = "15px";
        btn.onclick = () => {
            currentSticks = 21;
            document.getElementById('sticks-msg').innerText = "";
            document.getElementById('stick-input').value = 1;
            updateDisplay();
            btn.remove();
        };
        container.appendChild(btn);
    }
}


/* ========================================================
   2. JOGO DO CAMPO MINADO
   (Baseado na matriz em CampoMinado.c do autor)
   ======================================================== */
let msBoard = [];    // Matriz lógica (-1 = Bomba, 0-8 = Adjacentes)
let msState = [];    // Matriz de interface (0 = fechado, 1 = aberto, 2 = bandeira)
let msRows, msCols, msBombs;
let msFlagsUsed = 0;
let msGameOver = false;
let msFirstClick = true;

// Inicia a partida alocando memória (arrays) assim como a alloc() do C
function startMinesweeper() {
    msRows = parseInt(document.getElementById('ms-rows').value);
    msCols = parseInt(document.getElementById('ms-cols').value);
    msBombs = parseInt(document.getElementById('ms-bombs').value);

    // Validações
    if (msRows < 5 || msCols < 5) { alert("Mínimo 5x5!"); return; }
    if (msBombs >= msRows * msCols) { alert("Muitas bombas!"); return; }

    msGameOver = false;
    msFirstClick = true;
    msFlagsUsed = 0;
    
    document.getElementById('ms-msg').innerText = "";
    document.getElementById('ms-bomb-count').innerText = msBombs;
    document.getElementById('ms-flag-count').innerText = msFlagsUsed;

    // Inicializa as Matrizes de Lógica e Estado
    msBoard = Array(msRows).fill().map(() => Array(msCols).fill(0));
    msState = Array(msRows).fill().map(() => Array(msCols).fill(0));

    renderBoard();
}

// Renderiza o tabuleiro no HTML
function renderBoard() {
    const boardEl = document.getElementById('ms-board');
    boardEl.style.gridTemplateColumns = `repeat(${msCols}, 30px)`;
    boardEl.innerHTML = '';

    for (let r = 0; r < msRows; r++) {
        for (let c = 0; c < msCols; c++) {
            const cell = document.createElement('div');
            cell.classList.add('ms-cell');
            
            // Impede menu de contexto ao clicar com botão direito
            cell.oncontextmenu = (e) => { e.preventDefault(); toggleFlag(r, c); };
            cell.onclick = () => openCell(r, c);

            // Atualiza visual baseado no estado (0=fechado, 1=aberto, 2=bandeira)
            if (msState[r][c] === 1) {
                cell.classList.add('opened');
                if (msBoard[r][c] === -1) {
                    cell.classList.add('bomb');
                    cell.innerText = '💣';
                } else if (msBoard[r][c] > 0) {
                    cell.innerText = msBoard[r][c];
                    cell.classList.add(`ms-c${msBoard[r][c]}`); // Cor do número
                }
            } else if (msState[r][c] === 2) {
                cell.classList.add('flag');
                cell.innerText = '🚩';
            }

            boardEl.appendChild(cell);
        }
    }
}

// Distribui bombas de forma aleatória garantindo que o 1º clique seja seguro
function placeBombs(firstR, firstC) {
    let bombsPlaced = 0;
    while (bombsPlaced < msBombs) {
        let r = Math.floor(Math.random() * msRows);
        let c = Math.floor(Math.random() * msCols);
        
        // Evita por bomba onde já tem, ou no local do primeiro clique
        if (msBoard[r][c] !== -1 && !(r === firstR && c === firstC)) {
            msBoard[r][c] = -1;
            bombsPlaced++;
            
            // Incrementa números ao redor da bomba (Equivalente ao num() do C)
            for (let i = -1; i <= 1; i++) {
                for (let j = -1; j <= 1; j++) {
                    if (r+i >= 0 && r+i < msRows && c+j >= 0 && c+j < msCols && msBoard[r+i][c+j] !== -1) {
                        msBoard[r+i][c+j]++;
                    }
                }
            }
        }
    }
}

// Equivalente a função recursiva abrir() do CampoMinado.c
function openCell(r, c) {
    if (msGameOver || r < 0 || r >= msRows || c < 0 || c >= msCols) return;
    if (msState[r][c] !== 0) return; // Se já ta aberto ou com bandeira, ignora

    if (msFirstClick) {
        placeBombs(r, c);
        msFirstClick = false;
    }

    msState[r][c] = 1; // Marca como aberto

    // Clicou em bomba
    if (msBoard[r][c] === -1) {
        msGameOver = true;
        document.getElementById('ms-msg').innerText = "💥 BOOM! Você Perdeu!";
        revealAllBombs();
        renderBoard();
        return;
    }

    // Se clicou em vazio, faz a recursividade (Flood Fill)
    if (msBoard[r][c] === 0) {
        for (let i = -1; i <= 1; i++) {
            for (let j = -1; j <= 1; j++) {
                openCell(r + i, c + j);
            }
        }
    }

    renderBoard();
    checkWinCondition();
}

// Equivalente a função ban() do C
function toggleFlag(r, c) {
    if (msGameOver || msState[r][c] === 1) return;

    if (msState[r][c] === 0) {
        msState[r][c] = 2; // Põe Bandeira
        msFlagsUsed++;
    } else if (msState[r][c] === 2) {
        msState[r][c] = 0; // Tira Bandeira
        msFlagsUsed--;
    }

    document.getElementById('ms-flag-count').innerText = msFlagsUsed;
    renderBoard();
}

function revealAllBombs() {
    for (let r = 0; r < msRows; r++) {
        for (let c = 0; c < msCols; c++) {
            if (msBoard[r][c] === -1) msState[r][c] = 1;
        }
    }
}

function checkWinCondition() {
    let closedOrFlagged = 0;
    for (let r = 0; r < msRows; r++) {
        for (let c = 0; c < msCols; c++) {
            if (msState[r][c] !== 1) closedOrFlagged++;
        }
    }
    
    // Se a quantidade de locais fechados/bandeira for igual a qt de bombas, ganhou!
    if (closedOrFlagged === msBombs) {
        msGameOver = true;
        document.getElementById('ms-msg').innerText = "🏆 PARABÉNS! Você Venceu!";
        document.getElementById('ms-msg').style.color = "#4CAF50";
        revealAllBombs();
        renderBoard();
    }
}

// Inicia tudo no carregamento da página
document.addEventListener('DOMContentLoaded', () => {
    updateDisplay();
    startMinesweeper();
});