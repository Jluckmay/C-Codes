#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Função de Limpar a tela
void limp()
{
    system("cls || clear");
}

//Função de abrir, recursivamente, as posições
void abrir(char** mat, int l, int c, int i, int j)
{
    if(i<0||i>l||j<0||j>c || mat[i][j]=='-' || (mat[i][j]-20)>'0' && (mat[i][j]-20)<'9' || mat[i][j]=='*'||((mat[i][j]-41)=='#'||(mat[i][j]-41)=='*'||((mat[i][j]-41)>'0'&&(mat[i][j]-41)<'9')))
    {
        return;
    }

    if(mat[i][j]>'0'&&mat[i][j]<'9')
    {
        mat[i][j]+=20;
        return;
    }

    if(mat[i][j]=='#')
    {
        mat[i][j]='-';
    }
    
    if(i!=0)
    {
        abrir(mat,l,c,i-1,j);
        if(j!=0)
        {
            abrir(mat,l,c,i-1,j-1);
        }
        if(j!=(c-1))
        {
            abrir(mat,l,c,i-1,j+1);
        }
    }
    if(i!=(l-1))
    {
        abrir(mat,l,c,i+1,j);
        if(j!=0)
        {
            abrir(mat,l,c,i+1,j-1);
        }
        if(j!=(c-1))
        {
            abrir(mat,l,c,i+1,j+1);
        }
    }

    if(j!=0)
    {
        abrir(mat,l,c,i,j-1);
    }
    if(j!=(c-1))
    {
        abrir(mat,l,c,i,j+1);
    }

}

//Imprime o tabuleiro, escondendo as bombas
void imp(char** mat, int l, int c)
{
    int i, j,k;

    for(i=0;i<=c;i++)
    {
        
        printf("%i",i);

        if(c>10 && i<10)
        {
            k=c;
            do
            {
                printf(" ");
                k/=10;
            } while (k>10);
        }

        if(i!=c)
        {
            printf("|");
        }
    }

    for(i=0;i<l;i++)
    {
        printf("\n%i",i+1);

        if(l>9 && i<9)
        {
            k=l;
            do
            {
                printf(" ");
                k/=10;
            } while (k>10);
            
        }

        printf("|");
        
        for(j=0;j<c;j++)
        {
            k=c;

            if((mat[i][j]>'0'&&mat[i][j]<'9') || mat[i][j]=='*')
            {
                printf("#");
            }
            else if((mat[i][j]-20)>'0' && (mat[i][j]-20)<'9')
            {
                printf("%c", mat[i][j]-20);
            }
            else if((mat[i][j]-41)=='#'||(mat[i][j]-41)=='*'||((mat[i][j]-41)>'0'&&(mat[i][j]-41)<'9'))
            {
                printf("B");
            }
            else
            {
                printf("%c", mat[i][j]);
            }

            do
            {
                printf(" ");
                k/=10;
            } while (k!=0);
            
        }
    }
}

//Imprime o tabuleiro, sem esconder coisa alguma
void impn(char** mat, int l, int c)
{
    int i,j,k;

    for(i=0;i<=c;i++)
    {
        printf("%i ",i);

        if(c>10 && i<10)
        {
            k=c;
            do
            {
                printf(" ");
                k/=10;
            } while (k>10);
        }
    }

    for(i=0;i<l;i++)
    {
        printf("\n%i",i+1);
        if(c>10 && i<10)
        {
            k=c;
            do
            {
                printf(" ");
                k/=10;
            } while (k>10);
        }

        for(j=0;j<c;j++)
        {
            
            printf("%c", mat[i][j]);
            
            k=c;
            do
            {
                printf(" ");
                k/=10;
            } while (k!=0);
        }
    }
}

//Imprime o tabuleiro destacando a bomba que explodiu
void impp(char** mat, int l, int c)
{
    int i,j,k;

    for(i=0;i<=c;i++)
    {
        printf("%i ",i);

        if(c>10 && i<10)
        {
            k=c;
            do
            {
                printf(" ");
                k/=10;
            } while (k>10);
        }
    }

    for(i=0;i<l;i++)
    {
        printf("\n%i ",i+1);
        if(l>9 && i<9)
        {
            k=l;
            do
            {
                printf(" ");
                k/=10;
            } while (k>10);
            
        }
        for(j=0;j<c;j++)
        {
            k=c;
            if((mat[i][j]>'0' && mat[i][j]<'9') || mat[i][j]=='*')
            {
                printf("%c", mat[i][j]);
            }
            else if((mat[i][j]-20)>'0' && (mat[i][j]-20)<'9')
            {
                printf("%c", mat[i][j]-20);
            }
            else if(mat[i][j]=='-' || mat[i][j]=='#')
            {
                printf("-");
            }
            else if((mat[i][j]-41)=='*')
            {
                printf("B");
            }
            else
            {
                printf("X");
            }

            do
            {
                printf(" ");
                k/=10;
            } while (k!=0);
            
        }
    }

}

//Cria, dinamicamente, uma matriz de i linhas e j colunas
char** alloc(int i, int j)
{
    int k,l;
    char** c;

    c=(char**)calloc(i,sizeof(char*));

    if(c==NULL)
    {
        printf("Erro!");
        sleep(5);
        return c;
    }

    for(k=0;k<i;k++)
    {
        c[k]=(char*)calloc(j,sizeof(char));

        if(c[k]==NULL)
        {
            k--;
            while (k<0)
            {
                free(c[k]);
                k--;
            }

            free(c);
            
            printf("Erro!");
            sleep(5);
            break;
        }
        
        for(l=0;l<j;l++)
        {
            c[k][l]='#';
        }
    }

    return c;
}

//Função que adiciona 1 ao valor da posição caso não tenhá bomba na mesma
void num(char* c)
{
    if((*c)=='#')
    {
        (*c)='1';
    }
    else if((*c)!='*')
    {
        (*c)++;
    }
    
}

//Função de pôr/tirar a bandeira da posição
void ban(char*c)
{
    if((((*c)-20)>'0' && ((*c)-20)<'9') || (*c)=='-')
    {
        return;
    }

    if(((*c)-41)=='#'||((*c)-41)=='*'||(((*c)-41)>'0'&&((*c)-41)<'9'))
    {
        (*c)-=41;
    }
    else
    {
        (*c)+=41;
    }
    
}

//Função que distribui aleatóriamente b bombas em uma matriz mat de i linhas e j colunas
int bomb(char** mat, int i, int j, int b)
{
    int l,c;

    if(b<=i*j)
    {
        for(b;b>0;b--)
        {
            l=rand()%i;
            c=rand()%j;

            if(mat[l][c]=='*')
            {
                b++;
            }
            else
            {
                mat[l][c]='*';
                
                if(l!=0)
                {
                    num(&mat[l-1][c]);
                    
                    if(c!=0)
                    num(&mat[l-1][c-1]);

                    if(c!=(j-1))
                    num(&mat[l-1][c+1]);
                }

                if(l!=(i-1))
                {
                    num(&mat[l+1][c]);

                    if(c!=0)
                    num(&mat[l+1][c-1]);

                    if(c!=(j-1))
                    num(&mat[l+1][c+1]);
                }
                
                if(c!=0)
                num(&mat[l][c-1]);

                if(c!=(j-1))
                num(&mat[l][c+1]);
            
            }   
        }
    }
    else
    {
        printf("Erro, número de bombas inválido");
        sleep(5);
        return -1;
    }
    
    return 1;
    
}

//Função que libera todas as posições, alocadas dinamicamente, em uma matriz mat de i linhas e j colunas
void freeall(char** mat, int i, int j)
{

    for(j=0;j<i;j++)
    {
        free(mat[j]);
    }

    free(mat);
}

//Função que exibe o menu do jogo e retorna a opção selecionada pelo usuário
int menu()
{
    int op;

    setlocale(LC_ALL, "Portuguese");

    limp();

    printf("\t**-# Campo Minado #-**\n\n");
    printf("\nDigite:\n\n");
    printf("0 - Para ler as regras do jogo\n");
    printf("1 - Para jogar no tabuleiro padrão\n");
    printf("2 - Para jogar em um tabuleiro personalisado\n");
    printf("3 - Para ver os records salvos\n");
    printf("4 - Para sair\n\n");
    scanf("%i",&op);
    getchar();

    limp();

    return op;
}

//Exibe uma mensagem de "Aperte enter para retornar ao menu"
void enter()
{
    printf("Pressione \"Enter\" para retornar ao menu\n");
    getchar();
}

//Conta e retorna a quantidade de bombas presentes em uma matriz de l linhas e c colunas
int cont(char** mat, int l, int c)
{
    int i, j,b=0;

    for(i=0;i<l;i++)
    {
        for(j=0;j<c;j++)
        {
            if(!(mat[i][j]=='*' || (mat[i][j]-41)=='*' || mat[i][j]=='#' || (mat[i][j]>'0'&&mat[i][j]<'9')))
            {
                b++;
            }
        }
    }

    return b;
}

// Função que mede comprimento da string s
int cmp(char s[]) 
{
    int i;
    for(i=0; s[i]!='\0'; i++);
    return i;
}

// Função que copia x em y
void cpy(char x[], char *y)  
{
    int i,j=cmp(x);

    for(i=0;i<j;i++)
    y[i]=x[i];

    y[j]='\0';
}

//Função q converte um inteiro s em segundos para uma string min em minutos
char* conv(int s, char* min)
{
    cpy("00:00:00",min);

    while (s>59)
    {
        s-=60;
        min[4]++;
        if(min[4]>'9')
        {
            min[4]='0';
            min[3]++;
            if(min[3]=='6')
            {
                min[3]='0';
                min[1]++;
                if(min[1]>'9')
                {
                    min[1]='0';
                    min[0]++;
                    if(min[0]>'9')
                    {
                        min[0]='0';
                    }
                }
            }
        }
    }

    min[6]=(s/10)+48;
    min[7]=(s-((s/10)*10))+48;
    
    return min;
}

//Converte o tempo armazenado na string s para segundos e o retorna
int vnoc(char *s)
{
    int i=0;

    i+=(s[7]-48);
    i+=(s[6]-48)*10;
    i+=(s[4]-48)*60;
    i+=(s[3]-48)*600;
    i+=(s[1]-48)*3600;
    i+=(s[0]-48)*36000;

    return i;
}

//Exibe o Record
void impr(FILE* f)
{
    int l=0, i, t, j=0, k, m, st[9],q=0;
    char c,s[45];

    rewind(f);

    do
    {
        c=fgetc(f);
        if(c=='\n')
        {
            q++;
        }
    } while (c!=EOF);

    if(q>5)
    {
        q=5;
    }

    rewind(f);

    for (i = 0; i < q; i++)
    {
        k=0;
        m=10000000;

        do
        {
            c=fgetc(f);
            if(c==' ')
            {
                fgets(st,9,f);

                t=vnoc(st);

                if(t<m && t>j)
                {
                    m=t;
                }
            }

        }while(c!=EOF);

        if(m!=10000000)
        {
            j=m;
        }

        rewind(f);

        do
        {
            c=fgetc(f);
            if(c==' ')
            {
                fgets(st,9,f);
                k++;

                t=vnoc(st);

                if(t==m)
                {
                    break;
                }
            }

        }while(c!=EOF);

        rewind(f);

        for(k-=1;k>0;k--)
        {
            do
            {
                c=fgetc(f);
            } while (c!='\n');
        }

        fgets(s,45,f);
        puts(s);   

        rewind(f);
        
    }
    
    
}

void main()
{
    FILE* f;
    char **mat=NULL,s[21],st[9]="00:00:00";
    int i=0,j=0,b,k,l,r, t;

    srand(time(NULL));

    do
    {
        switch(menu())
        {
            case 0:
                
                printf("\t--#* Regras *#--\n\n\n");
                printf(" # Tabuleiros:\n\n\n");
                printf("O tabuleiro padrão eh 9x9, ou seja, possui nove linhas e nove colunas. Ele possui 10(dez) bombas espalhadas.\n\n");
                printf("O tabuleiro personalisado terá o tamanho a ser decidido pelo usuário, tanto em linhas como em colunas e em número de bombas.\n\n\n");
                printf(" # O jogo:\n\n\n");
                printf("O tabuleiro do jogo possui bombas escondidas em suas posições, quando fechadas estas serão representadas pelo carácter \"#\".\nO objetivo do jogo e abrir todas as posições que não possuem bombas, para auxiliar neste processo o jogador pode marcar uma \nposição com uma bandeira (representada pelo carácter \"B\") para simbolizar o local onde ele supõe que há uma bomba, da mesma \nforma pode remover a bandeira.\nPara localizar as bombas, e necessário que o jogador preste atenção aos números no tabuleiro, pois o número que estiver em \numa determida posição representa a quantidade de bombas presentes nas posições adjacentes(vizinhas).\nPara marcar ou desmarcar uma posição como bandeira, digite \"0\" durante o jogo.\n\n");
                enter();
                r=1;

            break;
            
            case 1:

                k=9;
                l=9;
                b=10;                    
                r=0;
                
                mat=alloc(l,k);

                if(mat!=NULL)
                {
                   
                    bomb(mat,l,k,b);
                    t=time(NULL);
                    do
                    {
                        limp();
                        
                        /*
                        impn(mat,l,k);
                        printf("\n\n");
                        */
                        imp(mat,l,k);
                        printf("\n\nBandeiras: %i/%i\n\n",r,b);

                        do
                        {
                            printf("Em qual linha deseja jogar?\n");
                            scanf("%i",&i);
                            getchar();
                            if(i>0&&i<=l)
                            {
                                printf("Em qual coluna deseja jogar?\n");
                                scanf("%i",&j);
                                getchar();
                            }
                            limp();

                        }while(i<0||i>l||j<0||j>k);

                        i--;
                        j--;

                        if(i==-1 || j==-1 && r<b)
                        {
                            do
                            {
                                /*
                                impn(mat,l,k);
                                printf("\n\n");
                                */
                                imp(mat,l,k);
                                printf("\n\nBandeiras: %i/%i\n\n",r,b);

                                printf("Em qual linha deseja por/retirar a bandeira?\n");
                                scanf("%i",&i);
                                getchar();
                                if(i>0&&i<=l)
                                {
                                    printf("Em qual coluna deseja por/retirar a bandeira?\n");
                                    scanf("%i",&j);
                                    getchar();
                                }
                                limp();

                            }while(i<=0||i>l||j<=0||j>k);
                            
                            i--;
                            j--;

                            ban(&mat[i][j]);
                            if((mat[i][j]-41)=='#' || ((mat[i][j]-41)>'0' && (mat[i][j]-41)<'9') || (mat[i][j]-41)=='*')
                            {
                                r++;
                            }
                            else if(!(((mat[i][j]-20)>'0' && (mat[i][j]-20)<'9') || mat[i][j]=='-'))
                            {
                                r--;
                            }
                            
                        }
                        else if(mat[i][j]!='*')
                        {
                            abrir(mat,l,k,i,j);
                        }
                        else if(mat[i][j]=='*')
                        {
                            conv(time(NULL)-t,st);
                            impp(mat,l,k);
                            printf("\n%i/%i",r,b);
                            printf("\n\nVocê perdeu!\nTempo: %s\n", st);
                            enter();
                            break;
                        }

                    }while(cont(mat,l,k)!=((l*k)-b));

                    if(cont(mat,l,k)==((l*k)-b))
                    {
                        conv(time(NULL)-t,st);

                        limp();

                        f=fopen("records.txt","r");

                        if(f==NULL)
                        {
                            f=fopen("records.txt","w");
                        }
                        else
                        {
                            fclose(f);

                            f=fopen("records.txt","a");
                        }

                        if(f!=NULL)
                        {
                            printf("Parabéns, você venceu!!!\nTempo: %s\nDigite seu nome: ",st);
                            scanf("%s", s);
                            getchar();
                            printf("\n");
                            fprintf(f,"%s %s\n",s,st);
                            fclose(f);
                        }
                        else
                        {
                            printf("Erro, não há memória para salvar o record!\n");
                        }

                        enter();

                    }
                    freeall(mat,k,l);   
                }
                else
                {
                    printf("Erro!\n");
                    enter();
                }
                r=1;
                
            break;

            case 2:

                do
                {
                    limp();
                    printf("Digite o número de linhas do tabuleiro\n");
                    scanf("%i",&l);
                } while (l<=0);

                do
                {
                    limp();
                    printf("Digite o número de colunas do tabuleiro\n");
                    scanf("%i",&k);
                } while (k<=0);

                do
                {
                    limp();
                    printf("Digite o número de bombas do tabuleiro\n");
                    scanf("%i",&b);
                } while (b<=0 || k*l<b);

                r=0;
                
                mat=alloc(l,k);

                if(mat!=NULL)
                {
                   
                    bomb(mat,l,k,b);
                    t=time(NULL);
                    do
                    {
                        limp();   

                        do
                        {

                            /*
                            impn(mat,l,k);
                            printf("\n\n");
                            */
                            imp(mat,l,k);
                            printf("\n\nBandeiras: %i/%i\n\n",r,b);

                            printf("Em qual linha deseja jogar?\n");
                            scanf("%i",&i);
                            getchar();
                            if(i>0&&i<=l)
                            {
                                printf("Em qual coluna deseja jogar?\n");
                                scanf("%i",&j);
                                getchar();
                            }
                            limp();
                        }while(i<0||i>l||j<0||j>k);

                        i--;
                        j--;

                        if(i==-1 || j==-1 && r<b)
                        {
                            do
                            {
                                /*
                                impn(mat,l,k);
                                printf("\n\n");
                                */
                                imp(mat,l,k);
                                printf("\n\nBandeiras: %i/%i\n\n",r,b);

                                printf("Em qual linha deseja por/retirar a bandeira?\n");
                                scanf("%i",&i);
                                getchar();
                                if(i>0&&i<=l)
                                {
                                    printf("Em qual coluna deseja por/retirar a bandeira?\n");
                                    scanf("%i",&j);
                                    getchar();
                                }
                                limp();

                            }while(i<=0||i>l||j<=0||j>k);
                            
                            i--;
                            j--;

                            ban(&mat[i][j]);
                            if((mat[i][j]-41)=='#' || ((mat[i][j]-41)>'0' && (mat[i][j]-41)<'9') || (mat[i][j]-41)=='*')
                            {
                                r++;
                            }
                            else if(!(((mat[i][j]-20)>'0' && (mat[i][j]-20)<'9') || mat[i][j]=='-'))
                            {
                                r--;
                            }
                            
                        }
                        else if(mat[i][j]!='*')
                        {
                            abrir(mat,l,k,i,j);
                        }
                        else if(mat[i][j]=='*')
                        {
                            conv(time(NULL)-t,st);
                            impp(mat,l,k);
                            printf("\n%i/%i",r,b);
                            printf("\n\nVocê perdeu!\nTempo: %s\n", st);
                            enter();
                            break;
                        }

                    }while(cont(mat,l,k)!=((l*k)-b));

                    if(cont(mat,l,k)==((l*k)-b) && mat[i][j]!='*')
                    {
                        conv(time(NULL)-t,st);

                        limp();

                        f=fopen("recordsp.txt","r");

                        if(f==NULL)
                        {
                            f=fopen("recordsp.txt","w");
                        }
                        else
                        {
                            fclose(f);

                            f=fopen("recordsp.txt","a");
                        }

                        if(f!=NULL)
                        {
                            printf("Parabéns, você venceu!!!\nTempo: %s\nDigite seu nome: ",st);
                            scanf("%s", s);
                            getchar();
                            printf("\n");
                            fprintf(f,"%s %s\n",s,st);
                            fclose(f);
                        }
                        else
                        {
                            printf("Erro, não há memória para salvar o record!\n");
                        }

                        enter();

                    }
                    freeall(mat,l,k);   
                }
                else
                {
                    printf("Erro!\n");
                    enter();
                }
                r=1;
            break;

            case 3:

                limp();

                f=fopen("records.txt","r");

                if(f==NULL)
                {
                    f=fopen("recordsp.txt","r");
                    if(f==NULL)
                    {
                        printf("Para utilizar este recurso, vença o jogo!\n\n");
                        enter();
                    }
                    else
                    {
                        printf("  --*# Records Personalizados #*--\n\n");
                        impr(f);
                        printf("\n");
                        enter();
                        fclose(f);
                    }
                }
                else
                {
                    printf("  --*# Records Padrões #*--\n\n");
                    impr(f);
                    printf("\n");
                    fclose(f);

                    f=fopen("recordsp.txt","r");
                    if(f!=NULL)
                    {
                        printf("\n  --*# Records Personalizados #*--\n\n");
                        impr(f);
                        printf("\n");
                        fclose(f);
                    }

                    enter();
                    
                }
                
            break;

            case 4:
                r=(-2);
            break;
        }
        
    } while (r>0);

    printf("Este jogo foi desenvolvido por: João Lucas Mayrinck\n\nGostou do jogo? Compartilhe!\nTem algo para melhorar? Me conte.\n\nE-mail: jluckmay@gmail.com\n\nFechando o jogo aguarde...\n");
    sleep(7);    
    limp();
    
}