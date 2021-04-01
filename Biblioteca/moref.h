#include <stdlib.h>
#include <stdio.h>


// Funções criadas po João Lucas Mayrinck

int time();

// Calcula base elevado a expo
double pot(double base, double expo);

// Função q imprime uma mensagem acompanhada de um numero inteiro i, usada para teste de mesa
void teste(int i)
{
    printf("\nSem erro por aqui - %i\n", i);
}

//retorna 1 se o sistema onde esta sendo rodado for Linux, 2 se for Windows e 3 para outros
int sistema()
{
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
int fthere(char *s)
{
    FILE *f;

    f = fopen(s, "r");

    if (f != NULL)
    {
        fclose(f);
        return 1;
    }

    return 0;
}

//Função que limpa a tela
void limp()
{
    system("cls||clear");
}

// Função que mede comprimento da string s
int len(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        ;
    return i;
}

// Função que copia x em y
void cpy(char x[], char *y)
{
    int i, j = len(x);

    for (i = 0; i < j; i++)
        y[i] = x[i];

    y[j] = '\0';
}

// Função que diz se 2 strings são iguais.
int igual(char x[], char y[])
{
    int i, j, k;

    if (len(x) != len(y))
    {
        return 0;
    }

    j = len(x);

    for (i = 0; ((i < j) && (x[i] == y[i])); i++)
        ;

    if (i == j)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Função que confere se uma string possui apenas numeros
int sorn(char s[])
{
    int i, j = 0;
    for (i = 0; ((i < len(s))); i++)
    {
        if ((s[i] == '.') || (s[i] == '0') || (s[i] == '1') || (s[i] == '2') || (s[i] == '3') || (s[i] == '4') || (s[i] == '5') || (s[i] == '6') || (s[i] == '7') || (s[i] == '8') || (s[i] == '9'))
        {
            j++;
        }
    }

    if ((j == i) && (j > 0)) // se so tiver numeros retorna 0 se n, retorna 1
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Coloca a string s em minusculo se k<=0 e em maiúsculo se k>0
void uplw(char *s, double k)
{
    int i, j;

    if (k <= 0)
    {
        for (i = 0; s[i] != '\0'; i++)
        {
            if (s[i] > 64 && s[i] < 91)
            {
                s[i] += 32;
            }
        }
    }

    else
    {
        for (i = 0; s[i] != '\0'; i++)
        {
            if (s[i] > 96 && s[i] < 123)
            {
                s[i] -= 32;
            }
        }
    }
}

// Responde a pergunta: Quem e mais proximo de x? y ou z?
double prox(double x, double y, double z)
{
    double i, j;

    i = x - y;
    j = x - z;

    if (i < 0)
    {
        i = -i;
    }

    if (j < 0)
    {
        j = -j;
    }

    if (i > j)
    {
        return z;
    }

    else
    {
        return y;
    }
}

// Retorna um número diferente de 0 caso o número passado como parrametro seja inteiro, se não retorna 0
long int inteiro(double n)
{
    long int x;

    x = n;

    if (n == 0)
    {
        return 1;
    }
    else if (n == x)
    {
        return x;
    }

    return 0;
}

// confere se a string contem apenas um numeros inteiros, se sim retorna 1, se não retorna 0
int sori(char *s)
{
    int i, j = 0, k;

    for (k = 0; s[k] != '\0'; k++)
        ;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9')
        {
            j++;
        }
    }

    if (j == k)
    {
        return 0;
    }

    else
    {
        return 1;
    }
}

// Arredonda um double
double arr(double x)
{
    long int part_I;
    double i, j, q, n;

    n = x;

    if (x != 0)
    {
        part_I = inteiro(x);
    }

    for (i = 0; !inteiro(n) && i < 7; i++)
    {
        n *= 10;
    }

    q = (1 / (pot(10, i)));

    if (q != 1)
    {
        q *= 10;

        for (i = 0; i < x; i += q)
            ;

        j = i - q;

        return part_I + prox(x, i, j);
    }

    return x;
}

// Calcula a raiz r de n
double raiz(double radical, double n)
{
    double ant, result, k, q, sinal;
    int part_I, j;
    const double focus = 0.000001; // Variável de precisão de casas decimas (6 casas é o máximo)
    const int focus2 = 1000000;

    result = 0;
    sinal = 0;
    part_I = radical;

    // Retorna n caso o radical/expoente seja 1 e imprime uma mensagem de erro caso seja 0, nesse caso retornará 0
    if (radical == 1)
    {
        return n;
    }
    if (radical == 0)
    {
        // return 1/0; // Pois 0v(5) = 5^(1/0)

        // Para não crachar o programa

        printf("\n--ERRO--");
        printf("\n\nNao existe raiz zerezima, pois isso implicaria que o numero dentro da raiz estaria elevado a uma dicisão por zero\n\n");

        return 0;
    }

    // Caso o radical seja negativo, n recebe seu inverso para o radical ficar positivo
    if (radical < 0)
    {
        radical = -radical;
        n = pot(n, -1);
    }

    // Calculo de raiz inteira(no if) e de raiz real(no else)
    if (radical == part_I)
    {
        /*
            Caso n seja negativo e o radical é impar "anotamos", na variável sinal, 
            que o resultado final é negativo e ignoramos o sinal para o calculo
        */
        if (n < 0 && part_I % 2 != 0)
        {
            n = -n;
            sinal = 1;
        }

        /*
            Verifica se result elevado ao radical da raiz é menor que n, 
            atualizado lentamente o seu valor. 
            Ao fim do "while" ele ou será a raiz de n ou estará próximo dela,
            sendo maior que a mesma. 
        */
        while (pot(result, radical) < n)
        {
            result += 1;
        }

        result -= 1;

        while (pot(result, radical) < n)
        {
            result += focus;
        }

        // Verificando se o arredondamento da raiz é para mais ou para menos e se o valor encontrado é a raiz

        ant = result - focus;

        k = prox(n, pot(result, radical), pot(ant, radical));

        if (k == pot(ant, radical))
        {
            result = ant;
        }
    }
    else
    {
        //transforma a raiz em potencia para representar o expoente racional em forma de fração
        result = pot(n, (1 / radical));
    }

    // Verifica se está "anotado" que o resultado será negativo
    if (sinal == 1)
    {
        result = -result;
    }

    return result;
}

// Calcula base elevado a expo
double pot(double base, double expo)
{
    double k, q, s = 0, result;
    long int part_I, j;
    const long int focus = 10000000000;

    if (expo < 0)
    {
        s = 1;
        expo = -expo;
    }

    part_I = expo;

    if (expo == 0)
    {
        return 1;
    }
    if (expo == 1)
    {
        return base;
    }

    if (part_I == expo)
    {
        result = 1;
        for (part_I = 1; part_I <= expo; part_I++)
        {
            result *= base;
        }
    }
    else
    {
        /*
            Como o expoente não é inteiro, iremos achar números inteiros para representa-lo por fração,
            para com eles calcular a potencia.
            Caso ele seja irracional o usuário não conseguirá o número como parâmetro e irá arredonda-lo,
            o que fará com que recebamos apenas números racionais.
        */

        k = expo;
        q = 1;

        while (!inteiro(k))
        {
            k *= 10;
            q *= 10;
        }

        result = raiz(q, pot(base, k));
    }

    if (s == 1)
    {
        result = 1 / result;
    }

    return result;
}

// Converte im inteiro i para uma string s
void itoa(int i, char *s)
{
    int j, l, u;
    double k, p;
    char *a;

    if (i < 0)
    {
        s[0] = '-';
        a = (s + 1);
        i = -i;
    }
    else
    {
        a = s;
    }

    k = i;

    for (j = 0; !(k < 1 && k >= 0); j++)
    {
        k /= 10;
    }

    u = i;

    for (i = 0; i < j; i++)
    {
        l = u / pot(10, j - (i + 1));

        a[i] = l + 48; //Jeito pratico

        /*

        Jeito antigo

        if(l==0)
        {
            a[i]='0';
        }

        else if(l==1)
        {
            a[i]='1';
        }

        else if(l==2)
        {
            a[i]='2';
        }

        else if(l==3)
        {
            a[i]='3';
        }

        else if(l==4)
        {
            a[i]='4';
        }

        else if(l==5)
        {
            a[i]='5';
        }

        else if(l==6)
        {
            a[i]='6';
        }

        else if(l==7)
        {
            a[i]='7';
        }

        else if(l==8)
        {
            a[i]='8';
        }

        else if(l==9)
        {
            a[i]='9';
        }*/

        u -= l * (int)pot(10, j - (i + 1));
    }

    a[i] = '\0';
}

// Converte as virgulas(commas) de uma string em pontos(dots)
void comtodot(char *s)
{
    int i;

    for (i = 0; i < len(s); i++)
    {
        if (s[i] == ',')
            s[i] = '.';
    }
}

// Converte os pontos(dots) de uma string em virgulas(commas)
void dottocom(char *s)
{
    int i;

    for (i = 0; i < len(s); i++)
    {
        if (s[i] == '.')
            s[i] = ',';
    }
}

// Converte um double f para uma sting c
void ftoa(double f, char *c)
{
    int i, j, k;
    double q, w, e;
    char *a;

    if (f < 0)
    {
        c[0] = '-';
        a = (c + 1);
        f = (f * (-1));
    }
    else
    {
        a = c;
    }

    q = f;

    for (i = 0; !((q < 1) && (q > 0)); i++)
    {
        q /= 10;
    }

    k = f;

    e = f - k;

    if (e != 0)
        for (j = 0; !inteiro(e); j++)
        {
            e = e * 10;
        }

    itoa(k, a);

    if (e != 0)
    {
        a[i] = '.';

        i++;

        itoa(e, (a + i));
    }
}

// Acha l em s, caso nao exista retorna um numero negativo, caso exista retorna a posição
int find(char l, char s[])
{
    int i;

    for (i = 0; s[i] != l && i < len(s); i++)
        ;

    if (i == len(s))
    {
        i = -i;
    }

    return i;
}

// Calcula n!
int fat(int n)
{
    int i, j = 1;

    for (i = 1; i <= n; i++)
    {
        j = j * i;
    }

    return j;
}

// soma numeros de x a y
int some(int x, int y)
{
    int i, j = 0;

    if (x > y)
    {
        i = x;
        x = y;
        y = i;
    }

    for (i = x; i <= y; i++)
    {
        j = j + i;
    }

    return j;
}

// multiplica numeros de x a y
int prode(int x, int y)
{
    int i, j = 1;

    if (x > y)
    {
        i = x;
        x = y;
        y = i;
    }

    for (i = x; i <= y; i++)
    {
        j *= i;
    }

    return j;
}

// identifica se a string esta em morse ou nao
int mora(char s[])
{
    int i, j = 0;

    for (i = 0; i < len(s); i++)
    {
        if (s[i] == '.' || s[i] == '/' || s[i] == '-' || s[i] == ' ')
            j++;
    }

    if (j == i)
    {
        return 1;
    }

    return 0;
}

// Converte código morse para escrita
void mtoa(char m[], char *s)
{
    int i, j, k = 0, c = 0, y;
    char *cm, *cm1, let[10];

    cm = (char *)calloc(len(m), 1);
    cm1 = (char *)calloc(len(m), 1);

    for (i = k; i < len(m); i++, k++)
    {
        if (m[i] == '.')
        {
            cm[k] = '1';
        }

        else if (m[i] == '-')
        {
            cm[k] = '2';
        }

        else if (m[i] == ' ')
        {
            cm[k] = '3';

            if (m[i + 1] == ' ')
            {
                k++;
                cm[k] = '4';
            }

            c++;
        }

        else if (m[i] == '/')
        {
            cm[k] = '4';
        }
    }

    for (i = 0; i <= c; i++)
    {
        while (find('3', cm) == 0)
        {
            cpy(&cm[1], cm1);
            cpy(cm1, cm);
        }

        j = find('3', cm);

        if (i == c || find('3', cm) < 0)
        {
            cpy(cm, let);
            c = 0;
        }

        else
        {
            for (y = 0; y < j; y++)
            {
                let[y] = cm[y];
            }

            let[y] = '\0';
        }

        k = atoi(let);

        if (k == 12)
        {
            s[i] = 'a';
        }

        else if (k == 2111)
        {
            s[i] = 'b';
        }

        else if (k == 2121)
        {
            s[i] = 'c';
        }

        else if (k == 211)
        {
            s[i] = 'd';
        }

        else if (k == 1)
        {
            s[i] = 'e';
        }

        else if (k == 1121)
        {
            s[i] = 'f';
        }

        else if (k == 221)
        {
            s[i] = 'g';
        }

        else if (k == 1111)
        {
            s[i] = 'h';
        }

        else if (k == 11)
        {
            s[i] = 'i';
        }

        else if (k == 1222)
        {
            s[i] = 'j';
        }

        else if (k == 212)
        {
            s[i] = 'k';
        }

        else if (k == 1211)
        {
            s[i] = 'l';
        }

        else if (k == 22)
        {
            s[i] = 'm';
        }

        else if (k == 21)
        {
            s[i] = 'n';
        }

        else if (k == 222)
        {
            s[i] = 'o';
        }

        else if (k == 1221)
        {
            s[i] = 'p';
        }

        else if (k == 2212)
        {
            s[i] = 'q';
        }

        else if (k == 121)
        {
            s[i] = 'r';
        }

        else if (k == 111)
        {
            s[i] = 's';
        }

        else if (k == 2)
        {
            s[i] = 't';
        }

        else if (k == 112)
        {
            s[i] = 'u';
        }

        else if (k == 1112)
        {
            s[i] = 'v';
        }

        else if (k == 122)
        {
            s[i] = 'w';
        }

        else if (k == 2112)
        {
            s[i] = 'x';
        }

        else if (k == 2122)
        {
            s[i] = 'y';
        }

        else if (k == 2211)
        {
            s[i] = 'z';
        }

        else if (k == 12222)
        {
            s[i] = '1';
        }

        else if (k == 11222)
        {
            s[i] = '2';
        }

        else if (k == 11122)
        {
            s[i] = '3';
        }

        else if (k == 11112)
        {
            s[i] = '4';
        }

        else if (k == 11111)
        {
            s[i] = '5';
        }

        else if (k == 21111)
        {
            s[i] = '6';
        }

        else if (k == 22111)
        {
            s[i] = '7';
        }

        else if (k == 22211)
        {
            s[i] = '8';
        }

        else if (k == 22221)
        {
            s[i] = '9';
        }

        else if (k == 22222)
        {
            s[i] = '0';
        }

        else if (k == 4)
        {
            s[i] = ' ';
        }

        else if (k == 112211)
        {
            s[i] = '?';
        }

        else if (k == 221122)
        {
            s[i] = ',';
        }

        else if (k == 121212)
        {
            s[i] = '.';
        }

        else if (k == 211112)
        {
            s[i] = '-';
        }

        else if (k == 222111)
        {
            s[i] = ':';
        }

        else if (k == 212121)
        {
            s[i] = ';';
        }

        else if (k == 122221)
        {
            s[i] = '\'';
        }

        else if (k == 21121)
        {
            s[i] = '/';
        }

        else if (k == 21221)
        {
            s[i] = '(';
        }

        else if (k == 212212)
        {
            s[i] = ')';
        }
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
void atom(char a[], char *s)
{
    int i, j, k;

    s[0] = '\0';
    uplw(a, 0);

    for (i = 0; i < len(a); i++)
    {
        if (a[i] == 'a')
        {
            k = 12;
        }

        else if (a[i] == 'b')
        {
            k = 2111;
        }

        else if (a[i] == 'c')
        {
            k = 2121;
        }

        else if (a[i] == 'd')
        {
            k = 211;
        }

        else if (a[i] == 'e')
        {
            k = 1;
        }

        else if (a[i] == 'f')
        {
            k = 1121;
        }

        else if (a[i] == 'g')
        {
            k = 221;
        }

        else if (a[i] == 'h')
        {
            k = 1111;
        }

        else if (a[i] == 'i')
        {
            k = 11;
        }

        else if (a[i] == 'j')
        {
            k = 1222;
        }

        else if (a[i] == 'k')
        {
            k = 212;
        }

        else if (a[i] == 'l')
        {
            k = 1211;
        }

        else if (a[i] == 'm')
        {
            k = 22;
        }

        else if (a[i] == 'n')
        {
            k = 21;
        }

        else if (a[i] == 'o')
        {
            k = 222;
        }

        else if (a[i] == 'p')
        {
            k = 1221;
        }

        else if (a[i] == 'q')
        {
            k = 2212;
        }

        else if (a[i] == 'r')
        {
            k = 121;
        }

        else if (a[i] == 's')
        {
            k = 111;
        }

        else if (a[i] == 't')
        {
            k = 2;
        }

        else if (a[i] == 'u')
        {
            k = 112;
        }

        else if (a[i] == 'v')
        {
            k = 1112;
        }

        else if (a[i] == 'w')
        {
            k = 122;
        }

        else if (a[i] == 'x')
        {
            k = 2112;
        }

        else if (a[i] == 'y')
        {
            k = 2122;
        }

        else if (a[i] == 'z')
        {
            k = 2211;
        }

        else if (a[i] == '1')
        {
            k = 12222;
        }

        else if (a[i] == '2')
        {
            k = 11222;
        }

        else if (a[i] == '3')
        {
            k = 11122;
        }

        else if (a[i] == '4')
        {
            k = 11112;
        }

        else if (a[i] == '5')
        {
            k = 11111;
        }

        else if (a[i] == '6')
        {
            k = 21111;
        }

        else if (a[i] == '7')
        {
            k = 22111;
        }

        else if (a[i] == '8')
        {
            k = 22211;
        }

        else if (a[i] == '9')
        {
            k = 22221;
        }

        else if (a[i] == '0')
        {
            k = 22222;
        }

        else if (a[i] == ' ')
        {
            k = 4;
        }

        else if (a[i] == '?')
        {
            k = 112211;
        }

        else if (a[i] == ',')
        {
            k = 221122;
        }

        else if (a[i] == '.')
        {
            k = 121212;
        }

        else if (a[i] == '-')
        {
            k = 211112;
        }

        else if (a[i] == ':')
        {
            k = 222111;
        }

        else if (a[i] == ';')
        {
            k = 212121;
        }

        else if (a[i] == '\'')
        {
            k = 122221;
        }

        else if (a[i] == '/')
        {
            k = 21121;
        }

        else if (a[i] == '(')
        {
            k = 21221;
        }

        else if (a[i] == ')')
        {
            k = 212212;
        }

        if (k == 4)
        {
            j = len(s);
            s[j] = ' ';
            s[j + 1] = '/';
            s[j + 2] = '\0';
        }
        else
        {
            itoa(k, &s[len(s)]);
        }

        j = len(s);
        s[j] = ' ';
        s[j + 1] = '\0';
    }

    for (i = 0; i < len(s); i++)
    {
        if (s[i] == '1')
        {
            s[i] = '.';
        }

        else if (s[i] == '2')
        {
            s[i] = '-';
        }
    }
}

//Inverte a ordem dos caracteres de uma string
void invs(char *s)
{
    char *c;
    int i, j, k;

    c = (char *)calloc(len(s), 1);

    cpy(s, c);

    j = len(c) - 1;

    for (i = 0; i < len(c); i++)
    {
        s[i] = c[j];
        j--;
    }

    free(c);
}

// Inverte a ordem dos dígitoa de um numero inteiro
int invi(int n)
{
    int i, j, k, m, n1;

    if (n == 0)
    {
        return n;
    }

    n1 = n;

    for (i = 0; n >= 1; i++)
        n /= 10;

    n = n1;

    n /= 10;
    m = n;
    n *= 10;

    n = n1 - n;

    for (j = 0; j < i - 1; j++)
        n *= 10;

    return n + invi(m);
}

// Calcula logaritmos inteiros
int logarit(int b, int n)
{
    int i;

    for (i = 0; pot(b, i) < n; i++)
        ;

    if (n == pot(b, i))
    {
        return i;
    }

    return -1;
}

// Converte numeros binarios para inteiros
int btoi(int i)
{
    int j, k = i, w;
    char *q;

    if (i == 0)
        return i;

    for (j = 0; i != 0; j++)
        i /= 10;

    q = (char *)calloc(j + 1, 1);

    if (q == NULL)
        return -1;

    itoa(k, q);

    for (i = 0, k = 0, j--; i <= j; i++)
    {
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
int itob(int b)
{
    int i, j, k;
    char *q;

    for (i = 0, j = b; j > 0; i++, j /= 2)
        ;

    q = (char *)calloc(i + 1, 1);

    if (q == NULL)
        return -1;

    for (k = 0, j = b % 2; k < i; j = b % 2, k++)
    {
        *(q + k) = j + 48;
        b /= 2;
    }

    invs(q);

    i = atoi(q);

    free(q);

    return i;
}

//Converte reais para binario sem recursividade
char *bin(double n)
{
    int i, j, k, b = n;
    char *q;

    if (!inteiro(n))
    {
        q = bin(b);
        i = atoi(q);
        free(q);

        n -= b;

        b = i;
        for (j = 0; b > 0; j++, b /= 10)
            ;

        q = (char *)calloc(j + 7, 1);

        itoa(i, q);
        q[j] = '.';

        b = j;

        for (j = 0; j < 5 && n != 0; j++)
        {
            n *= 2;
            i = n;
            n -= i;
            *(q + j + b + 1) = i + 48;
        }

        *(q + j + b + 1) = '\0';

        return q;
    }

    for (i = 0, j = b; j > 0; i++, j /= 2)
        ;

    q = (char *)calloc(i + 1, 1);

    if (q == NULL)
        return NULL;

    for (k = 0, j = b % 2; k < i; j = b % 2, k++)
    {
        *(q + k) = j + 48;
        b /= 2;
    }

    invs(q);

    return q;
}

// Confere se a string contem caracteres especiais
int hva(char *c)
{
    int i, j = 0;

    for (i = 0; i < len(c); i++)
    {
        if (c[i] != -61)
            j++;
    }

    if (j == i)
        return 0;

    return 1;
}

//Lota a RAM
void trava()
{
    char *q;

    for (q = (char *)malloc(1); q != NULL; q = (char *)malloc(1));
}

//Calcula e printa o dia e horário atuais, utilizando o fuso horário.
void temp(int fuso)
{
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

    if (fuso >= 24)
    {
        day++;
    }
    fuso %= 24;

    for (i; i > 0; i--)
    {
        day++;

        if (m < 8)
        {
            switch (m)
            {
            case 2:
                if (a % 4 == 0 && a % 100 != 0)
                {
                    if (day > 29)
                    {
                        day = 1;
                        m++;
                    }
                }
                else
                {
                    if (day > 28)
                    {
                        day = 1;
                        m++;
                    }
                }

                break;

            default:
                if (m % 2 == 0)
                {
                    if (day > 30)
                    {
                        day = 1;
                        m++;
                    }
                }
                else
                {
                    if (day > 31)
                    {
                        day = 1;
                        m++;
                    }
                }

                break;
            }
        }
        else
        {
            if (m % 2 == 0)
            {
                if (day > 31)
                {
                    day = 1;
                    m++;
                }
            }
            else
            {
                if (day > 30)
                {
                    day = 1;
                    m++;
                }
            }
        }

        if (m > 12)
        {
            m = 1;
            a++;
        }
    }

    if (day < 10)
    {
        data[0] = '0';
        itoa(day, &data[1]);
    }
    else
    {
        itoa(day, &data[0]);
    }

    data[2] = '/';

    if (m < 10)
    {
        data[3] = '0';
        itoa(m, &data[4]);
    }
    else
    {
        itoa(m, &data[3]);
    }

    data[5] = '/';

    itoa(a, &data[6]);

    switch ((time(NULL) / (60 * 60 * 24)) % 7)
    {
    case 0:
        cpy("Quinta", dia);
        break;

    case 1:
        cpy("Sexta", dia);
        break;

    case 2:
        cpy("Sabado", dia);
        break;

    case 3:
        cpy("Domingo", dia);
        break;

    case 4:
        cpy("Segunda", dia);
        break;

    case 5:
        cpy("Terca", dia);
        break;

    case 6:
        cpy("Quarta", dia);
        break;
    }

    if (h < 10)
    {
        hora[0] = '0';
        itoa(h, &hora[1]);
    }
    else
        itoa(h, hora);

    hora[2] = ':';

    if (min < 10)
    {
        hora[3] = '0';
        itoa(min, &hora[4]);
    }
    else
        itoa(min, &hora[3]);

    hora[5] = ':';

    if (seg < 10)
    {
        hora[6] = '0';
        itoa(seg, &hora[7]);
    }
    else
        itoa(seg, &hora[6]);

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
void creaty(char *mensage, char *file, char *ex)
{
    FILE *f1, *f2;
    int i, j = 6, k, t = len(ex);
    char c, s[101];

    f1 = fopen(file, "w");

    fprintf(f1, mensage);

    fclose(f1);

    f1 = fopen(file, "r");

    srand(time(NULL));

    for (j = t + 1; j < 101; j++)
    {
        k = 0;
        do
        {
            do
            {
                for (i = 0; i < j; i++)
                {
                    do
                    {
                        s[i] = rand() % 127;
                    } while (s[i] == '\0');
                }

                cpy(ex, &s[i - t]);

            } while (fthere(s));

            f2 = fopen(s, "w");

            if (f2 != NULL)
            {
                for (c = fgetc(f1); c != EOF; c = fgetc(f1))
                {
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
void enter(char *finalidade)
{
    printf("\n\nPressione \"Enter\" para %s\n", finalidade);
    getchar();

    limp();
}

// Função que printa créditoa ao fim do programa
void credits(int tempo, char *nome, char *email, char *tipo_programa)
{
    printf("Este %s foi desenvolvido por: %s\n\nGostou do %s? Compartilhe!\nTem algo para melhorar? Me conte!\n\nE-mail: %s\n\nFechando o %s, aguarde...\n", tipo_programa, nome, tipo_programa, email, tipo_programa);
    sleep(tempo);
    limp();
}

//Converte o tempo armazenado na string s para segundos e o retorna
int vtos(char *s)
{
    int i = 0;

    i += (s[7] - 48);
    i += (s[6] - 48) * 10;
    i += (s[4] - 48) * 60;
    i += (s[3] - 48) * 600;
    i += (s[1] - 48) * 3600;
    i += (s[0] - 48) * 36000;

    return i;
}

// Acha dois números inteiros que divididos resultem em n ou próximo dele
void achaInt(long int *i, long int *q, double n)
{
    long int j;

    for (j = 1; !inteiro(n); j *= 10)
    {
        n *= 10;
    }

    *i = n;
    *q = j;
}

// Calcula o módulo de n
double mod(double n)
{
    if (n < 0)
    {
        n = -n;
    }

    return n;
}

/*

    Feito por: 
    João Lucas Mayrinck

    Aluno da Universidade Federal de Viçosa

*/