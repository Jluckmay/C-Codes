#ifndef SYSTEM_F_H
#define SYSTEM_F_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "string_f.h"

// Função q imprime uma mensagem acompanhada de um numero inteiro i, usada para teste de mesa
void teste(int i) {
    printf("\nSem erro por aqui - %i\n", i);
}

//retorna 1 se o sistema onde esta sendo rodado for Linux, 2 se for Windows e 3 para outros
int sistema() {
    int i;

    #if defined(__linux__) || defined(linux) || defined(LINUX)
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

// Converte o tempo armazenado na string s para segundos e o retorna
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

// Converte segundos para string
int stov(int segundos)
{
    int h, m, s;
    char tempo[9];

    h = segundos / 3600;
    m = (segundos % 3600) / 60;
    s = segundos % 60;

    if (h < 10) {
        tempo[0] = '0';
        itoa_f(h, &tempo[1]);
    } else {
        itoa_f(h, &tempo[0]);
    }

    tempo[2] = ':';

    if (m < 10) {
        tempo[3] = '0';
        itoa_f(m, &tempo[4]);
    } else {
        itoa_f(m, &tempo[3]);
    }

    tempo[5] = ':';

    if (s < 10) {
        tempo[6] = '0';
        itoa_f(s, &tempo[7]);
    } else {
        itoa_f(s, &tempo[6]);
    }

    tempo[8] = '\0';

    printf("%s", tempo);

    return 0;
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
        itoa_f(day, &data[1]);
    } else {
        itoa_f(day, &data[0]);
    }

    data[2] = '/';

    if (m < 10) {
        data[3] = '0';
        itoa_f(m, &data[4]);
    } else {
        itoa_f(m, &data[3]);
    }

    data[5] = '/';

    itoa_f(a, &data[6]);

    switch ((time(NULL) / (60 * 60 * 24)) % 7) {
    case 0: cpy("Quinta", dia); break;
    case 1: cpy("Sexta", dia); break;
    case 2: cpy("Sabado", dia); break;
    case 3: cpy("Domingo", dia); break;
    case 4: cpy("Segunda", dia); break;
    case 5: cpy("Terca", dia); break;
    case 6: cpy("Quarta", dia); break;
    }

    if (h < 10) { hora[0] = '0'; itoa_f(h, &hora[1]); }
    else itoa_f(h, hora);

    hora[2] = ':';

    if (min < 10) { hora[3] = '0'; itoa_f(min, &hora[4]); }
    else itoa_f(min, &hora[3]);

    hora[5] = ':';

    if (seg < 10) { hora[6] = '0'; itoa_f(seg, &hora[7]); }
    else itoa_f(seg, &hora[6]);

    i = len(dia);
    cpy(dia, &tempo[0]);
    tempo[i++] = ' ';
    cpy(data, &tempo[i]);
    i += len(data);
    tempo[i++] = ' ';
    cpy(hora, &tempo[i]);

    puts(tempo);
}


// Converte uma data para dias, representando a quantidade de dias passados desde 01/01/1970 até ela
int stod(char* data)
{
    int dia, mes, ano, total;

    // Tabela com a quantidade de dias antes do início de cada mês, considerando anos não bissextos
    static const int dias_antes_mes[] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
    };

    // Converção para inteiros
    dia = (data[0] - 48) * 10 + (data[1] - 48);
    mes = (data[3] - 48) * 10 + (data[4] - 48);
    ano = (data[6] - 48) * 1000 + (data[7] - 48) * 100 + (data[8] - 48) * 10 + (data[9] - 48);

    // Cálculo da diferença em dias
    total = 365 * (ano - 1) + (ano - 1) / 4 - (ano - 1) / 100 +
             (ano - 1) / 400 + dias_antes_mes[mes-1] + dia;

    // Verificação de ano bissexto
    if (mes > 2 && (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0))) total++;

    return total - 719163;
}

// Converte uma data para segundos, representando a quantidade de segundos passados desde 01/01/1970 até ela
int stosec(char* data)
{
    return stod(data) * 24 * 3600;
}

// Converte diferença de dias desde 01/01/1970 para data
char* dtos(int dias)
{
    static char data[11];
    int era, dia_era, ano_era, dia_ano, mes_calculo;
    int dia, mes, ano;

    dias += 719468;
    era = (dias >= 0 ? dias : dias - 146096) / 146097;
    dia_era = dias - era * 146097;
    ano_era = (dia_era - dia_era / 1460 + dia_era / 36524 - dia_era / 146096) / 365;
    ano = ano_era + era * 400;
    dia_ano = dia_era - (365 * ano_era + ano_era / 4 - ano_era / 100);
    mes_calculo = (5 * dia_ano + 2) / 153;
    dia = dia_ano - (153 * mes_calculo + 2) / 5 + 1;
    mes = mes_calculo + (mes_calculo < 10 ? 3 : -9);
    ano += mes <= 2;

    data[0] = (char)('0' + dia / 10);
    data[1] = (char)('0' + dia % 10);
    data[2] = '/';
    data[3] = (char)('0' + mes / 10);
    data[4] = (char)('0' + mes % 10);
    data[5] = '/';
    data[6] = (char)('0' + (ano / 1000) % 10);
    data[7] = (char)('0' + (ano / 100) % 10);
    data[8] = (char)('0' + (ano / 10) % 10);
    data[9] = (char)('0' + ano % 10);
    data[10] = '\0';

    return data;
}

// Converte a diferença em segundos desde 01/01/1970 em uma data
char* sectos(int segundos)
{
    int dias = segundos / 86400;

    if (segundos < 0 && segundos % 86400 != 0) dias--;

    return dtos(dias);
}

// Calcula a diferença em dias entre duas datas fornecidas no formato "DD/MM/AAAA". Retorno negativo indica que a primeira data é posterior à segunda.
int diff_datas(char *data1, char *data2) {

    int total1, total2, diferenca;

    // Cálculo do total de dias desde o início da era (01/01/0001) até cada data, considerando anos bissextos
    total1 = stod(data1);
    total2 = stod(data2);

    // Cálculo da diferença absoluta em dias entre as duas datas
    diferenca = total2 - total1;

    return diferenca;
}

// Indica o dia da semana de uma data dado a data atual. Datas no formato "DD/MM/AAAA" e dia da semana de 0 a 6
int dia_semana(char *data, char* hoje, int dia_sem_hoje)
{
    // 0 - Sábado | 1 - Domingo | 2 - Segunda | 3 - Terça | 4 - Quarta | 5 - Quinta | 6 - Sexta
    return (((diff_datas(hoje, data) + dia_sem_hoje) % 7) + 7) % 7;
}

// Indica o dia da semana de qualquer data
int semana_juliana(char *data)
{
    // 0 - Sábado | 1 - Domingo | 2 - Segunda | 3 - Terça | 4 - Quarta | 5 - Quinta | 6 - Sexta
    return dia_semana(data, "01/01/1970", 5); // 01/01/1970 foi uma quinta-feira
}

#endif
