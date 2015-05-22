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
