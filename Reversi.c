#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int linha;
    int coluna;
} coordenada;

void jogada_random(int *ptr) //Função de debbug
{
    return 0;
}

void vira(int tabuleiro[8][8], int eixo, int linha, int coluna, int conta, int jogador)
{
    int contador = 0;
    int contadores[4] = {0, 0, 0, 0};
    switch (eixo)
    {
        case 0:
            for(int i = 0; i<8; i++)
            {
                if(contador == 1)
                    tabuleiro[linha][i] = jogador;

                if(tabuleiro[linha][i] == jogador)
                    contador ++;
            }
            break;
        
        case 1:
            for(int i = 0; i<8; i++)
            {
                if(contador == 1)
                    tabuleiro[i][coluna] = jogador;
                    
                if(tabuleiro[i][coluna] == jogador)
                    contador ++;
            }
            break;

        case 2: 
            for(int i=0; i<8; i++)
            {
                if(linha+i<8 && coluna+i<8 && conta==0) // Direita-baixo
                {
                    if(contador == 1)
                        tabuleiro[linha+i][coluna+i] = jogador;

                    if(tabuleiro[linha+i][coluna+i] == jogador)
                        contador ++;
                }

                if( linha-i>=0 && coluna-i>=0 && conta==1) // Esquerda-Cima
                {
                    if(contador == 1)
                        tabuleiro[linha-i][coluna-i] = jogador;

                    if(tabuleiro[linha-i][coluna-i] == jogador)
                        contador ++;
                }

                if( linha+i<8 && coluna-i>=0 && conta==2) // Direita-cima
                {
                    if(contador == 1)
                        tabuleiro[linha+i][coluna-i] = jogador;

                    if(tabuleiro[linha+i][coluna-i] == jogador)
                        contador ++;
                }

                if(linha-i>=0 && coluna+i<8 && conta==3) // Esquerda-baixo
                {
                    if(contador == 1)
                        tabuleiro[linha-i][coluna+i] = jogador;

                    if(tabuleiro[linha-i][coluna+i] == jogador)
                        contador ++;
                }

            }
            break;
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

    /*Se a jogada for válida, a função deve modificar o
      tabuleiro de acordo com as regras e retornar 1; caso contrário, deve manter o tabuleiro como está e
      retornar 0.*/

    /*Se a função ExecutaJogada() retornar 0, o programa deve indicar que a jogada é inválida e solicitar
      uma nova jogada. Isso deve acontecer até que o jogador da vez informe uma jogada válida.
      Considere, nessa primeira versão do trabalho, que sempre existirá pelo menos uma jogada valida.
      Se a função ExecutaJogada() retornar 1, o programa deve mudar o jogador da vez.*/

    int linha = jogada.linha;
    int coluna = jogada.coluna;
    int conta_s = 0;
    int contadores[4] = {0, 0, 0, 0};

    if((tabuleiro[linha][coluna] != 0) || (linha >= 8) || (coluna>=8)||(linha<0)||(coluna<0)) //Peça em cima da outra ou fora do tabuleiro
        return 0;

    //Pelo menos uma peça diferente tem q estar do lado da peça a ser colocada
    for(int i=linha-1;i<=linha+1; i++)
    {
        for(int j=coluna-1;j<=coluna+1; j++)
            if(i>= 0 && j>=0)
                if(tabuleiro[i][j] == -1*jogador)
                    contadores[0]++;
    }
    if(contadores[0] <= 0)
        return 0;

    contadores[0] = 0;
    tabuleiro[linha][coluna] = jogador;

    //Contadores[0] são as peças iguais a do jogador
    //contadores[1] são para as peças diferentes
    //horizontal
    if(jogador != tabuleiro[linha][coluna+1] && jogador != tabuleiro[linha][coluna-1])
    {
        for(int i = 0; i<8; i++)
        {
            if(tabuleiro[linha][i] == jogador)
                contadores[0]++;
            if(contadores[0] >= 2 && tabuleiro[linha][i-1] == -1*jogador)
            {
                vira(tabuleiro, 0, linha, coluna, 0, jogador);
                conta_s ++;
            }
        }
    }

    contadores[0] = 0;

    //vertical
    if(jogador != tabuleiro[linha+1][coluna] && jogador != tabuleiro[linha-1][coluna])
    {
        for(int i = 0; i<8;i++)
        {
            if(tabuleiro[i][coluna] == jogador)
                contadores[0]++;
            if(contadores[0] >= 2)
            {
                vira(tabuleiro, 1, linha, coluna, 0, jogador);
                conta_s ++;
            }
        }
    }
    contadores[0] = 0;

    if(jogador != tabuleiro[linha+1][coluna+1] && jogador != tabuleiro[linha+1][coluna-1] && jogador != tabuleiro[linha-1][coluna+1] && jogador != tabuleiro[linha-1][coluna-1])
    {

        /*
        (-1,-1) Esquerda-Cima
        (+1,+1) Direita-baixo
        (-1,+1) Esquerda-baixo
        (+1,-1) Direita-cima
        */
        for(int i=0; i<8; i++)
        {
            if(tabuleiro[linha+i][coluna+i] == jogador && linha+i<8 && coluna+i<8) // Direita-baixo
                contadores[0]++;

            if(tabuleiro[linha-i][coluna-i] == jogador && linha-i>=0 && coluna-i>=0) // Esquerda-Cima
                contadores[1]++;

            if(tabuleiro[linha+i][coluna-i] == jogador && linha+i<8 && coluna-i>=0) // Direita-cima
                contadores[2]++;

            if(tabuleiro[linha-i][coluna+i] == jogador && linha-i>=0 && coluna+i<8) // Esquerda-baixo
                contadores[3]++;

        }
        for(int a=0; a<4; a++)
        {
            if(contadores[a] >= 2)
            {
                vira(tabuleiro, 2, linha, coluna, a, jogador);
                conta_s ++;
            }
        }
    }

    if(conta_s>0)
        return 1;
    else
    {
        tabuleiro[linha][coluna] = 0;
        return 2;
    }
}


coordenada EscolheJogada()
{
    coordenada jogada;
    printf("Digite a linha e a coluna: ");
    scanf("%d", &jogada.linha);
    scanf("%d", &jogada.coluna);
    jogada.linha--; jogada.coluna--;
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

int tabuleiro[8][8];

int main()
{

    coordenada jogada;
    int jogador = -1;
    int jogadas = 1;
    IniciaTabuleiro(&tabuleiro);

    while (jogadas<=64)
    {
        printf("Jogada: %d \nJogador: %d\n", jogadas, jogador);
        DesenhaTabuleiro(tabuleiro);
        jogada = EscolheJogada();
        int res = ExecutaJogada(tabuleiro, jogador, jogada);

        if(res == 1)
        {
            if(jogador == 1)
                jogador = -1;
            else
                jogador = 1;
            jogadas++;
        }

        switch (res)
        {
        case 0:
            printf("\nJogada invalida!\n");
            break;

        case 1:
            printf("\nJogada valida!\n");
            break;
        
        default:
            printf("\nErro ou diagonal\n");
            break;
        }
    }
    return 0;

}
