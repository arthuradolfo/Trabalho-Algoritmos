//menus do jogo
//todos funcionam de forma semelhante
//o usuario pode ir para cima e para baixo, e, no fim, a funcao retorna o indice da opcao escolhida

int menu (highscore) {
    int i, cheat = 0, posX = 50, posY = 13;
    char menuFundo[10][80] = {"                                   MENU                                ",
                                  "                      ________________________________                 ",
                                  "                     |                                |                ",
                                  "                     |   1 player:                    |                ",
                                  "                     |   2 player:                    |                ",
                                  "                     |   Criar mapa:                  |                ",
                                  "                     |   Modo Brutal:                |                ",
                                  "                     |   Replay do ultimo jogo:       |                ",
                                  "                     |   Sair:                        |                ",
                                  "                     |________________________________|                "
                            };
    setCursor(0, 0);
    desenhaLogo();
    system("color ff");
    for (i = 0; i < 5; i++) {
        printf("\n");
        Sleep(150);
    }
    for (i = 0; i < 10; i++) {
        printf("%s\n", menuFundo[i]);
        Sleep(150);
    }
    printf("                     HIGH SCORE: %4d                                  ", highscore);
    for (i = 0; i < 4; i++) {
        printf("\n");
        Sleep(150);
    }
    while(!GetAsyncKeyState(VK_RETURN)) {
        setCursor(posX, posY);
        printf("<-");
        if(GetAsyncKeyState(VK_DOWN) && posY < 17) {
            setCursor(posX, posY);
            printf("  ");
            posY++;
            Sleep(300);
        }
        if (GetAsyncKeyState(VK_UP) && posY > 13) {
            setCursor(posX, posY);
            printf("  ");
            posY--;
            Sleep(300);

        }
        if (GetAsyncKeyState(VK_LEFT)) {
            cheat+=3;// eater egg
            Sleep(300);
        }

        if (GetAsyncKeyState(VK_RIGHT)) {
            cheat+=7;// eater egg
            Sleep(300);
        }
        if(cheat == 13) {// eater egg
            MAPA mapa;
            carregaMapaOnePlayer("memapa", &mapa);
            setCursor(0, 0);
            printaMapa(&mapa);
            setCursor(0, 0);
            Sleep(2000);
            return 6;
        }
        if(cheat == 17) { // eater egg
            MAPA mapa;
            carregaMapaOnePlayer("memapa1", &mapa);
            setCursor(0, 0);
            printaMapa(&mapa);
            setCursor(0, 0);
            Sleep(2000);
            return 6;
        }
        Sleep(1000/30);
    }
    return posY-12;
}


int menuBrutal() {
    int i, posX = 50, posY = 13;
    char menuFundo[8][80] = {     "       Brutal Mode: anda tambem para cima e para baixo (UP & DOWN)     ",
                                  "                      ________________________________                 ",
                                  "                     |                 teclas:        |                ",
                                  "                     |   2 player:    (W-A-S-D)       |                ",
                                  "                     |   3 player:    (I-J-K-L)       |                ",
                                  "                     |   4 player:    (T-F-G-H)       |                ",
                                  "                     |________________________________|                ",
                                  "                                                                       "
                            };
    system("cls");
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
    for (i = 0; i < 4; i++) {
        printf("\n");
        Sleep(150);
    }
    while(!GetAsyncKeyState(VK_RETURN)) {
        setCursor(posX, posY);
        printf("<-");
        if(GetAsyncKeyState(VK_DOWN) && posY < 15) {
            setCursor(posX, posY);
            printf("  ");
            posY++;
            Sleep(300);
        }
        if (GetAsyncKeyState(VK_UP) && posY > 13) {
            setCursor(posX, posY);
            printf("  ");
            posY--;
            Sleep(300);

        }
        Sleep(1000/30);
    }
    return posY-11;
}

int menuReplay() {
    int i, posX = 50, posY = 13;
    char menuFundo[6][80] = {     "                     Deseja salvar o replay desse jogo?                ",
                                  "                        Sobrescrevera o antigo replay                  ",
                                  "                      ________________________________                 ",
                                  "                     |   NAO:                         |                ",
                                  "                     |   SIM:                         |                ",
                                  "                     |________________________________|                "
                            };
    system("cls");
    setCursor(0, 0);
    desenhaLogo();
    system("color ff");
    for (i = 0; i < 5; i++) {
        printf("\n");
        Sleep(150);
    }
    for (i = 0; i < 6; i++) {
        printf("%s\n", menuFundo[i]);
        Sleep(150);
    }
    for (i = 0; i < 4; i++) {
        printf("\n");
        Sleep(150);
    }
    while(!GetAsyncKeyState(VK_RETURN)) {
        setCursor(posX, posY);
        printf("<-");
        if(GetAsyncKeyState(VK_DOWN) && posY < 14) {
            setCursor(posX, posY);
            printf("  ");
            posY++;
            Sleep(300);
        }
        if (GetAsyncKeyState(VK_UP) && posY > 13) {
            setCursor(posX, posY);
            printf("  ");
            posY--;
            Sleep(300);

        }
        Sleep(1000/30);
    }
    return posY-13;
}
