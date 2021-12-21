#include <stdio.h>
#include <stdlib.h>

struct jogada{
    int linha,coluna;
    struct jogada *prox,*ant;
};

int printa_lista(struct jogada *lista)
{
    struct jogada *p = lista;
    struct jogada *fim = lista;
    int i=0;
    //printf("\n");
    do
    {
        printf("%d-(%d, %d)\n",i+1, p->linha, p->coluna);
        p = p->prox;
        i++;
    }while (p != fim);
    printf("\n");
    return i;
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

struct jogada *insere(struct jogada *lista, struct jogada jog)
{
    struct jogada *novo = Criaposicao(jog.linha, jog.coluna);

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
   struct jogada* tmp;

    for(int i=0; i<50; i++)
    {
        tmp = lista;
        lista = lista->prox;
        free(tmp);
    }

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

struct jogada EscolheJogada(struct jogada *lista){
    struct jogada resp;
    struct jogada *p=lista;
    int n, num_lista=printa_lista(lista);
    do
    {
        printf("Escolha a sua jogada: ");
        scanf("%d",&n);
        if(n<1||n>num_lista)
            printf("jogada invalida!\n");
    }while(n<1||n>num_lista);

    for(int i=0; i<n-1; i++)
        p=p->prox;
    resp.linha = p->linha; resp.coluna = p->coluna;
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
    return resposta;
}

struct jogada *CalculaJogadasValidas(int tab[8][8], int jogVez)
{
    int aux=1, lista_vazia=1;
    struct jogada *lista;
    lista = inicializa();
    struct jogada jog;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            jog.linha = j; jog.coluna = i;
            if (tab[jog.linha][jog.coluna]==0){
                for (int deltaL=-1;deltaL<=1&&aux;deltaL++){
                    for (int deltaC=-1;deltaC<=1&&aux;deltaC++){
                        if (deltaL!=0||deltaC!=0){
                            if (TestaDirecao(tab,jogVez,jog,deltaL,deltaC)){
                                lista = insere(lista, jog);
                                aux=0;
                                lista_vazia = 0;
                            }
                        }
                    }
                }
            }
            aux=1;
        }
    if(lista_vazia==0)
        return lista;
    else
        return NULL;
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
        lista = CalculaJogadasValidas(tabuleiro, jogaVez);

        if(lista == NULL)
        {
            printf("\nSem jogadas validas, perdeu a vez\n");
            jogaVez = -jogaVez;
        }
        else
        {
            if (jogaVez==1){
            printf("\nJogador Brancas\n");
            }else printf("\nJogador Pretas\n");

            jog = EscolheJogada(lista);

            ExecutaJogada(tabuleiro,jogaVez,jog);
            jogaVez = -jogaVez;
            casasVazias--;
        }
        //printa_lista(lista);
    }
    system("cls");
    DesenhaTabuleiro(tabuleiro);
    CalculaVencedor(tabuleiro);
}