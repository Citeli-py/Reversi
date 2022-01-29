#include <stdio.h>
#include <stdlib.h>

struct jogada
{
    int linha, coluna;
};

struct elemento
{
    struct jogada jog;
    struct elemento *prox,*ant;
};

struct posicao
{
    int tabuleiro[8][8];
    int jogadorVez;
};


int printa_lista(struct elemento *lista)
{
    struct elemento *p = lista;
    struct elemento *fim = lista;
    int i=0;
    //printf("\n");
    do
    {
        printf("%d-(%d, %d)\n",i+1, p->jog.linha, p->jog.coluna);
        p = p->prox;
        i++;
    }while (p != fim);
    printf("\n");
    return i;
}


struct elemento *inicializa()
{
    return NULL;
}


struct elemento *Criaposicao(int linha, int coluna)
{
    struct elemento *novo = (struct elemento*)malloc(sizeof(struct elemento));
    novo->jog.linha = linha;
    novo->jog.coluna = coluna;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}


struct elemento *insere(struct elemento *lista, struct elemento jog)
{
    struct elemento *novo = Criaposicao(jog.jog.linha, jog.jog.coluna);

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

//verificar o tamanho da lista
int tamanho(struct elemento *lista){
    if (lista==NULL) return 0;  
    int cont = 0;
    struct elemento *aux = lista; 

    do{
        cont++;
        aux = aux->prox;
    }while (aux!=lista); 
    return cont;
}

//destruindo a lista
void destruirlista(struct elemento *lista)
{

    int contador = 0;
    int n = tamanho(lista);   
    struct elemento *t;
    struct elemento *p = lista;
    while (contador <= n)
    {

        t = p->prox; 
        free(p); 
        p = t; 
        contador++;
    }

}

struct posicao IniciaTabuleiro()
{
    struct posicao joga;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            joga.tabuleiro[i][j]=0;
        }
    }
    joga.tabuleiro[3][3] = joga.tabuleiro[4][4] = 1;
    joga.tabuleiro[3][4] = joga.tabuleiro[4][3] = -1;

    joga.jogadorVez = -1;

    return joga;
}

void DesenhaTabuleiro(struct posicao joga)
{
    printf("  ");
    for (int i = 0; i < 8; i++) // Cria os numeros acima
        printf(" %d ",i);

    printf("\n +------------------------+\n");
    for (int i=0;i<8;i++){
        printf("%d|",i);
        for (int j=0;j<8;j++){
            if (joga.tabuleiro[i][j]==0){
                printf(" - ");
            }else if (joga.tabuleiro[i][j]==1){
                printf(" W ");
            }else printf(" B ");
        }
        printf("|\n");
    }
    printf(" +------------------------+\n");
}

struct elemento EscolheJogada(struct elemento *lista)
{
    struct elemento resp;
    struct elemento *p=lista;
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
    resp.jog.linha = p->jog.linha; resp.jog.coluna = p->jog.coluna;
    return resp;
}


int TestaDirecao(int tab[8][8], int jogVez, struct elemento jog, int deltaL, int deltaC)
{
    int i=jog.jog.linha+deltaL;
    int j=jog.jog.coluna+deltaC;
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

void ViraPedrasDirecao(int tab[8][8],int jogVez, struct elemento jog, int deltaL, int deltaC)
{
    int i=jog.jog.linha+deltaL;
    int j=jog.jog.coluna+deltaC;

    while (tab[i][j]==-jogVez)
    {
        tab[i][j] = - tab[i][j];
        i += deltaL;
        j += deltaC;
    }

}

int ExecutaJogada(struct posicao *jogo, struct elemento jog){
    
    int jogVez = jogo->jogadorVez;
    
    int resposta=0;

    for (int deltaL=-1;deltaL<=1;deltaL++)
    {
        for (int deltaC=-1;deltaC<=1;deltaC++)
        {
            if (deltaL!=0||deltaC!=0){
                if (TestaDirecao(jogo->tabuleiro,jogVez,jog,deltaL,deltaC))
                {
                    ViraPedrasDirecao(jogo->tabuleiro,jogVez,jog,deltaL,deltaC);
                    resposta=1;
                }
            }
        }
    }
    if (resposta==1)
    {
        jogo->tabuleiro[jog.jog.linha][jog.jog.coluna] = jogVez;
    }
    return resposta;
}

struct elemento *CalculaJogadasValidas(struct posicao joga)
{
    int jogVez = joga.jogadorVez;

    int aux=1, lista_vazia=1;
    struct elemento *lista;
    lista = inicializa();
    struct elemento jog;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            jog.jog.linha = j; jog.jog.coluna = i;
            if (joga.tabuleiro[jog.jog.linha][jog.jog.coluna]==0){
                for (int deltaL=-1;deltaL<=1&&aux;deltaL++){
                    for (int deltaC=-1;deltaC<=1&&aux;deltaC++){
                        if (deltaL!=0||deltaC!=0){
                            if (TestaDirecao(joga.tabuleiro,jogVez,jog,deltaL,deltaC)){
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