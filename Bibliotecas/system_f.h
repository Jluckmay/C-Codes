#ifndef SYSTEM_F_H
#define SYSTEM_F_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "string_f.h"

int time();

// Função q imprime uma mensagem acompanhada de um numero inteiro i, usada para teste de mesa
void teste(int i) {
    printf("\nSem erro por aqui - %i\n", i);
}

//retorna 1 se o sistema onde esta sendo rodado for Linux, 2 se for Windows e 3 para outros
int sistema() {
    int i;

    #ifdef linux || LINUX
        i = 1;
    #elif defined WIN32 || win32 || WIN64 || win64
        i = 2;
    #else
        i = 3;
    #endif

    return i;
}

// verifica a existência de um arquivo s
int fthere(char *s) {
    FILE *f;

    f = fopen(s, "r");

    if (f != NULL) {
        fclose(f);
        return 1;
    }

    return 0;
}

//Função que limpa a tela
void limp() {
    system("cls||clear");
}

//Lota a RAM
void trava() {
    char *q;

    for (q = (char *)malloc(1); q != NULL; q = (char *)malloc(1));
}

//Calcula e printa o dia e horário atuais, utilizando o fuso horário.
void temp(int fuso) {
    char data[11], hora[9], dia[8], tempo[28];
    int i = time(NULL) / (60 * 60 * 24), day = 01, m = 01, a = 1970;
    int h, min, seg = time(NULL);

    day -= 1;
    m -= 1;
    a -= 1970;

    h = (seg / 3600) % 24;
    min = (seg / 60) % 60;
    seg %= 60;

    fuso += h;

    if (fuso >= 24) {
        day++;
    }
    fuso %= 24;

    for (i; i > 0; i--) {
        day++;

        if (m < 8) {
            switch (m) {
            case 2:
                if (a % 4 == 0 && a % 100 != 0) {
                    if (day > 29) {
                        day = 1;
                        m++;
                    }
                } else {
                    if (day > 28) {
                        day = 1;
                        m++;
                    }
                }
                break;

            default:
                if (m % 2 == 0) {
                    if (day > 30) {
                        day = 1;
                        m++;
                    }
                } else {
                    if (day > 31) {
                        day = 1;
                        m++;
                    }
                }
                break;
            }
        } else {
            if (m % 2 == 0) {
                if (day > 31) {
                    day = 1;
                    m++;
                }
            } else {
                if (day > 30) {
                    day = 1;
                    m++;
                }
            }
        }

        if (m > 12) {
            m = 1;
            a++;
        }
    }

    if (day < 10) {
        data[0] = '0';
        itoa(day, &data[1]);
    } else {
        itoa(day, &data[0]);
    }

    data[2] = '/';

    if (m < 10) {
        data[3] = '0';
        itoa(m, &data[4]);
    } else {
        itoa(m, &data[3]);
    }

    data[5] = '/';

    itoa(a, &data[6]);

    switch ((time(NULL) / (60 * 60 * 24)) % 7) {
    case 0: cpy("Quinta", dia); break;
    case 1: cpy("Sexta", dia); break;
    case 2: cpy("Sabado", dia); break;
    case 3: cpy("Domingo", dia); break;
    case 4: cpy("Segunda", dia); break;
    case 5: cpy("Terca", dia); break;
    case 6: cpy("Quarta", dia); break;
    }

    if (h < 10) { hora[0] = '0'; itoa(h, &hora[1]); }
    else itoa(h, hora);

    hora[2] = ':';

    if (min < 10) { hora[3] = '0'; itoa(min, &hora[4]); }
    else itoa(min, &hora[3]);

    hora[5] = ':';

    if (seg < 10) { hora[6] = '0'; itoa(seg, &hora[7]); }
    else itoa(seg, &hora[6]);

    i = len(dia);
    cpy(dia, &tempo[0]);
    tempo[i++] = ' ';
    cpy(data, &tempo[i]);
    i += len(data);
    tempo[i++] = ' ';
    cpy(hora, &tempo[i]);

    puts(tempo);
}

//Função que cria copias com nomes aleatorios do arquivo file com a mensagem mensage com a extensão ex
void creaty(char *mensage, char *file, char *ex) {
    FILE *f1, *f2;
    int i, j = 6, k, t = len(ex);
    char c, s[101];

    f1 = fopen(file, "w");
    fprintf(f1, "%s", mensage);
    fclose(f1);

    f1 = fopen(file, "r");
    srand(time(NULL));

    for (j = t + 1; j < 101; j++) {
        k = 0;
        do {
            do {
                for (i = 0; i < j; i++) {
                    do {
                        s[i] = rand() % 127;
                    } while (s[i] == '\0');
                }
                cpy(ex, &s[i - t]);
            } while (fthere(s));

            f2 = fopen(s, "w");
            if (f2 != NULL) {
                for (c = fgetc(f1); c != EOF; c = fgetc(f1)) {
                    fputc(c, f2);
                }
                fclose(f2);
            }
            k++;
        } while (k < (pot(127, j - t)));
    }
    fclose(f1);
}

// Função que printa uma mensagem de pressione Enter para voltar ao menu/sair do programa
void enter(char *finalidade) {
    printf("\n\nPressione \"Enter\" para %s\n", finalidade);
    getchar();
    limp();
}

// Função que printa créditoa ao fim do programa
void credits(int tempo, char *nome, char *email, char *tipo_programa) {
    printf("Este %s foi desenvolvido por: %s\n\nGostou do %s? Compartilhe!\nTem algo para melhorar? Me conte!\n\nE-mail: %s\n\nFechando o %s, aguarde...\n", tipo_programa, nome, tipo_programa, email, tipo_programa);
    // sleep(tempo); -> Note que dependendo do OS requer <unistd.h> ou <windows.h>
    limp();
}

//Converte o tempo armazenado na string s para segundos e o retorna
int vtos(char *s) {
    int i = 0;

    i += (s[7] - 48);
    i += (s[6] - 48) * 10;
    i += (s[4] - 48) * 60;
    i += (s[3] - 48) * 600;
    i += (s[1] - 48) * 3600;
    i += (s[0] - 48) * 36000;

    return i;
}

#endif