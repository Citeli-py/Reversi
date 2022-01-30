#include "ReversiLib.h"
#include <stdlib.h>
#include <stdio.h>

#define INFINITY 10000
#define MAX_NIVEL 4

double AvaliaPosicao(struct posicao jogo)
{
    //quanto melhor estiver o jogo para as peças pretas, menor deve ser o valor retornado;
    // A pontuação vai de -20 até 20, 10 pontos relacionados a quantidade;

    double pontos = 0;
    // branco -> +1; preto -> -1
    double brancas = 0,  pretas = 0;

    for(int i=0; i<8;i++)  
        for(int j=0; j<8; j++)
            if(jogo.tabuleiro[i][j] != 0)
            {
                if(jogo.tabuleiro[i][j] == 1)
                    {
                    brancas++;
                   // printf("Brancas: %.0lf\n", brancas);
                    }
                else
                   {
                        pretas++;
              //      printf("pretas: %.0lf\n", pretas);
                   }
            }
        
    
    pontos = ((brancas/(brancas+pretas)) * 40.0)-20;

    
    printf("\n|----------(%.2lf)----------|\n", pontos);
    return pontos;

}


int printa_lista2(struct elemento *lista)
{
    struct elemento *p = lista;
    int i=0;
    //printf("\n");
    do
    {
        printf("%d-(%d, %d)\n",i+1, p->jog.linha, p->jog.coluna);
        p = p->prox;
        i++;
    }while (p->jog.linha != -1);
    printf("\n");
    return i;

}



struct jogada ExecutaIA(struct posicao posAtual, int nivel, double alfa, double beta)
{
    ///declarar e inicializar as variáveis indicadas (item 1 do exercício);
    double melhorValor, valorJogada;
    int podado = 0;
    struct jogada melhorJogada; 
    struct jogada jogadaIA;
    melhorJogada.linha = -1; melhorJogada.coluna = -1;
    struct elemento *lista = inicializa();
    struct jogada *jogadaAux;

    if(nivel % 2 == 0 )
        melhorValor = -INFINITY;

    else
        melhorValor = INFINITY;

    ///calcular as possíveis jogadas de acordo com o jogador da vez (item 2 e 2a do exercício);
    struct elemento sentinela;
    //sentinela.jog.linha = -1;
    //lista = insere(lista, sentinela);
    lista = CalculaJogadasValidas(posAtual);
    
    //printa_lista2(lista);

    ///a lista sendo vazia, deve ser retornado imediatamente "melhorJogada" (item 2b do exercício);
    if(lista == NULL)
        return melhorJogada;

    jogadaAux = lista->prox;///começar a percorrer a lista, considerando a lista com sentinela (item 3 do exercício)
    struct posicao posCopia;



    while (jogadaAux!=lista && podado == 0)
    {
        ///aqui vamos percorrer a lista de jogadas possíveis (ou das brancas ou das pretas) enquanto ainda for bom continuar avaliando a posiçăo
        ///copiar o parâmetro "posAtual" para "posCopia" (item 3 do exercício)
        posCopia = posAtual;
        ///executar a jogada "jogadaAux" em "posCopia" (item 3 do exercício)
        ExecutaJogada(&posCopia, *jogadaAux);
        ///verificar se "nivel" é menor do que "MAX_NIVEL" (item 4 do exercício)
        if (nivel<MAX_NIVEL)
        {
            ///verificar se "nivel" é par (item 4a do exercício)
            if (nivel % 2 == 0)
            {
                ///chamar a função recursivamente e guardar a jogada retornada em "jogadaIA" (item 4a do exercício)
                jogadaIA.jog = ExecutaIA(posCopia, nivel+1, melhorValor, beta);

            }

            ///verificar se "nivel" é ímpar (item 4b do exercício) - pode ser usado "else" em relação ao item 4a
            else
            {
                ///chamar a função recursivamente e guardar a jogada retornada em "jogadaIA" (item 4b do exercício)
                jogadaIA.jog = ExecutaIA(posCopia, nivel+1, alfa, melhorValor);
            }

            ///executar "jogadaIA" sobre "posCopia" (item 4c do exercício)
            if(jogadaIA.jog.linha>-1)
                ExecutaJogada(&posCopia, jogadaIA);

        }

        ///avaliar a posiçao "posCopia" (item 5 do exercício)
        ///verificar se houve poda (item 5 do exercício);
        valorJogada = AvaliaPosicao(posCopia);
        if(valorJogada < alfa || valorJogada > beta)
            podado = 1;

        ///verificar "jogadaIA" é a melhor jogada encontrada até o momento (item 6 do exercício);
        if(nivel % 2 == 0 && valorJogada>= melhorValor)
        { 
            melhorValor = valorJogada;
            melhorJogada = jogadaIA.jog;
        }

        if(nivel % 2 != 0 && valorJogada <= melhorValor)
        {
            melhorValor = valorJogada;
            melhorJogada = jogadaAux->jog;
        }

        jogadaAux = jogadaAux->prox;
    }

    ///liberar a memória alocada nas listas de possíveis jogadas das peças brancas ou pretas (item 7 do exercício)
    destruirlista(lista);
    destruirlista(jogadaAux);

    ///retornar a melhor jogada encontrada "melhorJogada" (item 7 do exercício).
    return melhorJogada;

}

void SalvaJogada(struct elemento *jogada){
    struct jogada jog = jogada->jog;
    FILE *arq = fopen("jogadas.bin", "a");

    if(jogada==NULL)
        fclose(arq);
    else
        fwrite(&jog, sizeof(struct jogada), 1, arq);
    fclose(arq);
}
/*
void printa_arq()
{
    struct jogada jog;
    FILE *arq = fopen("jogadas.bin", "rb");

    while (fread(&jog, sizeof(struct jogada), 1, arq))
        printf("(%d, %d) ", jog.linha, jog.coluna);
    printf("\n");
    fclose(arq);
}
*/
int main()
{
    fopen("jogadas.bin","wb");

    int casasVazias = 60;
    struct elemento jog;
    struct posicao joga;
    joga = IniciaTabuleiro();
    struct elemento *lista;
    

    while (casasVazias>0)
    {
       // ExecutaIA(joga, 0, 0, 0);
        DesenhaTabuleiro(joga);
        lista = inicializa();
        lista = CalculaJogadasValidas(joga);

        if(lista == NULL)
        {
            printf("\nSem jogadas validas, perdeu a vez\n");
            joga.jogadorVez = -joga.jogadorVez;
        }
        else
        {
            if(joga.jogadorVez == 1)
            {
                printf("\nJogador Brancas\n");
                jog.jog = ExecutaIA(joga, 0, 0, 0);
                printf("Jogada:%d %d\n", jog.jog.linha,jog.jog.coluna);
            }
            else 
            {
                printf("\nJogador Pretas\n");
                jog = EscolheJogada(lista);
            }

            SalvaJogada(&jog);
            ExecutaJogada(&joga,jog);
            joga.jogadorVez = -joga.jogadorVez;
            casasVazias--;
        } 
    }


    system("cls");
    DesenhaTabuleiro(joga);
    CalculaVencedor(joga.tabuleiro);
    destruirlista(lista);
}
