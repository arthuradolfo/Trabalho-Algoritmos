void setCursor(int x, int y);
void abertura();
void desenhaLogo();
void clearBuff(void)
{
  while ( getc(stdin) != '\n' );
}

void abertura() {
    int i, j, k = 0, acaba = 0, posX=WIDTH/2, posY=HEIGHT/2, dirX=1, dirY=1;
    char fraseAbertura[2][80] = {"Arthur e Thomas apresentam:", "ARTHOMAS, O jogo dos campeoes"};
    char abertura[5][80] = {"         _      ____    _____   _   _    ___    __  __      _      ____",
                             "        / \\    |  _ \\  |_   _| | | | |  / _ \\  |  \\/  |    / \\    / ___|",
                             "       / _ \\   | |_) |   | |   | |_| | | | | | | |\\/| |   / _ \\   \\___ \\ ",
                             "      / ___ \\  |  _ <    | |   |  _  | | |_| | | |  | |  / ___ \\   ___) |",
                             "     /_/   \\_\\ |_| \\_\\   |_|   |_| |_|  \\___/  |_|  |_| /_/   \\_\\ |____/ "
                           };
    // desenha a tela
    for (i = 0; i < 2; i++) {
        setCursor(26, 12);
        for (j = 0; j < strlen(fraseAbertura[i]); j++)  {
            printf("%c", fraseAbertura[i][j]);
            Sleep(100);
        }
        Sleep(1000);
        system("cls");
    }
    for(i=0; i<HEIGHT; i++){
        for(j=0; j<WIDTH; j++){
            if(i == 0 || i == HEIGHT-1) printf("X");
            else if(j == 0 || j == WIDTH-1) printf("X");
            else printf (" ");
        }
    }
    setCursor(0, 0);
    while(posX < 80) // enquanto a tecla ESC nao for pressionada
    {

        setCursor(posX, posY); // altera a posicao do cursor para o da bola
        printf(""); // imprime um espaco sobre a bola
        // verifica colisoes
        if(posX+dirX == 0 || posX+dirX == WIDTH-3) dirX*=-2;
        if(posY+dirY == 0 || posY+dirY == HEIGHT-2) dirY*=-2;

        //movimenta a bola
        posX += dirX;
        posY += dirY;

        setCursor(posX, posY); //altera a posicao do cursor paraa nova posica da bola
        printf("ARTHOMAS"); //imprime a bola

        Sleep(1000/30); //30 frames por segundo
    }
    setCursor(posX, posY); // altera a posicao do cursor para o da bola
    printf(" "); // imprime um espaco sobre a bola
    setCursor(0, posY);
    desenhaLogo();
    for (i = 0; i < 10; i++) {
        printf("________________________________________________________________________________");
        Sleep(50);
    }
    Sleep(2000);
    system("color 04");
    setCursor(0, posY-24);
    for (i = 0; i < 28; i++) {
        for (j = 0; j < 80; j++) {
            printf("O");
        }
    }
    Sleep(1000);
    system("cls");
}

void desenhaLogo() {
    int i, j;
    char abertura[5][80] = {"         _      ____    _____   _   _    ___    __  __      _      ____",
                             "        / \\    |  _ \\  |_   _| | | | |  / _ \\  |  \\/  |    / \\    / ___|",
                             "       / _ \\   | |_) |   | |   | |_| | | | | | | |\\/| |   / _ \\   \\___ \\ ",
                             "      / ___ \\  |  _ <    | |   |  _  | | |_| | | |  | |  / ___ \\   ___) |",
                             "     /_/   \\_\\ |_| \\_\\   |_|   |_| |_|  \\___/  |_|  |_| /_/   \\_\\ |____/ "
                            };
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 80; j++) {
            printf("%c", abertura[i][j]);
            Sleep(2);
        }
    }
}


void gameOver() {
    int i, j, posX = 50, posY = 13;
    char menuFundo[5][80] = {"                  ___                         ___                               ",
                             "                 / _ \\__ _ _ __ ___   ___    /___\\__   _____ _ __               ",
                             "                / /_\\/ _` | '_ ` _ \\ / _ \\  //  //\\ \\ / / _ \\ '__|              ",
                             "               / /_\\\\ (_| | | | | | |  __/ / \\_//  \\ V /  __/ |                 ",
                             "               \\____/\\__,_|_| |_| |_|\\___| \\___/    \\_/ \\___|_|                 "};
    system("cls");
    setCursor(0, 5);
    system("color ff");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 80; j++) {
            printf("%c", menuFundo[i][j]);
            Sleep(2);
        }
    }
    Sleep(500);
}

void printaScore(int pontuacaoPlayer1, int pontuacaoPlayer2, int nivel, int linhas, int highscore) {
    setCursor(0, 0);
    mudaCor(15);
    printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", pontuacaoPlayer2, nivel);
    setCursor(0, linhas+1);
    printf("SCORE: %3d________________________________________________________HIGH_SCORE:_%2d", pontuacaoPlayer1, highscore);
    setCursor(0, 0);
}

void printaMapa(MAPA *mapa) {
    int i, j;
    for(i=0; i<mapa->linhas; i++){
        for(j=0; j<mapa->colunas; j++){
            //if(i == 0 || i == HEIGHT) printf("X");
            //if(j == 0 || j == mapa.colunas-1) printf("%c", mapa.borda);
            //else printf (" ");
            if(j == 0 || j  == mapa->colunas-1) {
                mudaCor(15);
                if(mapa->mapa[i][j] == 1) {
                    printf("%c", mapa->borda);
                }
                else {
                    mudaCor(15);
                    printf (" ");
                }
            }
            else {
                mudaCor(7);
                if(mapa->mapa[i][j] == 1) {
                    printf("%c", 219);
                }
                else {
                    mudaCor(15);
                    printf (" ");
                }
            }
        }
        if(mapa->colunas < 80) {
            printf("\n");
        }
    }
}
