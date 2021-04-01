/*

UFV - Universidade Federal de Viçosa

Trabalho de Programação

Alunos: João Lucas Mayrinck D'Oliveira.
Matriculas: 6320.

*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void timer(int i)
{
    int j;

    j=time(NULL);

    while(time(NULL)-j<i)
    {

    }
}

void uplw(char *s, float k)
{
    int i,j;

    if(k<=0)
    {
        for(i=0;s[i]!='\0';i++)
        {
            if(s[i]>64&&s[i]<91)
            {
                s[i]+=32;
            }
        }
    }

    else
    {
        for(i=0;s[i]!='\0';i++)
        {
            if(s[i]>96&&s[i]<123)
            {
                s[i]-=32;
            }
        }
    }
    
}

int sori(char s[])
{
    int i,j=0,k;

    for(k=0;s[k]!='\0';k++);

    for(i=0;s[i]!='\0';i++)
    {
        if(s[i]=='1'||s[i]=='2'||s[i]=='3'||s[i]=='4'||s[i]=='5'||s[i]=='6'||s[i]=='7'||s[i]=='8'||s[i]=='9')
        {
            j++;
        }
    }

    if(j==k)
    {
        return 0;
    }
    
    else
    {
        return 1;
    }
}

void main()
{
    int i=0, j, k, q=21,u,pc;
    char s[5];

    setlocale(LC_ALL, "Portuguese");

    system("cls || clear");

    printf("UFV - Universidade Federal de Viçosa\n\nTrabalho da Semana Academica\n\nAluno: João Lucas Mayrinck\nMatricula: 6320.\n\nPressione Enter para rodar o programa.\n");
    getchar();

    do
    {
        do
        {

            system("cls || clear");

            printf("\n ////// Jogo dos 21 palitos - Menu ////// \n");

            printf("\nEscolha uma das opções abaixo digitando o número correspondente a mesma.\n");
            printf("\n 1 - Player vs Máquina.");
            printf("\n 2 - Player 1 vs Player 2.");
            printf("\n 3 - Visualizar as regras do jogo");
            printf("\n 4 - Sair do programa.\n");
            printf("\n ////// Jogo dos 21 palitos - Menu ////// \n\n");
            gets(s);

            if(sori(s)==1)
            {    
                continue;
            }

        }while(atoi(s)<0 || atoi(s)>4);

        system("cls || clear");

        if(atoi(s)==1)
        {
            do
            {
                system("cls || clear");
                printf("\n %iº Rodada\n",i+1);
                printf("Quantidade de palitos: %i\n\n",q);

                for(j=0;j<q;j++)
                {
                    printf("| ");
                }

                do
                {    
                    printf("\n\nQuantos palitos deseja retirar?\n");
                    gets(s);
                }while(sori(s)==1);

                while(atof(s)>4 || atof(s)==0 || atof(s)>q)
                {
                    printf("\n\nDigite uma quantidade válida.\n");
                    gets(s);
                }
                
                u=atof(s);
                k=q-u;
                
                
                if(k>16 && k<21)
                {
                    pc=k-16;
                }
                else if(k>11 && k<16)
                {
                    pc=k-11;
                }
                else if(k<11 && k>6)
                {
                    pc=k-6;
                }
                else if(k<6)
                {
                    pc=k-1;
                }

                printf("\nVocê retirou %i palitos.",u);
                
                if(pc==0)
                {
                    system("cls || clear");
                    printf("\nVocê ganhou.\n");
                    printf("\nAguarde.\n");
                    timer(2);
                    break;
                }

                else if(q-u!=0)
                printf("\nO computador retirou %i palitos.\n", pc);

                else
                {
                    pc=0;

                    system("cls || clear");

                    printf("\nVocê perdeu.\n");
                }

                printf("\nAguarde.\n");
                timer(2);

                i++;
                q-=(u+pc);
            } while (q>0);
        }

        else if(atoi(s)==2)
        {
            i=0;

            do
            {
                system("cls || clear");
                if(i!=0)
                {
                
                printf("\nNa rodada anterior...\n");
                printf("\nO Player 1 retirou %i palitos.",u);
                printf("\nO Player 2 retirou %i palitos.\n", pc);
                }
                printf("\n %iº Rodada\n",i+1);
                printf("Quantidade de palitos: %i\n\n",q);

                for(j=0;j<q;j++)
                {
                    printf("| ");
                }

                do
                {    
                    printf("\n\nPlayer 1, quantos palitos deseja retirar?\n");
                    gets(s);
                }while(sori(s)==1);

                while(atof(s)>4 || atof(s)==0 || atof(s)>q)
                {
                    printf("\n\nDigite uma quantidade válida.\n");
                    gets(s);
                }
                
                u=atoi(s);

                q-=u;
                
                if(q==0)
                {
                    system("cls || clear");

                    printf("\nVencedor: Player 2\n");
                    printf("\nAguarde.\n");
                    timer(2);
                    break;
                }
                
                do
                {
                    system("cls || clear");
                    printf("\n %iº Rodada\n",i+1);
                    printf("Quantidade de palitos: %i\n\n",q);
                    
                    for(j=0;j<q;j++)
                    {
                        printf("| ");
                    }

                    printf("\n\nPlayer 2, quantos palitos deseja retirar?\n");
                    gets(s);
                }while(sori(s)==1);

                while(atof(s)>4 || atof(s)==0 || atof(s)>q)
                {
                    printf("\n\nDigite uma quantidade válida.\n");
                    gets(s);
                }
                
                pc=atof(s);
                q-=pc;

                if(q==0)
                {
                    system("cls || clear");

                    printf("\nVencedor: Player 1\n");
                    printf("\nAguarde.\n");
                    timer(2);
                    break;
                }

                i++;
            } while (q>0);

        }

        else if(atoi(s)==3)
        {
            printf("\n                      ////// Jogo dos 21 palitos ////// \n");
            printf("\n  Como funciona o jogo?\n\n   O jogo começa com uma fileira de 21 palitos, cada jogador deve retirar de\n   1 a 4 palitos por rodada, perde o jogador que retirar o último palito da\n   fileira.\n");
            printf("\n  Objetivo do jogo:\n\n   Fazer com que o adversário retire o último palito da fileira.\n\n                                 Aguarde...\n\n");
            timer(20);
            system("cls || clear");
            printf("\n                           ////// Regras ////// \n");
            printf("\n   1 - Não e permitido aos jogadores deixar de jogar durante uma rodada\n       ou passar a vez para o outro jogador");
            printf("\n\n   2 - Os jogadores podem retirar apenas de 1 a 4 palitos, não podendo\n       tirar 0 palitos ou deixar de retirar os mesmos.");
            printf("\n\n OBS: No modo de jogo \"Player vs Máquina\", a máquina sempre vence.\n\n");
            printf("Pressione \"Enter\" para retornar ao menu.\n");

            getchar();
            
            s[0]='s';

            continue;
        }
        
        else
        {
            break;
        }

        i=0;
        q=21;
        
        system("cls || clear");

        do
        {
            printf("\nDeseja jogar novamente?\n\nSe sim, digite \"sim\". Se não, digite \"não\".\n\n");
            gets(s);
            uplw(s,0);
        }while(s[0]!='n' && s[0]!='s');

        system("cls || clear");

    } while (s[0]=='s');

    printf("\nSe gostou do jogo, avalie-nos e compartilhe com os amigos.\nAcha que podemos melhorar? Nos diga como.\n\n  Entre em contato:\n\n  E-mail:jluckmay@gmail.com\n  Telefone:(24) 981413283\n\n");
    printf("\nFechando o jogo... Aguarde...\n\n");
    timer(20);
    system("cls || clear");
}