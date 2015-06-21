#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 25

#include "movimentos.h"
#include "menu.h"
#include "edicao.h"
#include "nivel.h"
#include "animacoes.h"
#include "replay.h";

void onePlayer(int dificuldade);
void twoPlayer(int dificuldade);

void setCursor(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(screen, coordinate);
}

void mudaCor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main(int argc, char *argv[]) {
    int opcao = 0;
    //abertura();
    mudaCor(15);
    do {
        system("cls");
        fflush(stdin);
        GetAsyncKeyState(VK_RETURN);
        opcao = menu();
        fflush(stdin);
        switch(opcao) {
            case 1:
                onePlayer(1);
                break;
            case 2:
                twoPlayer(1);
                break;
            case 3:
                editMap();
                break;
            case 4:
//                brutalMode();
                break;
            case 5:
                rodaReplay();
        }
    } while(opcao != 6);
    return 0;
}

int editMap(){
    int opEd = menuEdicao();
}

void onePlayer(int dificuldade) {
    //GetAsyncKeyState(VK_RETURN);
    //MAPA mapa = {25, 80 , 186, {0}};
    FILE *replay;
    if((replay = fopen("replay", "wb")) != 1) {
        printf("Erro ao abrir arquivo replay!");
    }
    MAPA mapa;
    char qualMapa[30] = "maps";
    //fflush(stdin);
    //clearBuff();
    //system("cls");
    //printf("Escolha o mapa:\n");
    //scanf("%s",qualMapa);
    //clearBuff();
    char idMapa[5];
    srand(time(NULL));
    itoa(rand()%5, idMapa, 10);
    strcat(qualMapa, idMapa);
    strcat(qualMapa, ".txt");
    carregaMapaOnePlayer(qualMapa, &mapa);

    int nivel = 20;

    NIVEL st_nivel;
    FILE* arqNivel;
    arqNivel = fopen("arqNiv","rb");
    fseek(arqNivel,(nivel-1)*sizeof(NIVEL),SEEK_SET);
    fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
    fclose(arqNivel);

    BOLA bola = {{mapa.colunas/2, 13, 30, 7, 7}, {mapa.linhas-1, 13, 20, 7, 7}, {st_nivel.velBola, st_nivel.velBola, st_nivel.velBola, st_nivel.velBola, st_nivel.velBola}, {-st_nivel.velBola, -st_nivel.velBola, -st_nivel.velBola, -st_nivel.velBola, -st_nivel.velBola}, 1, 166};

    PLAYER1 player1 = {mapa.colunas/2, mapa.linhas, st_nivel.tamPlayer1, st_nivel.velPlayer1, 0, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {mapa.colunas/2, 1, st_nivel.tamPlayer2, st_nivel.velPlayer2, 0, 0, st_nivel.IAPlayer2, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    int i, j, ponto = 0, ponto1 = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;
    system("cls");
    printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", pontuacaoPlayer2, nivel);
    printaMapa(&mapa);
    mudaCor(15);
    printf("SCORE: %3d_____________________________________________________________________", pontuacaoPlayer1);
    //desenhaMapa();
    setCursor(0,0);

    while(!GetAsyncKeyState(VK_ESCAPE)) // enquanto a tecla ESC nao for pressionada
    {
        movimentoPlayer1(&player1, &mapa);
        movimentoPlayer2(&player2, &bola, &mapa);
        ponto = movimentoBola(&bola, &player1, &player2, &mapa);
        player1.velX = 0;
        player2.velX = 0;
        if (ponto == 1) {
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");
            bola.posX[bola.bolaFora] = player2.posXPlayer2+(player2.tamanho/2);
            bola.posY[bola.bolaFora] = player2.posYPlayer2+1;
            bola.dirY[bola.bolaFora] = st_nivel.velBola;
            pontuacaoPlayer1++;
            //setCursor(0, 0);
            //mudaCor(15);
            //printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", pontuacaoPlayer2, nivel);
            //setCursor(0, mapa.linhas+1);
            //printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
            printaScore(pontuacaoPlayer1, pontuacaoPlayer2, nivel, mapa.linhas);
            Sleep(200);
            if(pontuacaoPlayer1 == 2) {
                nivel++;
                arqNivel = fopen("arqNiv","rb");
                fseek(arqNivel,(nivel-1)*sizeof(NIVEL),SEEK_SET);
                fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
                fclose(arqNivel);
                player1.dirX = st_nivel.velPlayer1;
                player2.dirX = st_nivel.velPlayer2;
                player1.tamanho = st_nivel.tamPlayer1;
                player2.tamanho = st_nivel.tamPlayer2;
                player2.nivelIA = st_nivel.IAPlayer2;
                bola.dirX[0] = st_nivel.velBola; bola.dirX[1] = st_nivel.velBola; bola.dirX[2] = st_nivel.velBola; bola.dirX[3] = st_nivel.velBola; bola.dirX[4] = st_nivel.velBola;
                bola.dirY[0] = st_nivel.velBola; bola.dirY[1] = st_nivel.velBola; bola.dirY[2] = st_nivel.velBola; bola.dirY[3] = st_nivel.velBola; bola.dirY[4] = st_nivel.velBola;
                pontuacaoPlayer1 = 0;
                pontuacaoPlayer2 = 0;
                srand(time(NULL));
                strcpy(qualMapa, "maps");
                itoa(rand()%5, idMapa, 10);
                strcat(qualMapa, idMapa);
                strcat(qualMapa, ".txt");
                carregaMapaOnePlayer(qualMapa, &mapa);
                player1.posYPlayer1 = mapa.linhas;
                system("cls");
                printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", pontuacaoPlayer2, nivel);
                printaMapa(&mapa);
                mudaCor(15);
                printf("SCORE: %3d_____________________________________________________________________", pontuacaoPlayer1);
                printaScore(pontuacaoPlayer1, pontuacaoPlayer2, nivel, mapa.linhas);
                Sleep(400);
            }
        }
        else if (ponto == 2) {
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");
            bola.posX[bola.bolaFora] = player1.posXPlayer1+(player1.tamanho/2);
            bola.posY[bola.bolaFora] = player1.posYPlayer1-1;
            bola.dirY[bola.bolaFora] = -st_nivel.velBola;
            pontuacaoPlayer2++;
            setCursor(0, 0);
            mudaCor(15);
            printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", pontuacaoPlayer2, nivel);
            setCursor(0, mapa.linhas+1);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(200);
            if(pontuacaoPlayer2 == 5) {
                gameOver();
                salvaReplay(atoi(idMapa), &player1, &player2, &bola, pontuacaoPlayer1, pontuacaoPlayer2, nivel, replay);
                fclose(replay);
                return;
            }
        }
        salvaReplay(atoi(idMapa), &player1, &player2, &bola, pontuacaoPlayer1, pontuacaoPlayer2, nivel, replay);
        Sleep(1000/20); //30 frames por segundo
    }
    fclose(replay);
}

void twoPlayer(int dificuldade) {
    //MAPA mapa = {25, 80 , 186, {0}};
    MAPA mapa;
    char qualMapa[30] = "maps";
    fflush(stdin);
    clearBuff();
    system("cls");
    printf("Escolha o mapa:\n");
    scanf("%s",qualMapa);
    clearBuff();
    carregaMapaOnePlayer(qualMapa, &mapa);
    BOLA bola = {{mapa.colunas/2, 10, 30, 7, 7}, {mapa.linhas-1, 10, 20, 7, 7}, {1, 1, 1, 1, 1}, {-dificuldade, dificuldade, -dificuldade, dificuldade, dificuldade}, 1, 219};
    PLAYER1 player1 = {mapa.colunas/2, mapa.linhas, 10, 4, 0, 0,  {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {mapa.colunas/2, 1, 10, 4, 0, 0, 0, 1, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    int i, j, ponto = 0, ponto1 = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;
    system("cls");
    printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
    for(i=0; i<mapa.linhas; i++){
        for(j=0; j<mapa.colunas; j++){
            //if(i == 0 || i == HEIGHT) printf("X");
            //if(j == 0 || j == mapa.colunas-1) printf("%c", mapa.borda);
            //else printf (" ");
            if(j == 0 || j  == mapa.colunas-1) {
                mudaCor(15);
                if(mapa.mapa[i][j] == 1) {
                    printf("%c", mapa.borda);
                }
                else {
                    mudaCor(15);
                    printf (" ");
                }
            }
            else {
                mudaCor(7);
                if(mapa.mapa[i][j] == 1) {
                    printf("%c", 219);
                }
                else {
                    mudaCor(15);
                    printf (" ");
                }
            }
        }
        if(mapa.colunas < 80) {
            printf("\n");
        }
    }
    mudaCor(15);
    printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
    //desenhaMapa();
    setCursor(0,0);

    while(!GetAsyncKeyState(VK_ESCAPE)) // enquanto a tecla ESC nao for pressionada
    {
        movimentoPlayer1(&player1, &mapa);
        movimentoPlayer2(&player2, &bola, &mapa);
        ponto = movimentoBola(&bola, &player1, &player2, &mapa);
        player1.velX = 0;
        player2.velX = 0;
        if (ponto == 1) {
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");
            bola.posX[bola.bolaFora] = player2.posXPlayer2+(player2.tamanho/2);
            bola.posY[bola.bolaFora] = player2.posYPlayer2+1;
            bola.dirY[bola.bolaFora] = dificuldade;
            pontuacaoPlayer1++;
            setCursor(0, 0);
            mudaCor(15);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas+1);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(0);
        }
        else if (ponto == 2) {
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");
            bola.posX[bola.bolaFora] = player1.posXPlayer1+(player1.tamanho/2);
            bola.posY[bola.bolaFora] = player1.posYPlayer1-1;
            bola.dirY[bola.bolaFora] = -dificuldade;
            pontuacaoPlayer2++;
            setCursor(0, 0);
            mudaCor(15);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas+1);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            //Sleep(200);
        }

        Sleep(1000/30); //30 frames por segundo
    }
}
