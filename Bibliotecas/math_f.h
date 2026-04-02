#ifndef MATH_F_H
#define MATH_F_H

#include <stdio.h>

double pot(double base, double expo);
long int inteiro(double n);
double prox(double x, double y, double z);

// Calcula a raiz r de n
double raiz(double radical, double n) {
    double ant, result, k, sinal;
    int part_I;
    const double focus = 0.000001; // Variável de precisão de casas decimas (6 casas é o máximo)

    result = 0;
    sinal = 0;
    part_I = radical;

    // Retorna n caso o radical/expoente seja 1 e imprime uma mensagem de erro caso seja 0, nesse caso retornará 0
    if (radical == 1) {
        return n;
    }
    if (radical == 0) {
        // return 1/0; // Pois 0v(5) = 5^(1/0)

        // Para não crachar o programa

        printf("\n--ERRO--");
        printf("\n\nNao existe raiz zerezima, pois isso implicaria que o numero dentro da raiz estaria elevado a uma dicisão por zero\n\n");

        return 0;
    }

    // Caso o radical seja negativo, n recebe seu inverso para o radical ficar positivo
    if (radical < 0) {
        radical = -radical;
        n = pot(n, -1);
    }

    // Calculo de raiz inteira(no if) e de raiz real(no else)
    if (radical == part_I) {
        /*
            Caso n seja negativo e o radical é impar "anotamos", na variável sinal, 
            que o resultado final é negativo e ignoramos o sinal para o calculo
        */
        if (n < 0 && part_I % 2 != 0) {
            n = -n;
            sinal = 1;
        }

        /*
            Verifica se result elevado ao radical da raiz é menor que n, 
            atualizado lentamente o seu valor. 
            Ao fim do "while" ele ou será a raiz de n ou estará próximo dela,
            sendo maior que a mesma. 
        */
        while (pot(result, radical) < n) {
            result += 1;
        }

        result -= 1;

        while (pot(result, radical) < n) {
            result += focus;
        }

        // Verificando se o arredondamento da raiz é para mais ou para menos e se o valor encontrado é a raiz
        ant = result - focus;
        k = prox(n, pot(result, radical), pot(ant, radical));

        if (k == pot(ant, radical)) {
            result = ant;
        }
    } else {
        //transforma a raiz em potencia para representar o expoente racional em forma de fração
        result = pot(n, (1 / radical));
    }

    // Verifica se está "anotado" que o resultado será negativo
    if (sinal == 1) {
        result = -result;
    }

    return result;
}

// Calcula base elevado a expo
double pot(double base, double expo) {
    double k, q, s = 0, result;
    long int part_I;

    if (expo < 0) {
        s = 1;
        expo = -expo;
    }

    part_I = expo;

    if (expo == 0) return 1;
    if (expo == 1) return base;

    if (part_I == expo) {
        result = 1;
        for (part_I = 1; part_I <= expo; part_I++) {
            result *= base;
        }
    } else {
        /*
            Como o expoente não é inteiro, iremos achar números inteiros para representa-lo por fração,
            para com eles calcular a potencia.
            Caso ele seja irracional o usuário não conseguirá o número como parâmetro e irá arredonda-lo,
            o que fará com que recebamos apenas números racionais.
        */
        k = expo;
        q = 1;

        while (!inteiro(k)) {
            k *= 10;
            q *= 10;
        }

        result = raiz(q, pot(base, k));
    }

    if (s == 1) {
        result = 1 / result;
    }

    return result;
}

// Responde a pergunta: Quem e mais proximo de x? y ou z?
double prox(double x, double y, double z) {
    double i, j;

    i = x - y;
    j = x - z;

    if (i < 0) i = -i;
    if (j < 0) j = -j;

    if (i > j) return z;
    else return y;
}

// Retorna um número diferente de 0 caso o número passado como parrametro seja inteiro, se não retorna 0
long int inteiro(double n) {
    long int x;
    x = n;

    if (n == 0) return 1;
    else if (n == x) return x;

    return 0;
}

// Calcula n!
int fat(int n) {
    int i, j = 1;
    for (i = 1; i <= n; i++) j = j * i;
    return j;
}

// soma numeros de x a y
int some(int x, int y) {
    int i, j = 0;
    if (x > y) {
        i = x; x = y; y = i;
    }
    for (i = x; i <= y; i++) j = j + i;
    return j;
}

// multiplica numeros de x a y
int prode(int x, int y) {
    int i, j = 1;
    if (x > y) {
        i = x; x = y; y = i;
    }
    for (i = x; i <= y; i++) j *= i;
    return j;
}

// Arredonda um double
double arr(double x) {
    long int part_I;
    double i, j, q, n;
    n = x;

    if (x != 0) part_I = inteiro(x);

    for (i = 0; !inteiro(n) && i < 7; i++) n *= 10;

    q = (1 / (pot(10, i)));

    if (q != 1) {
        q *= 10;
        for (i = 0; i < x; i += q);
        j = i - q;
        return part_I + prox(x, i, j);
    }
    return x;
}

// Acha dois números inteiros que divididos resultem em n ou próximo dele
void achaInt(long int *i, long int *q, double n) {
    long int j;
    for (j = 1; !inteiro(n); j *= 10) n *= 10;
    *i = n; *q = j;
}

// Calcula o módulo de n
double mod(double n) {
    if (n < 0) n = -n;
    return n;
}

// Calcula logaritmos inteiros
int logarit(int b, int n) {
    int i;
    for (i = 0; pot(b, i) < n; i++);
    if (n == pot(b, i)) return i;
    return -1;
}

// Calcula o logaritmo de num na base desejada (padrão 10)
double log(double num, double base) {
    double result = 0, focus = 0.000001; // Precisão de 6 casas decimais
    
    // Primeira verificação: Se a base é igual ao número, o log é sempre 1
    if (num == base) return 1;

    // Verificação de validade dos parâmetros conforme solicitado
    // Nota: Logaritmos exigem base positiva e diferente de 1, e logaritmando positivo
    if (base <= 1 || num <= 0) {
        printf("\n--ERRO--");
        printf("\n\nParametros invalidos para logaritmo. A base deve ser > 1 e o numero deve ser > 0.\n\n");
        return 0;
    }

    /* Utiliza a lógica de aproximação lenta similar à função raiz() do autor.
        Verifica se a base elevada ao resultado atual ainda é menor que o número alvo.
    */
    // Parte inteira do logaritmo
    while (pot(base, result) < num) result += 1;
    
    result -= 1; // Retorna um passo para refinar com decimais

    // Refinamento decimal para precisão de 6 casas
    while (pot(base, result) < num) result += focus;

    return result;
}

// Inverte a ordem dos dígitoa de um numero inteiro
int invi(int n) {
    int i, j, m, n1;

    if (n == 0) return n;

    n1 = n;
    for (i = 0; n >= 1; i++) n /= 10;

    n = n1;
    n /= 10;
    m = n;
    n *= 10;
    n = n1 - n;

    for (j = 0; j < i - 1; j++) n *= 10;

    return n + invi(m);
}

#endif