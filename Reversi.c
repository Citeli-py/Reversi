#include <stdio.h>
#include <stdlib.h>

struct jogada{
    int linha,coluna;
    struct jogada *prox,*ant;
};

void printa_lista(struct jogada *lista)
{
    struct jogada *p = lista;
    struct jogada *fim = lista;
    int i=1;
    do
    {
        printf("\n%d-(%d, %d)",i, p->linha, p->coluna);
        p = p->prox;
        i++;
    }while (p != fim);
}

struct jogada *inicializa()
{
    return NULL;
}

struct jogada *Criaposicao(int linha, int coluna)
{
    struct jogada *novo = (struct jogada*)malloc(sizeof(struct jogada));
    novo->linha = linha;
    novo->coluna = coluna;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

struct jogada *insere(struct jogada *lista, int linha, int coluna)
{
    struct jogada *novo = Criaposicao(linha, coluna);

    if(lista==NULL)
    {
        novo->prox = novo;
        novo->ant = novo;
        lista = novo;
    }
    else
    {
        novo->prox = lista;
        novo->ant = lista->ant;
        lista->ant->prox = novo;
        lista->ant = novo;
    }
    return lista;
}

void libera(struct jogada *lista)
{
    struct jogada *fim = lista;
    do
    {
        free(lista);
        lista=lista->prox;
    }while (lista != fim);
}

void IniciaTabuleiro(int tab[8][8]){
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            tab[i][j]=0;
        }
    }
    tab[3][3] = tab[4][4] = 1;
    tab[3][4] = tab[4][3] = -1;
}

void DesenhaTabuleiro(int tab[8][8]){
    printf("  ");
    for (int i = 0; i < 8; i++) // Cria os numeros acima
        printf(" %d ",i);

    printf("\n +------------------------+\n");
    for (int i=0;i<8;i++){
        printf("%d|",i);
        for (int j=0;j<8;j++){
            if (tab[i][j]==0){
                printf(" - ");
            }else if (tab[i][j]==1){
                printf(" W ");
            }else printf(" B ");
        }
        printf("|\n");
    }
    printf(" +------------------------+\n");
}

struct jogada EscolheJogada(){
    struct jogada resp;
    printf("Digite a linha e a coluna:");
    scanf("%d %d",&(resp.linha),&(resp.coluna));
    return resp;
}

int TestaDirecao(int tab[8][8], int jogVez, struct jogada jog, int deltaL, int deltaC){
    int i=jog.linha+deltaL;
    int j=jog.coluna+deltaC;
    int cont=0;

    while (i>=0 && i<8 && j>=0 && j<8 && tab[i][j]==-jogVez){
        cont++;
        i += deltaL;
        j += deltaC;
    }

    if (i>=8||i<0||j>=8||j<0){
        cont = 0;
    }else if (tab[i][j]==0)
        cont = 0;

    return cont;
}

void ViraPedrasDirecao(int tab[8][8],int jogVez, struct jogada jog, int deltaL, int deltaC){
    int i=jog.linha+deltaL;
    int j=jog.coluna+deltaC;

    while (tab[i][j]==-jogVez){
        tab[i][j] = - tab[i][j];
        i += deltaL;
        j += deltaC;
    }
}

int ExecutaJogada(int tab[8][8], int jogVez, struct jogada jog){
    int resposta=0;

    if (jog.linha>=0&&jog.linha<8&&jog.coluna>=0&&jog.linha<8&&tab[jog.linha][jog.coluna]==0){

        for (int deltaL=-1;deltaL<=1;deltaL++){
            for (int deltaC=-1;deltaC<=1;deltaC++){
                if (deltaL!=0||deltaC!=0){
                    if (TestaDirecao(tab,jogVez,jog,deltaL,deltaC)){
                        ViraPedrasDirecao(tab,jogVez,jog,deltaL,deltaC);
                        resposta=1;
                    }
                }
            }
        }

        if (resposta==1){
            tab[jog.linha][jog.coluna] = jogVez;
        }
    }
    return resposta;
}

struct jogada *Jogadas(int tab[8][8], int jogVez)
{
    struct jogada *lista;
    lista = inicializa();
    struct jogada jog;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            jog.linha = i; jog.coluna = j;
            for (int deltaL=-1;deltaL<=1;deltaL++){
                for (int deltaC=-1;deltaC<=1;deltaC++){
                    if (deltaL!=0||deltaC!=0){
                        if (TestaDirecao(tab,jogVez,jog,deltaL,deltaC)){
                            lista = insere(lista, i, j);
                        }
                    }
                }
            }
        }
    return lista;
}

void CalculaVencedor(int tab[8][8]){
    int brancas=0;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (tab[i][j]==1)
                brancas++;
        }
    }

    if (brancas==32){
        printf("Empate\n");
    }else if (brancas>32){
        printf("Brancas vencem\n");
    }else printf("Pretas vencem\n");
}

int main(){

    int tabuleiro[8][8];
    int jogaVez = -1;
    int casasVazias = 60;
    struct jogada jog;

    IniciaTabuleiro(tabuleiro);


    while (casasVazias>0){
        DesenhaTabuleiro(tabuleiro);
        struct jogada *lista;
        lista = inicializa();
        lista = Jogadas(tabuleiro, jogaVez);
        printa_lista(lista);

        if (jogaVez==1){
            printf("\nJogador Brancas\n");
        }else printf("\nJogador Pretas\n");

        jog = EscolheJogada();

        if (ExecutaJogada(tabuleiro,jogaVez,jog)==0){
            printf("Jogada inválida\n");
        }else{
            jogaVez = -jogaVez;
            casasVazias--;
        }
        libera(lista);
    }

    CalculaVencedor(tabuleiro);
}