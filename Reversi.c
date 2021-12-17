#include <stdio.h>

struct jogada{
    int linha,coluna;
};

struct Posicao{
    int tabuleiro[8][8];
    int jogadorVez;
};


struct Posicao IniciaTabuleiro(){
    struct Posicao jogo;

    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            jogo.tabuleiro[i][j]=0;
        }
    }
    jogo.tabuleiro[3][3] = jogo.tabuleiro[4][4] = 1;
    jogo.tabuleiro[3][4] = jogo.tabuleiro[4][3] = -1;

    return jogo;
}

void DesenhaTabuleiro(struct Posicao jogo){
    printf("  ");
    for (int i = 0; i < 8; i++) // Cria os numeros acima
        printf(" %d ",i);

    printf("\n +------------------------+\n");
    for (int i=0;i<8;i++){
        printf("%d|",i);
        for (int j=0;j<8;j++){
            if (jogo.tabuleiro[i][j]==0){
                printf(" - ");
            }else if (jogo.tabuleiro[i][j]==1){
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

int TestaDirecao(struct Posicao jogo, struct jogada jog, int deltaL, int deltaC){
    int i=jog.linha+deltaL;
    int j=jog.coluna+deltaC;
    int cont=0;

    while (i>=0 && i<8 && j>=0 && j<8 && jogo.tabuleiro[i][j]==-jogo.jogadorVez){
        cont++;
        i += deltaL;
        j += deltaC;
    }

    if (i>=8||i<0||j>=8||j<0){
        cont = 0;
    }else if (jogo.tabuleiro[i][j]==0)
        cont = 0;

    return cont;
}

struct Posicao ViraPedrasDirecao(struct Posicao jogo, struct jogada jog, int deltaL, int deltaC){
    int i=jog.linha+deltaL;
    int j=jog.coluna+deltaC;

    while (jogo.tabuleiro[i][j]==-jogo.jogadorVez){
        jogo.tabuleiro[i][j] = - jogo.tabuleiro[i][j];
        i += deltaL;
        j += deltaC;
    }
    return jogo;
}

struct Posicao ExecutaJogada(struct Posicao jogo, struct jogada jog, int *resposta){
    *resposta=0;

    if (jog.linha>=0&&jog.linha<8&&jog.coluna>=0&&jog.linha<8&&jogo.tabuleiro[jog.linha][jog.coluna]==0){

        for (int deltaL=-1;deltaL<=1;deltaL++){
            for (int deltaC=-1;deltaC<=1;deltaC++){
                if (deltaL!=0||deltaC!=0){
                    if (TestaDirecao(jogo, jog, deltaL, deltaC)){
                        jogo = ViraPedrasDirecao(jogo, jog, deltaL, deltaC);
                        *resposta=1;
                    }
                }
            }
        }

        if (*resposta==1){
            jogo.tabuleiro[jog.linha][jog.coluna] = jogo.jogadorVez;
        }
    }
    // ------------------------ Com Erro -------------------
    printf("\n--%d--\n", *resposta);// Debug
    return jogo;
}

void CalculaVencedor(struct Posicao jogo){
    int brancas=0;
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if (jogo.tabuleiro[i][j]==1)
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

    struct Posicao jogo;
    int resposta;
    jogo.jogadorVez = -1;
    int casasVazias = 60;
    struct jogada jog;


    jogo = IniciaTabuleiro();

    while (casasVazias>0){
        DesenhaTabuleiro(jogo);

        if (jogo.jogadorVez==1){
            printf("Jogador Brancas\n");
        }else printf("Jogador Pretas\n");

        jog = EscolheJogada();
        jogo = ExecutaJogada(jogo,jog, &resposta);

        if (resposta==0){
            printf("Jogada invalida\n");
        }else{
            jogo.jogadorVez = -jogo.jogadorVez;
            casasVazias--;
        }
    }

    CalculaVencedor(jogo);
}