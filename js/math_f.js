/* ========================================================
   math_f.js
   Biblioteca de cálculos lógicos e IA matemática pura
   (Equivalente lógico inspirado no math_f.h)
   ======================================================== */

/**
 * Função que calcula a jogada perfeita da Inteligência Artificial.
 * Recebe a quantidade de palitos na mesa e retorna quantos tirar.
 */
function calculaJogadaIA(palitosRestantes) {
    let k = palitosRestantes;
    let pc = 0;

    // A exata mesma lógica condicional do VintiumPalitusGame.c
    if (k > 16 && k < 21) {
        pc = k - 16;
    } 
    else if (k > 11 && k < 16) {
        pc = k - 11;
    } 
    else if (k < 11 && k > 6) {
        pc = k - 6;
    } 
    else if (k < 6) {
        pc = k - 1;
    } 
    else {
        // Quando o jogador acerta o "número múltiplo de 5 + 1", a IA joga 1 para forçar o erro
        pc = 1; 
    }

    return pc;
}