#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 10
#define NAVIOS 5
#define BOMBAS 10
#define MAX_TENTATIVAS 10
#define MAX_VIDAS 5

// preencher o tabuleiro com as bombas, navios e agua
void preencherTABULEIRO(int tabuleiro[TAM][TAM]);
// procedimento que inicia o jogo caso o usuario digite 1
void jogarOJogo(int tabuleiro[TAM][TAM], char* nome, int* tentativas, int* naviosEncontrados, int* bombasEncontradas, int* vidas, int jogadas[10][2], int* jogadasR);
// procedimento que salva as rodadas
void salvarJogo(char* nome, int tabuleiro[TAM][TAM], int tentativas, int naviosEncontrados, int bombasEncontradas, int vidas);
// função que retorna a rodada salva
int lerRodada(char* nome, int tabuleiro[TAM][TAM], int* tentativas, int* naviosEncontrados, int* bombasEncontradas, int* vidas);
// procedimento que salva os usuarios no ranking caso eles vencam a rodada
void salvarRanking(char* nome, int pontos);
// procedimento que exibe o rank para a tela 04
void imprimirRanking();
// procedimento para entrada segura
void limparBuffer();


int main() {
    int tabuleiro[TAM][TAM], jogadas[10][2], jogadasR = 0;
    int opMenu;
    char nome[50];
    int tentativas = 10;
    int naviosEncontrados = 0;
    int bombasEncontradas = 0;
    int vidas = 5;

    do {
        printf("\nJogo da Batalha Naval\n");
        printf("\n1 - Jogar\n");
        printf("2 - Ver pontuacoes\n");
        printf("0 - Sair\n");
        printf("\nDigite sua opcao: ");
        scanf("%d", &opMenu);
        limparBuffer();

        switch (opMenu){
        case 1: 
            printf("\nInsira o nome do jogador: \n");
            printf(">> ");
            scanf("%s", &nome);
            limparBuffer();

            // se o procedimento lerRodada funcionar com êxito, salva a rodada do usuario e pergunta se quer continuar de onde parou.
            if (lerRodada(nome, tabuleiro, &tentativas, &naviosEncontrados, &bombasEncontradas, &vidas)) {
                printf("\nEncontramos uma partida em seu nome pausada.\n");
                printf("\n1 - Recomeçar de onde parou.");
                printf("\n2 - Começar uma nova partida.");
                printf("\nDigite sua opcao: \n");
                printf(">> ");
                scanf("%d", &opMenu);
                limparBuffer();

                // tratativa de erro para o caso de a entrada ser diferente de 1 ou 2.
                while (opMenu != 1 && opMenu != 2) {
                    printf("\nOpcao invalida.\nO que deseja fazer?\n1 - Recomecar de onde parou\n2 - Comecar uma nova partida\nDigite sua opcao: ");
                    printf(">> ");
                    scanf("%d", &opMenu);
                    limparBuffer();
                }
                if (opMenu == 2) {
                    // funcao remove para excluir o arq do sistema caso o usuario queira recomecar, fazendo com que o arquivo seja temporario.
                    remove(nome);
                    preencherTABULEIRO(tabuleiro);
                    tentativas = 10;
                    naviosEncontrados = 0;
                    bombasEncontradas = 0;
                    vidas = 5;
                }
            }
            jogarOJogo(tabuleiro, nome, &tentativas, &naviosEncontrados, &bombasEncontradas, &vidas, jogadas, &jogadasR);
            break;
        case 2:
            imprimirRanking();
            break;
        case 0:
            printf("\nEncerrando o jogo.\n");
            break;
        default:
            printf("\nOpção invalida.\nTente novamente com os numeros disponiveis no MENU\n");
            break;
        }
    } while (opMenu != 0);

    return 0;
} 
void preencherTABULEIRO(int tabuleiro[TAM][TAM]) {
    // variaveis necessarias para o processo de gerar e preencher os tabuleiros
    int l, c, naviosP = 0, bombasP = 0;

   // utiliza o contador do tempo atual do relogio como semente do computador para gerar o tabuleiro de maneira aleatoria
    srand(time(NULL));
    // preenche o tabuleiro com zeros
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    // distribui de maneira aleatoria os navios no tabuleiro
    while (naviosP < NAVIOS) {
        l = rand() % TAM;
        c = rand() % TAM;

        if (tabuleiro[l][c] == 0) {
            tabuleiro[l][c] = 2;
            naviosP++;
        }
    }
    // distribui de maneira aleatoria as bombas no tabuleiro
    while (bombasP < BOMBAS) {
        l = rand() % TAM;
        c = rand() % TAM;

        if (tabuleiro[l][c] == 0) {
            tabuleiro[l][c] = 1;
            bombasP++;
        }
    }
}
void jogarOJogo(int tabuleiro[TAM][TAM], char* nome, int* tentativasR, int* naviosEncontrados, int* bombasEncontradas, int* vidas, int jogadas[10][2], int* jogadasR) {
    int l, c, repeteJogo = 0;
    int opcao;
    // corpo principal da funcao. realiza e registra as jogadas dos jogadores, e verifica se o jogador deseja pausar ou continuar jogando, até que ele ganhe ou perca
    while (*tentativasR > 0 && *naviosEncontrados < NAVIOS && *vidas > 0) {
        // recebe a linha do usuario
        printf("\nInsira uma linha entre (0-9): ");
        printf(">> ");
        scanf("%d", &l);
        limparBuffer();
        // tratativa, caso o usuario digite um valor de linha invalido
        while (l < 0 || l >= TAM) {
            printf("Posicao invalida. Tente novamente uma linha valida entre (0-9).\n");
            printf(">> ");
            scanf("%d", &l);
            limparBuffer();
            
        }
        // recebe a coluna do usuario
        printf("Insira outro numero entre (0 e 9): ");
        printf(">> ");
        scanf("%d", &c);
        limparBuffer();
        // tratativa, caso o usuario digite um valor de coluna invalido
        while (c < 0 || c >= TAM) {
            printf("Posicao invalida. Digite uma coluna valida no range (0-9): \n");
            printf(">> ");
            scanf("%d", &c);
            limparBuffer();
        }

        repeteJogo = 0; // variavel de verificacao condicional para controlar as jogadas repetidas
        // verificacao no vetor jogadas se a jogada já existe
        for (int i = 0; i < *jogadasR; i++) {
            if (jogadas[i][0] == l && jogadas[i][1] == c) {
                repeteJogo = 1;
                break;
            }
        }
        // condicao que realiza o reinicio da rodada atual do jogo, caso a jogada seja repetida
        if (repeteJogo) {
            printf("\nVoce ja tentou essa posicao. Tente novamente outra opcao.\n");
            continue;
        }

        //registro e incremento do vetor que registra as jogadas e da variavel de contagem das jogadas realizadas
        jogadas[*jogadasR][0] = l;
        jogadas[*jogadasR][1] = c;
        (*jogadasR)++;

        // verificacao do elemento presente na coordenada da jogada realizada pelo jogador
        if (tabuleiro[l][c] == 2) {
            printf("\nNAVIO ENCONTRADO!\n");
            (*naviosEncontrados)++;
        }
        else if (tabuleiro[l][c] == 1) {
            printf("\nBOMBA ENCONTRADA! Voce perdeu uma vida.\n");
            (*vidas)--;
        }
        else {
            printf("\nSEU DISPARO ACERTOU A AGUA!\n");
        }
        (*tentativasR)--; // reducao das tentativas restantes do jogador apos uma jogada realizada

        // informa a situacao atual do usuario na partida
        printf("\nTentativa restantes: %d\nVidas restantes: %d\nPontos: %d\n", *tentativasR, *vidas, 10 - (*bombasEncontradas * 2));
        // pergunta se o usuario deseja, ainda, continuar jogando ou pausar a partida atual, salvando o arquivo
        printf("\nDeseja pausar o jogo e sair?\n[1] - SIM\n[0] - NAO: ");
        scanf("%d", &opcao);
        limparBuffer();
        // tratativa para o caso de o usuario digitar uma opcao invalida
        while (opcao != 1 && opcao != 0) {
            printf("\nOpcao invalida. Deseja salvar o jogo e sair?\n[1] - SIM\n[0] - NAO:  ");
            printf(">> ");
            scanf("%d", &opcao);
            limparBuffer();
        }
        // se a opcao escolhida pelo usuario for a de salvar, salva o estado atual da partida e sai dela
        if (opcao == 1) {
            salvarJogo(nome, tabuleiro, *tentativasR, *naviosEncontrados, *bombasEncontradas, *vidas);
            return;
        }
    }
    // verifica qual das condicoes foram atendidas para que o laco principal tenha se encerrado e imprime uma mensagem correspondente
    if (*naviosEncontrados == NAVIOS) {
        int pontos = 10 - (*bombasEncontradas * 2);
        printf("\nParabéns! Você encontrou todos os navios.\n");
        printf("Pontuacao final: %d\n", pontos);
        salvarRanking(nome, pontos);//se o jogador venceu a partida, registra seu nome e sua pontuacao no ranking
    }
    else if (*vidas == 0) {
        printf("\nVoce perdeu todas as vidas.\nFim de jogo.\n");
    }
    else{
    printf("\nSuas tentativas acabaram.\nFim de jogo.\n");
    }
}   
void salvarJogo(char* nome, int tabuleiro[TAM][TAM], int tentativas, int naviosEncontrados, int bombasEncontradas, int vidas) {
    FILE* arq;
    // cria o arquivo binario com o nome do jogador para gravacao
    arq = fopen(nome, "wb");
    if (arq == NULL) {
        printf("\nErro ao salvar o jogo.\n");
        return;
    }
    // salva no arquivo as informacoes referentes ao jogador e a partida em questao que esta sendo salva
    fwrite(tabuleiro, sizeof(int), TAM * TAM, arq);
    fwrite(&tentativas, sizeof(int), 1, arq);
    fwrite(&naviosEncontrados, sizeof(int), 1, arq);
    fwrite(&bombasEncontradas, sizeof(int), 1, arq);
    fwrite(&vidas, sizeof(int), 1, arq);
    fclose(arq); // fecha o arquivo apos salvar ele
}
int lerRodada(char* nome, int tabuleiro[TAM][TAM], int* tentativas, int* naviosEncontrados, int* bombasEncontradas, int* vidas) {
    FILE* arquivo;
    // abre o arquivo binario com o nome do jogador para leitura
    arquivo = fopen(nome, "rb");
    if (arquivo == NULL) {
        return 0;
    }
    // le do arquivo as informacoes necessarias referentes ao jogador e a partida que foi pausada
    fread(tabuleiro, sizeof(int), TAM * TAM, arquivo);
    fread(tentativas, sizeof(int), 1, arquivo);
    fread(naviosEncontrados, sizeof(int), 1, arquivo);
    fread(bombasEncontradas, sizeof(int), 1, arquivo);
    fread(vidas, sizeof(int), 1, arquivo);

    fclose(arquivo);// fecha o arquivo apos a leitura das informacoes necessarias para continuar uma partida

    return 1;
}
void salvarRanking(char* nome, int pontos) {
    // abre o arquivo binario do ranking para gravar os dados dos jogadores com maiores pontuacoes
    FILE* ranking = fopen("ranking.bin", "ab");

    if (ranking == NULL) {
        printf("\nErro ao salvar o ranking.\n");
        return;
    }
    // grava no ranking os nomes e as pontuacoes dos mais bem qualificados 
    int extentName = strlen(nome);
    fwrite(&extentName, sizeof(int), 1, ranking);
    fwrite(nome, sizeof(char), extentName, ranking);
    fwrite(&pontos, sizeof(int), 1, ranking);

    fclose(ranking); // fecha o arquivo ranking apos a gravacao dos dados
}
void imprimirRanking() {
    // abre o arquivo binario com o ranking para leitura dos dados
    FILE* ranking = fopen("ranking.bin", "rb");
    char nome[50];
    int extentName;
    int pontos;

    if (ranking == NULL) {
        printf("\nNenhuma pontuação registrada.\n");
        return;
    }
    // le e exibe o nome e os pontos dos jogadores no ranking 
    printf("\nRanking:\n");
    while (fread(&extentName, sizeof(int), 1, ranking) == 1) {
        fread(nome, sizeof(char), extentName, ranking);
        nome[extentName] = '\0';
        fread(&pontos, sizeof(int), 1, ranking);
        printf("\n%s - %d pontos\n", nome, pontos);
    }
    fclose(ranking); // fecha o arquivo do ranking apos a leitura e exibicao dos dados do placar

    // tratativa que nao fecha o ranking ate que o usario digite a letra 'v'
    printf("\nDigite V para voltar à tela inicial: \n");
    printf(">> ");
    char op;
    do {
        scanf(" %c", &op);
    } while (op != 'V' && op != 'v');
}
void limparBuffer() {
    char c;
    c = getchar();
    while (c != '\n') {
        c = getchar();
    }
}
