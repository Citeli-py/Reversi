#include <stdio.h>
#include <stdlib.h>

struct jogada
{
    int linha, coluna;
    struct jogada *prox,*ant;
};

struct posicao
{
    int tabuleiro[8][8];
    int jogadorVez;
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



//verificar o tamanho da lista
int tamanho(struct jogada *lista)
{
    int n = 0;

    struct jogada *j = lista->ant;

    for(struct jogada *k = lista; k!=j; k=k->prox)
        {

            n++;

        }
    n = n+2;

    return n;
}



//destruindo a lista
void destruirlista(struct jogada *lista)
{

    int contador = 0;
    int n = tamanho(lista);   
    struct jogada *t;
    struct jogada *p = lista;
    
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



struct jogada EscolheJogada(struct jogada *lista)
{
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


int TestaDirecao(int tab[8][8], int jogVez, struct jogada jog, int deltaL, int deltaC)
{
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

void ViraPedrasDirecao(int tab[8][8],int jogVez, struct jogada jog, int deltaL, int deltaC)
{
    int i=jog.linha+deltaL;
    int j=jog.coluna+deltaC;

    while (tab[i][j]==-jogVez)
    {
        tab[i][j] = - tab[i][j];
        i += deltaL;
        j += deltaC;
    }

}

int ExecutaJogada(struct posicao *jogo, struct jogada jog){
    
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
        jogo->tabuleiro[jog.linha][jog.coluna] = jogVez;
    }
    return resposta;
}

struct jogada *CalculaJogadasValidas(struct posicao joga)
{
    int jogVez = joga.jogadorVez;

    int aux=1, lista_vazia=1;
    struct jogada *lista;
    lista = inicializa();
    struct jogada jog;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            jog.linha = j; jog.coluna = i;
            if (joga.tabuleiro[jog.linha][jog.coluna]==0){
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

int main(){

    int casasVazias = 60;
    struct jogada jog;
    struct posicao joga;
    joga = IniciaTabuleiro();
    struct jogada *lista;
    

    while (casasVazias>0)
    {
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

            ExecutaJogada(&joga,jog);
            joga.jogadorVez = -joga.jogadorVez;
            casasVazias--;
        }
        

    }


    system("cls");
    DesenhaTabuleiro(joga);
    CalculaVencedor(joga.tabuleiro);
    destruirlista(lista);
    printa_lista(lista);

}
