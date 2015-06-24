#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//precisa para a abertura
#define WIDTH 80
#define HEIGHT 25

//tamanho maximo que a raquete assume (nao usado no jogo)
#define MAXRAQUETE 30

//tempo randomico para item aparecer, usado no srand
#define TEMPOITEM 50

//numero maximo de bolas que podem existir no jogo (o maximo usado no jogo eh 3)
#define MAXBOLAS 5

// bola estava inativa, isto eh, nao estava no jogo
#define INATIVA -1

// numero maximo de caracteres para o nome do mapa
#define MAXNAME 30

#include "arthomas.h"
//funcao principal do jogo
int main(int argc, char *argv[]) {
    FILE *high;
    int highscore = 0;
    int jogadores;
    int replay = 0;
    int opcao = 0;
    //abertura();
    mudaCor(15);

    do {
        system("cls");

        //tenta abrir o record.bin
        //se nao conseguir cria um novo e poem highscore=0 nele
        if(high = fopen("record.bin", "r+b")) {
            fread(&highscore, sizeof(int), 1, high);
            fclose(high);
        }
        else {
            high = fopen("record.bin", "wb");
            fwrite(&highscore, sizeof(int), 1, high);
            fclose(high);
        }
        fflush(stdin);
        GetAsyncKeyState(VK_RETURN);

        //menu retorna a opcao escolhida
        opcao = menu(highscore);

        fflush(stdin);
        switch(opcao) {
            case 1:
                replay = menuReplay();
                onePlayer(highscore, replay);
                break;
            case 2:
                replay = menuReplay();
                twoPlayer(replay);
                break;
            case 3:
                editMap();
                break;
            case 4:
                jogadores = menuBrutal();
                replay = menuReplay();
                brutalMode(jogadores, replay);
                break;
            case 5:
                rodaReplay();
                break;
        }
    } while(opcao != 6);
    return 0;
}

int editMap(){
    int opEd = menuEdicao();
}
