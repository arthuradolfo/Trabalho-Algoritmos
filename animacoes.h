void setCursor(int x, int y);
void abertura();
void desenhaLogo();

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