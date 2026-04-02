#ifndef STRING_F_H
#define STRING_F_H

#include <stdlib.h>
#include "math_f.h"

// Função que mede comprimento da string s
int len(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++);
    return i;
}

// Função que copia x em y
void cpy(char x[], char *y) {
    int i, j = len(x);
    for (i = 0; i < j; i++) y[i] = x[i];
    y[j] = '\0';
}

// Função que diz se 2 strings são iguais.
int igual(char x[], char y[]) {
    int i, j;
    if (len(x) != len(y)) return 0;
    j = len(x);
    for (i = 0; ((i < j) && (x[i] == y[i])); i++);
    if (i == j) return 1;
    else return 0;
}

// Função que confere se uma string possui apenas numeros
int sorn(char s[]) {
    int i, j = 0;
    for (i = 0; ((i < len(s))); i++) {
        if ((s[i] == '.') || (s[i] == '0') || (s[i] == '1') || (s[i] == '2') || (s[i] == '3') || (s[i] == '4') || (s[i] == '5') || (s[i] == '6') || (s[i] == '7') || (s[i] == '8') || (s[i] == '9')) {
            j++;
        }
    }
    if ((j == i) && (j > 0)) { // se so tiver numeros retorna 0 se n, retorna 1
        return 0;
    } else {
        return 1;
    }
}

// confere se a string contem apenas um numeros inteiros, se sim retorna 1, se não retorna 0
int sori(char *s) {
    int i, j = 0, k;
    for (k = 0; s[k] != '\0'; k++);
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9') {
            j++;
        }
    }
    if (j == k) return 0;
    else return 1;
}

// Coloca a string s em minusculo se k<=0 e em maiúsculo se k>0
void uplw(char *s, double k) {
    int i;
    if (k <= 0) {
        for (i = 0; s[i] != '\0'; i++) {
            if (s[i] > 64 && s[i] < 91) s[i] += 32;
        }
    } else {
        for (i = 0; s[i] != '\0'; i++) {
            if (s[i] > 96 && s[i] < 123) s[i] -= 32;
        }
    }
}

// Converte im inteiro i para uma string s
void itoa(int i, char *s) {
    int j, l, u;
    double k;
    char *a;

    if (i < 0) {
        s[0] = '-';
        a = (s + 1);
        i = -i;
    } else {
        a = s;
    }

    k = i;
    for (j = 0; !(k < 1 && k >= 0); j++) k /= 10;
    u = i;

    for (i = 0; i < j; i++) {
        l = u / pot(10, j - (i + 1));
        a[i] = l + 48; //Jeito pratico

        /*
        Jeito antigo

        if(l==0) { a[i]='0'; }
        else if(l==1) { a[i]='1'; }
        else if(l==2) { a[i]='2'; }
        else if(l==3) { a[i]='3'; }
        else if(l==4) { a[i]='4'; }
        else if(l==5) { a[i]='5'; }
        else if(l==6) { a[i]='6'; }
        else if(l==7) { a[i]='7'; }
        else if(l==8) { a[i]='8'; }
        else if(l==9) { a[i]='9'; }
        */

        u -= l * (int)pot(10, j - (i + 1));
    }
    a[i] = '\0';
}

// Converte um double f para uma sting c
void ftoa(double f, char *c) {
    int i, j, k;
    double q, e;
    char *a;

    if (f < 0) {
        c[0] = '-';
        a = (c + 1);
        f = (f * (-1));
    } else {
        a = c;
    }

    q = f;
    for (i = 0; !((q < 1) && (q > 0)); i++) q /= 10;

    k = f;
    e = f - k;

    if (e != 0) {
        for (j = 0; !inteiro(e); j++) e = e * 10;
    }

    itoa(k, a);

    if (e != 0) {
        a[i] = '.';
        i++;
        itoa(e, (a + i));
    }
}

// Converte as virgulas(commas) de uma string em pontos(dots)
void comtodot(char *s) {
    int i;
    for (i = 0; i < len(s); i++) {
        if (s[i] == ',') s[i] = '.';
    }
}

// Converte os pontos(dots) de uma string em virgulas(commas)
void dottocom(char *s) {
    int i;
    for (i = 0; i < len(s); i++) {
        if (s[i] == '.') s[i] = ',';
    }
}

// Acha l em s, caso nao exista retorna um numero negativo, caso exista retorna a posição
int find(char l, char s[]) {
    int i;
    for (i = 0; s[i] != l && i < len(s); i++);
    if (i == len(s)) i = -i;
    return i;
}

//Inverte a ordem dos caracteres de uma string
void invs(char *s) {
    char *c;
    int i, j;
    c = (char *)calloc(len(s), 1);
    cpy(s, c);
    j = len(c) - 1;

    for (i = 0; i < len(c); i++) {
        s[i] = c[j];
        j--;
    }
    free(c);
}

// Converte numeros binarios para inteiros
int btoi(int i) {
    int j, k = i, w;
    char *q;

    if (i == 0) return i;

    for (j = 0; i != 0; j++) i /= 10;

    q = (char *)calloc(j + 1, 1);
    if (q == NULL) return -1;

    itoa(k, q);

    for (i = 0, k = 0, j--; i <= j; i++) {
        w = *(q + i + 1);
        *(q + i + 1) = '\0';
        k += atoi(q + i) * pot(2, j - i);
        *(q + i + 1) = w;
    }
    free(q);
    return k;
}

/*
// Converte inteiros para binário de forma recursiva
int itob(int n) 
{
    if( n == 1 || n == 0)
        return n;
    return 10*itob(n/2)+n%2;
}
*/

//Converte inteiros para binario sem recursividade
int itob(int b) {
    int i, j, k;
    char *q;

    for (i = 0, j = b; j > 0; i++, j /= 2);

    q = (char *)calloc(i + 1, 1);
    if (q == NULL) return -1;

    for (k = 0, j = b % 2; k < i; j = b % 2, k++) {
        *(q + k) = j + 48;
        b /= 2;
    }

    invs(q);
    i = atoi(q);
    free(q);

    return i;
}

//Converte reais para binario sem recursividade
char *bin(double n) {
    int i, j, k, b = n;
    char *q;

    if (!inteiro(n)) {
        q = bin(b);
        i = atoi(q);
        free(q);

        n -= b;
        b = i;
        for (j = 0; b > 0; j++, b /= 10);

        q = (char *)calloc(j + 7, 1);
        itoa(i, q);
        q[j] = '.';
        b = j;

        for (j = 0; j < 5 && n != 0; j++) {
            n *= 2;
            i = n;
            n -= i;
            *(q + j + b + 1) = i + 48;
        }
        *(q + j + b + 1) = '\0';
        return q;
    }

    for (i = 0, j = b; j > 0; i++, j /= 2);

    q = (char *)calloc(i + 1, 1);
    if (q == NULL) return NULL;

    for (k = 0, j = b % 2; k < i; j = b % 2, k++) {
        *(q + k) = j + 48;
        b /= 2;
    }

    invs(q);
    return q;
}

// Confere se a string contem caracteres especiais
int hva(char *c) {
    int i, j = 0;
    for (i = 0; i < len(c); i++) {
        if (c[i] != -61) j++;
    }
    if (j == i) return 0;
    return 1;
}

#endif