#ifndef MORSE_F_H
#define MORSE_F_H

#include <stdlib.h>
#include "string_f.h"

typedef struct {
    char letra;
    int codigo_interno;
} MorseMap;

// Tabela Lookup Otimizada (Preserva os valores numéricos criados pelo autor original)
static const MorseMap M_TABLE[] = {
    {'a', 12},   {'b', 2111}, {'c', 2121}, {'d', 211},  {'e', 1},
    {'f', 1121}, {'g', 221},  {'h', 1111}, {'i', 11},   {'j', 1222},
    {'k', 212},  {'l', 1211}, {'m', 22},   {'n', 21},   {'o', 222},
    {'p', 1221}, {'q', 2212}, {'r', 121},  {'s', 111},  {'t', 2},
    {'u', 112},  {'v', 1112}, {'w', 122},  {'x', 2112}, {'y', 2122},
    {'z', 2211}, {' ', 4},    {'0', 22222},{'1', 12222},{'2', 11222},
    {'3', 11122},{'4', 11112},{'5', 11111},{'6', 21111},{'7', 22111},
    {'8', 22211},{'9', 22221},{'.', 121212},{',', 221122},{'?', 112211},
    {'-', 211112},{':', 222111},{';', 212121},{'\'', 122221},{'/', 21121},
    {'(', 21221},{')', 212212}
};
#define M_SIZE (sizeof(M_TABLE)/sizeof(M_TABLE[0]))

// Funções utilitárias da Lookup Table
char get_letra_f(int k) {
    for(int i=0; i<M_SIZE; i++) if(M_TABLE[i].codigo_interno == k) return M_TABLE[i].letra;
    return '\0';
}

int get_codigo_f(char c) {
    for(int i=0; i<M_SIZE; i++) if(M_TABLE[i].letra == c) return M_TABLE[i].codigo_interno;
    return 0;
}

// identifica se a string esta em morse ou nao
int mora(char s[]) {
    int i, j = 0;

    for (i = 0; i < len(s); i++) {
        if (s[i] == '.' || s[i] == '/' || s[i] == '-' || s[i] == ' ') j++;
    }

    if (j == i) return 1;
    return 0;
}

// Converte código morse para escrita
void mtoa(char m[], char *s) {
    int i, j, k = 0, c = 0, y;
    char *cm, *cm1, let[10];

    cm = (char *)calloc(len(m), 1);
    cm1 = (char *)calloc(len(m), 1);

    for (i = k; i < len(m); i++, k++) {
        if (m[i] == '.') { cm[k] = '1'; }
        else if (m[i] == '-') { cm[k] = '2'; }
        else if (m[i] == ' ') {
            cm[k] = '3';
            if (m[i + 1] == ' ') {
                k++;
                cm[k] = '4';
            }
            c++;
        }
        else if (m[i] == '/') { cm[k] = '4'; }
    }

    for (i = 0; i <= c; i++) {
        while (find('3', cm) == 0) {
            cpy(&cm[1], cm1);
            cpy(cm1, cm);
        }

        j = find('3', cm);

        if (i == c || find('3', cm) < 0) {
            cpy(cm, let);
            c = 0;
        } else {
            for (y = 0; y < j; y++) {
                let[y] = cm[y];
            }
            let[y] = '\0';
        }

        k = atoi(let);

        // Busca utilizando a Lookup Table
        s[i] = get_letra_f(k);
        
        cpy(&cm[j + 1], cm1);
        cpy(cm1, cm);
    }

    s[i] = '\0';

    uplw(s, 2);
    uplw(&s[1], 0);

    free(cm);
    free(cm1);
}

// Converte a escrita para codigo morse
void atom(char a[], char *s) {
    int i, j, k;

    s[0] = '\0';
    uplw(a, 0);

    for (i = 0; i < len(a); i++) {
        
        // Busca utilizando a Lookup Table
        k = get_codigo_f(a[i]);

        if (k == 4) {
            j = len(s);
            s[j] = ' ';
            s[j + 1] = '/';
            s[j + 2] = '\0';
        } else if (k != 0) {
            itoa(k, &s[len(s)]);
        }

        j = len(s);
        s[j] = ' ';
        s[j + 1] = '\0';
    }

    for (i = 0; i < len(s); i++) {
        if (s[i] == '1') {
            s[i] = '.';
        } else if (s[i] == '2') {
            s[i] = '-';
        }
    }
}

#endif