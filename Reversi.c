#include "stdio.h"

struct jogada{
    int linha,coluna;
};

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

        if (jogaVez==1){
            printf("Jogador Brancas\n");
        }else printf("Jogador Pretas\n");

        jog = EscolheJogada();

        if (ExecutaJogada(tabuleiro,jogaVez,jog)==0){
            printf("Jogada invalida\n");
        }else{
            jogaVez = -jogaVez;
            casasVazias--;
        }
    }

    CalculaVencedor(tabuleiro);
}