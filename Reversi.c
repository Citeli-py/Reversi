#include "ReversiLib.h"
#include <stdlib.h>
#include <stdio.h>

double AvaliaPosicao(struct posicao jogo)
{
    //quanto melhor estiver o jogo para as peças pretas, menor deve ser o valor retornado.
    // A pontuação vai de -20 até 20, 10 pontos relacionados a quantidade
    double pontos = 0;

    int pecas=0; //0 -> equilibrada; pecas>0 -> brancas; pecas>0 -> pretas
    // branco -> +1; preto -> -1
    for(int i=0; i<8;i++)
        for(int j=0; j<8; j++)
            if(jogo.tabuleiro[i][j] != 0)
            {
                if(jogo.tabuleiro[i][j] == 1)
                    pecas++;
                else
                    pecas--;
            }
    printf("\n|---(%d)---|\n", pecas);
}

//struct elemento ExecutaIA(/*passar os parâmetros*/){
    ///declarar e inicializar as variáveis indicadas (item 1 do exercício)

    ///calcular as possíveis jogadas de acordo com o jogador da vez (item 2 e 2a do exercício)

    ///a lista sendo vazia, deve ser retornado imediatamente "melhorJogada" (item 2b do exercício)

    //jogadaAux = lista->prox;///começar a percorrer a lista, considerando a lista com sentinela (item 3 do exercício)

    //while (jogadaAux!=lista && podado==0){///aqui vamos percorrer a lista de jogadas possíveis (ou das brancas ou das pretas) enquanto ainda for bom continuar avaliando a posiçăo

        ///copiar o parâmetro "posAtual" para "posCopia" (item 3 do exercício)

        ///executar a jogada "jogadaAux" em "posCopia" (item 3 do exercício)

        ///verificar se "nivel" é menor do que "MAX_NIVEL" (item 4 do exercício)
        //if ()
        //{
            ///verificar se "nivel" é par (item 4a do exercício)
            //if (){
                ///chamar a função recursivamente e guardar a jogada retornada em "jogadaIA" (item 4a do exercício)
            //}

            ///verificar se "nivel" é ímpar (item 4b do exercício) - pode ser usado "else" em relação ao item 4a
            //else{
                ///chamar a função recursivamente e guardar a jogada retornada em "jogadaIA" (item 4b do exercício)
            //}

            ///executar "jogadaIA" sobre "posCopia" (item 4c do exercício)

        //}

        ///avaliar a posiçao "posCopia" (item 5 do exercício)

        ///verificar se houve poda (item 5 do exercício)

        ///verificar "jogadaIA" é a melhor jogada encontrada até o momento (item 6 do exercício)

        //jogadaAux = jogadaAux->prox;
    //}

    ///liberar a memória alocada nas listas de possíveis jogadas das peças brancas ou pretas (item 7 do exercício)

    ///retornar a melhor jogada encontrada "melhorJogada" (item 7 do exercício).
//}

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
int main(){
    fopen("jogadas.bin","wb");

    int casasVazias = 60;
    struct elemento jog;
    struct posicao joga;
    joga = IniciaTabuleiro();
    struct elemento *lista;
    

    while (casasVazias>0)
    {
        AvaliaPosicao(joga);
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
            if (joga.jogadorVez == 1){
            printf("\nJogador Brancas\n");
            }else printf("\nJogador Pretas\n");

            jog = EscolheJogada(lista);
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
