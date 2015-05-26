#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 25

#include "animacoes.h"
#include "movimentos.h"
#include "menu.h"

void onePlayer(int dificuldade);
void twoPlayer(int dificuldade);

int main(int argc, char *argv[]) {
    int opcao = 0;
    //abertura();
    opcao = menu();
    switch(opcao) {
        case 1:
            onePlayer(1);
            break;
        case 2:
            twoPlayer(1);
            break;
        case 3:
//            editMap();
            break;
        case 4:
 //           brutalMode();
            break;
    }
    return 0;
}

void setCursor(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(screen, coordinate);
}

void onePlayer(int dificuldade) {
    //MAPA mapa = {25, 80 , 186, {0}};
    MAPA mapa;
    carregaMapaOnePlayer("mapa1.txt", &mapa);
    BOLA bola = {{mapa.colunas/2, 10, 30, 7, 7}, {mapa.linhas-1, 10, 20, 7, 7}, {1, 1, 1, 1, 1}, {-dificuldade, dificuldade, -dificuldade, dificuldade, dificuldade}, 3};
    PLAYER1 player1 = {mapa.colunas/2, mapa.linhas, 10, 4, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {mapa.colunas/2, 1, 10, 1, 0, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    int i, j, ponto = 0, ponto1 = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;
    printf("%d %d", mapa.linhas, mapa.colunas);
    system("cls");
    printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
    for(i=0; i<mapa.linhas; i++){
        for(j=0; j<mapa.colunas; j++){
            //if(i == 0 || i == HEIGHT) printf("X");
            //if(j == 0 || j == mapa.colunas-1) printf("%c", mapa.borda);
            //else printf (" ");
            if(mapa.mapa[i][j] == 1) {
                printf("%c", mapa.borda);
            }
            else {
                printf (" ");
            }
        }
        if(mapa.colunas < 80) {
            printf("\n");
        }
    }
    //printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
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
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas+1);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            //Sleep(200);
        }

        Sleep(1000/30); //30 frames por segundo
    }
}

void twoPlayer(int dificuldade) {
    MAPA mapa = {25, 80, 186, {0}};
    BOLA bola = {{mapa.colunas/2, 0, 0, 0, 0}, {mapa.linhas-3, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {-dificuldade, 0, 0, 0, 0}, 1};
    PLAYER1 player1 = {mapa.colunas/2, mapa.linhas-2, 10, 1, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {mapa.colunas/2, 1, 10, 1, 0, 0, 1, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    int i, j, ponto = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;
    system("cls");
    printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
    for(i=0; i<mapa.linhas-2; i++){
        for(j=0; j<mapa.colunas; j++){
            //if(i == 0 || i == HEIGHT) printf("X");
            if(j == 0 || j == mapa.colunas-1) printf("%c", mapa.borda);
            else printf (" ");
        }
        if(mapa.colunas < 80) {
            printf("\n");
        }
    }
    printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
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
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }
        else if (ponto == 2) {
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");
            bola.posX[bola.bolaFora] = player1.posXPlayer1+(player1.tamanho/2);
            bola.posY[bola.bolaFora] = player1.posYPlayer1-1;
            bola.dirY[bola.bolaFora] = -dificuldade;
            pontuacaoPlayer2++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }
        Sleep(1000/30); //30 frames por segundo
    }
}
