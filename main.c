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

int menu () {
    int i, j, posX = 50, posY = 13;
        char menuFundo[8][80] = {"                                   MENU                                ",
                                  "                      ________________________________                 ",
                                  "                     |                                |                ",
                                  "                     |   1 player:                    |                ",
                                  "                     |   2 player:                    |                ",
                                  "                     |   Criar mapa:                  |                ",
                                  "                     |   Modo Extreme:                |                ",
                                  "                     |________________________________|                "
                            };
    setCursor(0, 0);
    desenhaLogo();
    system("color ff");
    for (i = 0; i < 5; i++) {
        printf("\n");
        Sleep(150);
    }
    for (i = 0; i < 8; i++) {
        printf("%s\n", menuFundo[i]);
        Sleep(150);
    }
    for (i = 0; i < 5; i++) {
        printf("\n");
        Sleep(150);
    }
    while(!GetAsyncKeyState(VK_RETURN)) {
        setCursor(posX, posY);
        printf("<-");
        if(GetAsyncKeyState(VK_DOWN) && posY < 16) {
            setCursor(posX, posY);
            printf("  ");
            posY++;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_UP) && posY > 13) {
            setCursor(posX, posY);
            printf("  ");
            posY--;
            Sleep(100);

        }
        Sleep(1000/30);
    }
    return posY-12;
}

void setCursor(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(screen, coordinate);
}

void onePlayer(int dificuldade) {

    BOLA bola = {WIDTH/2, HEIGHT-3, 1, -dificuldade};
    PLAYER1 player1 = {WIDTH/2, HEIGHT-2, 10, 4, 0, 0};
    PLAYER2 player2 = {WIDTH/2, 1, 10, 1, 0, 0, 0};
    int i, j, ponto = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;
    system("cls");
    printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
    for(i=1; i<HEIGHT-1; i++){
        for(j=0; j<WIDTH; j++){
            //if(i == 0 || i == HEIGHT) printf("X");
            if(j == 0 || j == WIDTH-1) printf("X");
            else printf (" ");
        }
    }
    printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
    setCursor(0,0);

    while(!GetAsyncKeyState(VK_ESCAPE)) // enquanto a tecla ESC nao for pressionada
    {
        movimentoPlayer1(&player1);
        movimentoPlayer2(&player2, &bola);
        ponto = movimentoBola(&bola, &player1, &player2);
        player1.velX = 0;
        player2.velX = 0;
        if (ponto == 1) {
            setCursor(bola.posX, bola.posY);
            printf("_");
            bola.posX = player1.posXPlayer1+5;
            bola.posY = HEIGHT-3;
            bola.dirX = 1;
            bola.dirY = -dificuldade;
            pontuacaoPlayer1++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, HEIGHT-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }
        else if (ponto == 2) {
            setCursor(bola.posX, bola.posY);
            printf("_");
            bola.posX = player1.posXPlayer1+5;
            bola.posY = HEIGHT-3;
            bola.dirX = 1;
            bola.dirY = -dificuldade;
            pontuacaoPlayer2++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, HEIGHT-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }

        Sleep(1000/20); //30 frames por segundo
    }
}

void twoPlayer(int dificuldade) {
    BOLA bola = {WIDTH/2, HEIGHT-3, 1, -dificuldade};
    PLAYER1 player1 = {WIDTH/2, HEIGHT-2, 10, 4, 0, 0};
    PLAYER2 player2 = {WIDTH/2, 1, 10, 4, 0, 0, 1};
    int i, j, ponto = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;
    system("cls");
    printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
    for(i=1; i<HEIGHT-1; i++){
        for(j=0; j<WIDTH; j++){
            //if(i == 0 || i == HEIGHT) printf("X");
            if(j == 0 || j == WIDTH-1) printf("X");
            else printf (" ");
        }
    }
    printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
    setCursor(0,0);

    while(!GetAsyncKeyState(VK_ESCAPE)) // enquanto a tecla ESC nao for pressionada
    {
        movimentoPlayer1(&player1);
        movimentoPlayer2(&player2, &bola);
        ponto = movimentoBola(&bola, &player1, &player2);
        player1.velX = 0;
        player2.velX = 0;
        if (ponto == 1) {
            setCursor(bola.posX, bola.posY);
            printf("_");
            bola.posX = player1.posXPlayer1;
            bola.posY = HEIGHT-3;
            bola.dirX = 1;
            bola.dirY = -dificuldade;
            pontuacaoPlayer1++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, HEIGHT-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }
        else if (ponto == 2) {
            setCursor(bola.posX, bola.posY);
            printf("_");
            bola.posX = player1.posXPlayer1;
            bola.posY = HEIGHT-3;
            bola.dirX = 1;
            bola.dirY = -dificuldade;
            pontuacaoPlayer2++;
            setCursor(0, 0);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, HEIGHT-1);
            printf("SCORE: %d________________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            Sleep(1000);
        }

        Sleep(1000/20); //30 frames por segundo
    }
}
