#include <stdio.h>
#include <stdlib.h>
#include "moref.h"

void main()
{
    int i;
    char c[1000000],*s,e[2];

    do
    {
        limp();
        printf("\n++++*/ Conversor de Codigo Morse /*++++\n");

        printf("\n0 - Sair do programa");
        printf("\n1 - Decodificar do Morse");
        printf("\n2 - Codificar para Morse\n\n");

        gets(e);

        if(sori(e)==1)
        {
            continue;
        }

        limp();
        i=atoi(e);

        switch (i)
        {
            case 1:
                
                while(1)
                {
                    printf("\nDigite o codigo:\n");
                    gets(c);

                    if(mora(c)==0)
                    {
                        printf("\nIsso nao eh codigo morse\n");
                        sleep(1);
                        break;
                    }
                    
                    s = (char*)calloc(len(c),1);

                    mtoa(c,s);

                    printf("\nTexto decodificado:\n\n%s\n",s);
                    printf("\nPressione \"Enter\" para decodificar outro texto\n\n");
                    getchar();
                    limp();

                }
                free(s);

            break;

            case 2:

                while(1)
                {
                    printf("\nDigite o texto:\n");
                    gets(c);

                    if(mora(c)==1)
                    {
                        printf("\nIsso ja eh codigo morse\n");
                        sleep(1);
                        break;
                    }
                    else if (hva(c))
                    {
                        limp();
                        printf("\nRetire os acentos do texto e tente novamente\n");
                        sleep(2);
                        continue;
                    }
                    

                    s = (char*)calloc(len(c)*8,1);

                    atom(c,s);

                    printf("\nTexto codificado:\n\n%s\n",s);
                    printf("\nPressione \"Enter\" para codificar outro texto\n\n");
                    getchar();

                    limp();

                }
                free(s);
            break;
        }

    }while(e[0]!='0');

    limp();

    credits(10, "Joao Lucas Mayrinck", "jluckmay@gmail.com", "programa");

    limp();

}