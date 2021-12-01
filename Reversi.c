#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int linha, coluna;
} coordenada;


int ValidaJogada(int tabuleiro[8][8], int jogador, coordenada jogada)
{
    int linha = jogada.linha;
    int coluna = jogada.coluna;

    if((tabuleiro[linha][coluna] != 0) || (linha >= 8) || (coluna>=8)||(linha<0)||(coluna=0))
        return -1;


    for(int i = 0; i<8; i++)
        {
            for(int j = 0; j<8; j++)
                {
                 
                 return 0;
                  




                }
        
        }



}



void ExecutaJogada(int tabuleiro[8][8], int jogador, coordenada jogada)
{
    /*Se a jogada for válida, a função deve modificar o
      tabuleiro de acordo com as regras e retornar 1; caso contrário, deve manter o tabuleiro como está e
      retornar 0.*/

    /*Se a função ExecutaJogada() retornar 0, o programa deve indicar que a jogada é inválida e solicitar
      uma nova jogada. Isso deve acontecer até que o jogador da vez informe uma jogada válida.
      Considere, nessa primeira versão do trabalho, que sempre existirá pelo menos uma jogada valida.
      Se a função ExecutaJogada() retornar 1, o programa deve mudar o jogador da vez.*/

    return 0;
}

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

coordenada EscolheJogada()
{
    coordenada jogada;
    scanf("%d %d", &jogada.linha, &jogada.coluna);
    jogada.linha--; jogada.coluna--;
    return jogada;
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
    printf("%d",ValidaJogada(tabuleiro, 1, jogada));
    
    return 0;

}
