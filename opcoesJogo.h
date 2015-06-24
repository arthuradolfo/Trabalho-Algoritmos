void onePlayer(int highscore, int replayConfirma);
void twoPlayer(int replayConfirma);
void brutalMode(int jogadores, int replayConfirma);


void onePlayer(int highscore, int replayConfirma) {
    //GetAsyncKeyState(VK_RETURN);
    //MAPA mapa = {25, 80 , 186, {0}};
    FILE *replay;
    FILE *high;

    //ve se conseguiu abrir o arquivo de replay
    //mas o jogo deve rodar mesmo se nao abrir
    if(replayConfirma == 1) {
            if((replay = fopen("replay", "wb")) == 0) {
                printf("Erro ao abrir arquivo replay!");
            }
    }

    //escolha aleatoria do mapa
    MAPA mapa;
    char qualMapa[30] = "maps";
    char idMapa[5];
    srand(time(NULL));
    itoa(rand()%5, idMapa, 10);
    strcat(qualMapa, idMapa);
    strcat(qualMapa, ".txt");
    carregaMapaOnePlayer(qualMapa, &mapa);

    //ve no arquivo nivel como eh o nivel 1
    //e passa suas caracteristicas pra estrutura st_nivel
    int nivel = 1;
    NIVEL st_nivel;
    FILE* arqNivel;
    arqNivel = fopen("arqNiv","rb");
    fseek(arqNivel,(nivel-1)*sizeof(NIVEL),SEEK_SET);
    fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
    fclose(arqNivel);

    //inicializacao das estruturas dos plays e da bola ja com as caracteristicas do nivel
    BOLA bola = {{mapa.colunas/2, 13, 30, 7, 7}, {mapa.linhas-1, 13, 20, 7, 7}, {st_nivel.velBola, st_nivel.velBola, st_nivel.velBola, st_nivel.velBola, st_nivel.velBola}, {-st_nivel.velBola, -st_nivel.velBola, -st_nivel.velBola, -st_nivel.velBola, -st_nivel.velBola}, 1, 166};
    PLAYER1 player1 = {mapa.colunas/2, mapa.linhas, st_nivel.tamPlayer1, st_nivel.velPlayer1, st_nivel.velPlayer1, 0, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {mapa.colunas/2, 1, st_nivel.tamPlayer2, st_nivel.velPlayer2, st_nivel.velPlayer2, 0, 0, st_nivel.IAPlayer2, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};

    int i, j, ponto = 0, ponto1 = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;

    system("cls");

    //printa o mapa anteriormente carregado aleatoriamente
    setCursor(0, 0);
    printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", pontuacaoPlayer2, nivel);
    printaMapa(&mapa);
    mudaCor(15);
    printf("SCORE: %3d________________________________________________________HIGH_SCORE:_%2d", pontuacaoPlayer1, highscore);
    setCursor(0,0);
    while(!GetAsyncKeyState(VK_ESCAPE)) // enquanto a tecla ESC nao for pressionada
    {
        //movimento dos dois players
        movimentoPlayer1(&player1, &bola, &mapa, 0);
        movimentoPlayer2(&player2, &bola, &mapa, 0);

        //movimento da bola
        ponto = movimentoBola(&bola, &player1, &player2, 0, 0, &mapa, 0, 0, 0);

        //abaixo devemos zerar estas variaveis
        player1.velX = 0;
        player2.velX = 0;

        //ponto 1 quer dizer ponto do player 1
        if (ponto == 1) {
            pontuacaoPlayer1++;

            //apaga a bola que saiu (marcou ponto)
            //bolafora indica o indice da bola que entrou na area de ponto
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");

            //esta bola deve ser inicializada em sua nova posicao
            bola.posX[bola.bolaFora] = player2.posXPlayer2+(player2.tamanho/2);
            bola.posY[bola.bolaFora] = player2.posYPlayer2+1;
            bola.dirY[bola.bolaFora] = st_nivel.velBola;

            //printamos o novo placar sem sobrepor o mapa
            printaScore(pontuacaoPlayer1, pontuacaoPlayer2, nivel, mapa.linhas, highscore);

            Sleep(200);

            //a segunda bola eh adicionada quando o player 1 faz dois pontos
            //a terceira bola e adicionada quando o player 2 faz tres pontos
            if(pontuacaoPlayer1%2 == 0 && pontuacaoPlayer1 != 0) {
                Beep(880, 500);
                bola.numBolas++;
            }

            //pontuacao player1 = 5 quer dizer dizer que o player 1 passou de nivel
            if(pontuacaoPlayer1 == 5) {
                //numero de bolas volta a ser 1
                bola.numBolas = 1;

                //aumenta o nivel e carrega suas caracteristicas na estrutura st_nivel
                nivel++;
                arqNivel = fopen("arqNiv","rb");
                fseek(arqNivel,(nivel-1)*sizeof(NIVEL),SEEK_SET);
                fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
                fclose(arqNivel);

                //atualiza as variaveis de acordo com o novo nivel
                player1.dirX = st_nivel.velPlayer1;
                player2.dirX = st_nivel.velPlayer2;
                player1.tamanho = st_nivel.tamPlayer1;
                player2.tamanho = st_nivel.tamPlayer2;
                player2.nivelIA = st_nivel.IAPlayer2;
                //atualiza a velocidade das bolas de acordo com o novo nivel
                bola.dirX[0] = st_nivel.velBola; bola.dirX[1] = st_nivel.velBola; bola.dirX[2] = st_nivel.velBola; bola.dirX[3] = st_nivel.velBola; bola.dirX[4] = st_nivel.velBola;
                bola.dirY[0] = st_nivel.velBola; bola.dirY[1] = st_nivel.velBola; bola.dirY[2] = st_nivel.velBola; bola.dirY[3] = st_nivel.velBola; bola.dirY[4] = st_nivel.velBola;

                //reseta as pontuacoes
                pontuacaoPlayer1 = 0;
                pontuacaoPlayer2 = 0;

                //carrega novo mapa de forma aleatoria
                srand(time(NULL));
                strcpy(qualMapa, "maps");
                itoa(rand()%5, idMapa, 10);
                strcat(qualMapa, idMapa);
                strcat(qualMapa, ".txt");
                carregaMapaOnePlayer(qualMapa, &mapa);

                //diferente mapas podem apresentar diferente numero de linhas, portanto atualizamos a posicao do player1
                player1.posYPlayer1 = mapa.linhas;

                system("cls");

                printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", pontuacaoPlayer2, nivel);
                printaMapa(&mapa);
                mudaCor(15);
                printf("SCORE: %3d________________________________________________________HIGH_SCORE:_%2d", pontuacaoPlayer1, highscore);
                //printaScore(pontuacaoPlayer1, pontuacaoPlayer2, nivel, mapa.linhas, highscore);

                Sleep(400);
            }
        }
        else if (ponto == 2) { //ponto do player 2
            pontuacaoPlayer2++;
            //apaga a bola do ponto
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");
            //atualiza  nova posicao da bola do ponto
            bola.posX[bola.bolaFora] = player1.posXPlayer1+(player1.tamanho/2);
            bola.posY[bola.bolaFora] = player1.posYPlayer1-1;
            bola.dirY[bola.bolaFora] = -st_nivel.velBola;

            printaScore(pontuacaoPlayer1, pontuacaoPlayer2, nivel, mapa.linhas, highscore);

            setCursor(0, 0);
            Sleep(200);

            if(pontuacaoPlayer2 == 5) {//significa que o player2 ganhou
                //abre o arquivo record.bin e o atualiza se o highscore atual for maior que o do record
                if(high = fopen("record.bin", "r+b")) {
                    if(highscore < nivel) {
                        fseek(high, 0, SEEK_SET);
                        fwrite(&nivel, sizeof(int), 1, high);
                        fclose(high);
                    }
                    fclose(high);
                }
                //roda o desenho de gameover
                gameOver();

                //acabou o jogo e vamos dar return, portanto salvamos a posicao atual no replay
                if(replayConfirma == 1) {
                    salvaReplay(atoi(idMapa), &player1, &player2, 0, 0, &bola, pontuacaoPlayer1, pontuacaoPlayer2, nivel, replay);
                    fclose(replay);
                }

                return 1;
            }
        }
        //a cada ciclo principal do jogo salvamos as informacoes necessarias ao replay no arquivo replay
        if(replayConfirma == 1) {
                salvaReplay(atoi(idMapa), &player1, &player2, 0, 0, &bola, pontuacaoPlayer1, pontuacaoPlayer2, nivel, replay);
        }

    setCursor(0, 0);
        Sleep(1000/20);
    }
    if(high = fopen("record.bin", "r+b")) {
        if(highscore < nivel) {
            fseek(high, 0, SEEK_SET);
            fwrite(&nivel, sizeof(int), 1, high);
            fclose(high);
        }
        fclose(high);
    }
    if(replayConfirma == 1) fclose(replay);
}

void twoPlayer(int replayConfirma) {
    //MAPA mapa = {25, 80 , 186, {0}};
    FILE *replay;
    //ve se conseguiu abrir o arquivo de replay
    //mas o jogo deve rodar mesmo se nao abrir
    if(replayConfirma == 1) {
            if((replay = fopen("replay", "wb")) == 0) {
                printf("Erro ao abrir arquivo replay!");
            }
    }
    MAPA mapa;
    char qualMapa[30];
    char idMapa[5];
    if(replayConfirma == 0) {
        fflush(stdin);
        clearBuff();
        system("cls");
        printf("Escolha o mapa:\n");
        scanf("%s",qualMapa);
        clearBuff();
    } else {
        strcpy(qualMapa, "maps");
        srand(time(NULL));
        itoa(rand()%5, idMapa, 10);
        strcat(qualMapa, idMapa);
        strcat(qualMapa, ".txt");
    }
    carregaMapaOnePlayer(qualMapa, &mapa);
    BOLA bola = {{mapa.colunas/2, 10, 30, 7, 7}, {mapa.linhas-1, 10, 20, 7, 7}, {1, 1, 1, 1, 1}, {-1, 1, -1, 1, 1}, 3, 219};
    PLAYER1 player1 = {mapa.colunas/2, mapa.linhas, 20, 4, 4, 0, 0,  {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {mapa.colunas/2, 1, 20, 4, 4, 0, 0, 0, 1, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    int i, j, ponto = 0, ponto1 = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0;
    system("cls");
    printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
    printaMapa(&mapa);
    mudaCor(15);
    printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
    //desenhaMapa();
    setCursor(0,0);

    while(!GetAsyncKeyState(VK_ESCAPE)) // enquanto a tecla ESC nao for pressionada
    {
        movimentoPlayer1(&player1, &bola, &mapa, 0);
        movimentoPlayer2(&player2, &bola, &mapa, 0);
        ponto = movimentoBola(&bola, &player1, &player2, 0, 0, &mapa, 0, 0, 0);
        player1.velX = 0;
        player2.velX = 0;
        if (ponto == 1) {
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");
            bola.posX[bola.bolaFora] = player2.posXPlayer2+(player2.tamanho/2);
            bola.posY[bola.bolaFora] = player2.posYPlayer2+1;
            bola.dirY[bola.bolaFora] = 1;
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
            bola.dirY[bola.bolaFora] = -1;
            pontuacaoPlayer2++;
            setCursor(0, 0);
            mudaCor(15);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas+1);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            //Sleep(200);
        }
        //a cada ciclo principal do jogo salvamos as informacoes necessarias ao replay no arquivo replay
        if(replayConfirma == 1) {
                salvaReplay(atoi(idMapa), &player1, &player2, 0, 0, &bola, pontuacaoPlayer1, pontuacaoPlayer2, -1, replay);
        }
        Sleep(1000/30); //30 frames por segundo
    }
    if(replayConfirma == 1) fclose(replay);
}

void brutalMode(int jogadores, int replayConfirma) {
    //MAPA mapa = {25, 80 , 186, {0}};
    FILE *replay;
    //ve se conseguiu abrir o arquivo de replay
    //mas o jogo deve rodar mesmo se nao abrir
    if(replayConfirma == 1) {
            if((replay = fopen("replay", "wb")) == 0) {
                printf("Erro ao abrir arquivo replay!");
            }
    }
    MAPA mapa;
    char qualMapa[30];
    char idMapa[5];
    if(replayConfirma == 0) {
        fflush(stdin);
        clearBuff();
        system("cls");
        printf("Escolha o mapa:\n");
        scanf("%s",qualMapa);
        clearBuff();
    } else {
        strcpy(qualMapa, "maps0.txt");
    }
    carregaMapaOnePlayer(qualMapa, &mapa);
    BOLA bola = {{mapa.colunas/2, 10, 30, 7, 7}, {mapa.linhas-1, 10, 20, 7, 7}, {1, 1, 1, 1, 1}, {-1, 1, -1, 1, 1}, 1, 219};
    PLAYER1 player1 = {3*mapa.colunas/4, mapa.linhas, 20, 2, 1, 0, 0,  {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {mapa.colunas/4, 1, 20, 2, 1, 0, 0, 0, 1, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER1 player3 = {mapa.colunas/4, mapa.linhas-6, 20, 2, 1, 0, 0,  {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player4 = {3*mapa.colunas/2, 6, 20, 2, 1, 0, 0, 0, 1, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    int i, j, ponto = 0, ponto1 = 0, pontuacaoPlayer2 = 0, pontuacaoPlayer1 = 0, colidiuPlayer1 = 0, colidiuPlayer2 = 0;
    system("cls");
    printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
    for(i=0; i<mapa.linhas; i++){
        for(j=0; j<mapa.colunas; j++){
            //if(i == 0 || i == HEIGHT) printf("X");
            //if(j == 0 || j == mapa.colunas-1) printf("%c", mapa.borda);
            //else printf (" ");

            if((i == mapa.linhas/2 && j > 0) && (i == mapa.linhas/2 && j < mapa.colunas-1)) {
                printf("-");
            }
            else {
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
        movimentoPlayer1(&player1, &bola, &mapa, 1);
        movimentoPlayer2(&player2, &bola, &mapa, 1);
        if(jogadores == 2) {
            ponto = movimentoBola(&bola, &player1, &player2, 0, 0, &mapa, 1, &colidiuPlayer1, &colidiuPlayer2);
        }
        else if(jogadores == 3) {
            movimentoPlayer3(&player3, &bola, &mapa, 1);
            ponto = movimentoBola(&bola, &player1, &player2, &player3, 0, &mapa, 1, &colidiuPlayer1, &colidiuPlayer2);
        }
        else if(jogadores == 4) {
            movimentoPlayer3(&player3, &bola, &mapa, 1);
            movimentoPlayer4(&player4, &bola, &mapa, 1);
            ponto = movimentoBola(&bola, &player1, &player2, &player3, &player4, &mapa, 1, &colidiuPlayer1, &colidiuPlayer2);
        }
        else {
           ponto = movimentoBola(&bola, &player1, &player2, 0, 0, &mapa, 1, &colidiuPlayer1, &colidiuPlayer2);
        }
        player1.velX = 0;
        player2.velX = 0;
        if (ponto == 1) {
            setCursor(bola.posX[bola.bolaFora], bola.posY[bola.bolaFora]);
            printf(" ");
            bola.posX[bola.bolaFora] = player2.posXPlayer2+(player2.tamanho/2);
            bola.posY[bola.bolaFora] = player2.posYPlayer2+1;
            bola.dirY[bola.bolaFora] = 1;
            colidiuPlayer2 = 1;
            colidiuPlayer1 = 0;
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
            bola.dirY[bola.bolaFora] = -1;
            pontuacaoPlayer2++;
            colidiuPlayer2 = 0;
            colidiuPlayer1 = 1;
            setCursor(0, 0);
            mudaCor(15);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer2);
            setCursor(0, mapa.linhas+1);
            printf("SCORE: %3d______________________________________________________________________", pontuacaoPlayer1);
            setCursor(0, 0);
            //Sleep(200);
        }
        //a cada ciclo principal do jogo salvamos as informacoes necessarias ao replay no arquivo replay
        if(replayConfirma == 1) {
                if(jogadores == 2) salvaReplay(atoi(idMapa), &player1, &player2, 0, 0, &bola, pontuacaoPlayer1, pontuacaoPlayer2, -2, replay);
                if(jogadores == 3) salvaReplay(atoi(idMapa), &player1, &player2, &player3, 0, &bola, pontuacaoPlayer1, pontuacaoPlayer2, -2, replay);
                if(jogadores == 4) salvaReplay(atoi(idMapa), &player1, &player2, &player3, &player4, &bola, pontuacaoPlayer1, pontuacaoPlayer2, -2, replay);
        }
        Sleep(1000/30); //30 frames por segundo
    }
    if(replayConfirma == 1) fclose(replay);
}
