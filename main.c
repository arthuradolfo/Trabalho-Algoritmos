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

int menu();
void onePlayer(int dificuldade);
void twoPlayer(int dificuldade);

int main(int argc, char *argv[]) {
    int opcao = 0;
    //abertura();
    opcao = menu();
    switch(opcao) {
        case 1:
            onePlayer(2);
            break;
        case 2:
            twoPlayer(2);
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
    MAPA mapa = {25, 80 , 186, {0}};
    BOLA bola = {mapa.colunas/2, mapa.linhas-3, 2, -dificuldade};
    PLAYER1 player1 = {mapa.colunas/2, mapa.linhas-2, 10, 4, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {mapa.colunas/2, 1, 10, 1, 0, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
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
            setCursor(bola.posX, bola.posY);
            printf("_");
            bola.posX = player2.posXPlayer2+(player2.tamanho/2);
            bola.posY = player2.posYPlayer2+1;
            bola.dirY = dificuldade;
            pontuacaoPlayer1++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }
        else if (ponto == 2) {
            setCursor(bola.posX, bola.posY);
            printf("_");
            bola.posX = player1.posXPlayer1+(player1.tamanho/2);
            bola.posY = player1.posYPlayer1-1;
            bola.dirY = -dificuldade;
            pontuacaoPlayer2++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }

        Sleep(1000/20); //30 frames por segundo
    }
}

void twoPlayer(int dificuldade) {
    MAPA mapa = {25, 80 , {0}, 186};
    BOLA bola = {mapa.colunas/2, mapa.linhas-3, 1, -dificuldade};
    PLAYER1 player1 = {mapa.colunas/2, mapa.linhas-2, 10, 4, 0, 0};
    PLAYER2 player2 = {mapa.colunas/2, 1, 10, 4, 0, 0, 1};
    int i, j, ponto = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;
    system("cls");
    printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
    for(i=1; i<mapa.linhas-1; i++){
        for(j=0; j<mapa.colunas; j++){
            //if(i == 0 || i == HEIGHT) printf("X");
            if(j == 0 || j == mapa.colunas-1) printf("X");
            else printf (" ");
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
            setCursor(bola.posX, bola.posY);
            printf("_");
            bola.posX = player2.posXPlayer2+(player2.tamanho/2);
            bola.posY = player2.posYPlayer2;
            bola.dirX = 1;
            bola.dirY = dificuldade;
            pontuacaoPlayer1++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }
        else if (ponto == 2) {
            setCursor(bola.posX, bola.posY);
            printf("_");
            bola.posX = player1.posXPlayer1+(player1.tamanho/2);
            bola.posY = player1.posYPlayer1;
            bola.dirX = 1;
            bola.dirY = -dificuldade;
            pontuacaoPlayer2++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }

        Sleep(1000/20); //30 frames por segundo
    }
}
