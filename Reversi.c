#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int linha;
    int coluna;
} coordenada;

void printa(int *ptr) //Função de debbug
{
    //notas *(ptr + linha*n_linhas + coluna) == matriz[linha][coluna];
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            printf("%d ", *(ptr + i*8 + j));

        printf("\n");
    }
}


void DesenhaTabuleiro(int tabuleiro[8][8])
{
    printf("  ");
    for (int i = 0; i < 8; i++) // Cria os numeros acima
    {
        printf(" %d ",i+1);
    }
    
    printf("\n +------------------------+");
    for(int i=0; i<8; i++)
    { 
        printf("\n%d|",i+1);
        for(int j=0;j<8;j++) // Define as peças do tabuleiro
        {
            if(tabuleiro[i][j] == -1)
                printf(" B ");
            if(tabuleiro[i][j] == 1)
                printf(" W ");
            if(tabuleiro[i][j] == 0)
                printf(" - ");
        }
        printf("|");
    }
    printf("\n +------------------------+");
    printf("\n");
    return 0;
}

int ExecutaJogada(int tabuleiro[8][8], int jogador, coordenada jogada)
{
    int linha = jogada.linha;
    int coluna = jogada.coluna;
    int contador = 1;
    int contadores[4] = {0, 0, 0, 0};

    if((tabuleiro[linha][coluna] != 0) || (linha >= 8) || (coluna>=8)||(linha<0)||(coluna=0))
        return -1;

    tabuleiro[linha][coluna] = jogador;
    printf("\n--%d--\n", tabuleiro[7][7]);
    printa(&tabuleiro[0][0]);

    //horizontal
    for(int i = 0; i<8; i++)
    {
        if(tabuleiro[linha][i] == jogador)
            contador++;
        if(contador >= 2)
            return 1;

        printf("%d\n", contador);
    }


    //vertical
    for(int i = 0; i<8;i++)
    {
        if(tabuleiro[i][coluna] == jogador)
            contador++;
        if(contador >= 2)
            return 1;
  
    }

    //diagonal
   /* for(int i = 0, a = 7; i<8, a>-1; i++, a--)
    {
        //Direita-Baixo
        if(tabuleiro[i+l][i+l] == tabuleiro[i+1+l][i+1+l])
            contadores[0]++;
        if(tabuleiro[a][a] == tabuleiro[i-1][i-1])
            contadores[1]++;



  
  
    }
*/

    return 2;
}



//void ExecutaJogada(int tabuleiro[8][8], int jogador, coordenada jogada)
//{
    /*Se a jogada for válida, a função deve modificar o
      tabuleiro de acordo com as regras e retornar 1; caso contrário, deve manter o tabuleiro como está e
      retornar 0.*/

    /*Se a função ExecutaJogada() retornar 0, o programa deve indicar que a jogada é inválida e solicitar
      uma nova jogada. Isso deve acontecer até que o jogador da vez informe uma jogada válida.
      Considere, nessa primeira versão do trabalho, que sempre existirá pelo menos uma jogada valida.
      Se a função ExecutaJogada() retornar 1, o programa deve mudar o jogador da vez.*/

  //  return 0;
//}

coordenada EscolheJogada()
{
    coordenada jogada;
    scanf("%d", &jogada.linha);
    scanf("%d", &jogada.coluna);
    jogada.linha-=1; jogada.coluna-=1;
    return jogada;
}



void IniciaTabuleiro(int *ptr)
{
    //Zera o tabuleiro
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            *(ptr + i*8 + j) = 0;


    //Peças do centro
    *(ptr + 3*8 + 3) = 1;
    *(ptr + 4*8 + 3) = -1;
    *(ptr + 3*8 + 4) = -1;
    *(ptr + 4*8 + 4) = 1;

    //notas *(ptr + linha*n_linhas + coluna) == matriz[linha][coluna];
}

int main()
{

    coordenada jogada;
    int tabuleiro[8][8];
    //tabuleiro
    //matriz_teste(&tabuleiro[0][0]);
    IniciaTabuleiro(&tabuleiro);
    DesenhaTabuleiro(tabuleiro);
    jogada = EscolheJogada();
    //printf("Linha: %d\nColuna: %d", jogada.linha, jogada.coluna);
    printf("%d",ExecutaJogada(tabuleiro, 1, jogada));
    DesenhaTabuleiro(tabuleiro);
    return 0;

}
