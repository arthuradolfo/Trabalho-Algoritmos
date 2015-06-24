int movimentoPlayer1(PLAYER1 *player1, BOLA *bola, MAPA *mapa, int brutal);
int movimentoPlayer2(PLAYER2 *player2, BOLA *bola, MAPA *mapa, int brutal);

int movimentoPlayer1(PLAYER1 *player1, BOLA *bola, MAPA *mapa, int brutal) {
        int i;
        //para printar todo oplayer de uma vez e nao caracter por caracter
        char player[player1->tamanho+1], playerApaga[player1->tamanho+1];

        mudaCor(9);
        //fazer a string que apaga o player
        for(i = 0; i <= player1->tamanho; i++) {
                if(i == player1->tamanho) playerApaga[i] = '\0';
                else playerApaga[i] = ' ';
        }
        //para nao apagar a barreira se o tamanho (junto de sua posicao) for sobrepor a barriera
        if(player1->posXPlayer1+player1->tamanho > mapa->colunas-1) {
                player1->posXPlayer1 = mapa->colunas-1-player1->tamanho;
        }

        //apaga o player pois ele mudara sua posicao (ou nao)
        setCursor(player1->posXPlayer1, player1->posYPlayer1);
        puts(playerApaga);


        if(brutal == 0) { //se nao estiver no modo brutal

            //movimenta para a esquerda
            if(GetAsyncKeyState(VK_LEFT) && player1->posXPlayer1 > 1) {
                    player1->posXPlayer1--;
                    //dirX marca quantas posicoes o player deve andar (como um marcador do valor absoluto da velocidade)
                    //entao andamos quantas forem necessarias
                    for(i = 1; i < player1->dirX; i++) {
                        if(player1->posXPlayer1 > 1) {
                            player1->posXPlayer1--;
                        }
                    }
                    //marca que o player esta se movendo para a esquerda
                    player1->velX = -1;
            }

            //movimenta para a direita
            //de forma analoga a movimentar para a esquerda
            if(GetAsyncKeyState(VK_RIGHT) && player1->posXPlayer1 < mapa->colunas-(player1->tamanho+1)) {
                    player1->posXPlayer1++;
                    for(i = 1; i < player1->dirX; i++) {
                        if(player1->posXPlayer1 < mapa->colunas-(player1->tamanho+1)) {
                            player1->posXPlayer1++;
                        }
                    }
                    player1->velX = 1;
            }
        }
        else { //eh brutal mode
            if(GetAsyncKeyState(VK_UP) && player1->posYPlayer1 > (mapa->linhas/2)+2) {
                    player1->posYPlayer1--;
                    for(i = 1; i < player1->dirY; i++) {
                        if(player1->posYPlayer1 > (mapa->linhas/2)+2) {
                            player1->posYPlayer1--;
                            //for(j = 0; j < 5; j++) {
                             //       colisaoPlayer1(bola, player1, mapa, j);
                            //}
                        }
                    }
            }
            if(GetAsyncKeyState(VK_DOWN) && player1->posYPlayer1 < mapa->linhas) {
                    player1->posYPlayer1++;
                    for(i = 1; i < player1->dirY; i++) {
                        if(player1->posYPlayer1 < mapa->linhas) {
                            player1->posYPlayer1++;
                            //for(j = 0; j < 5; j++) {
                            //        colisaoPlayer1(bola, player1, mapa, j);
                           // }
                        }
                    }
            }
            if(GetAsyncKeyState(VK_LEFT) && player1->posXPlayer1 > 1) {
                    player1->posXPlayer1--;
                    for(i = 1; i < player1->dirX; i++) {
                        if(player1->posXPlayer1 > 1) {
                            player1->posXPlayer1--;
                        }
                    }
                    player1->velX = -1;
            }
            if(GetAsyncKeyState(VK_RIGHT) && player1->posXPlayer1 < mapa->colunas-(player1->tamanho+1)) {
                    player1->posXPlayer1++;
                    for(i = 1; i < player1->dirX; i++) {
                        if(player1->posXPlayer1 < mapa->colunas-(player1->tamanho+1)) {
                            player1->posXPlayer1++;
                        }
                    }
                    player1->velX = 1;
            }
            //for(j = 0; j < 5; j++) {
            //    colisaoPlayer1(bola, player1, mapa, j);
            //}
        }

        mudaCor(9);
        //string player tem todos os caracteres do player e o tamanho do player
        strncpy(player, player1->raquete, player1->tamanho);
        player[player1->tamanho] = '\0';

        //para nao sobrepor o mapa
        if(player1->posXPlayer1+player1->tamanho > mapa->colunas-1) {
                player1->posXPlayer1 = mapa->colunas-1-player1->tamanho;
        }

        //printa o player na sua nova posicao
        setCursor(player1->posXPlayer1, player1->posYPlayer1); //altera a posicao do cursor paraa nova posica da bola
        puts(player);
}

int movimentoPlayer2(PLAYER2 *player2, BOLA *bola, MAPA *mapa, int brutal) {
        int i;

        //usaremos para printar como string nao caracter por caracter
        char player[player2->tamanho+1], playerApaga[player2->tamanho+1];

        if(player2->multiplayer == 1) { // dois jogadores humanos

            mudaCor(12);
            //faz a string que apagara o player 2
            for(i = 0; i <= player2->tamanho; i++) {
                    if(i == player2->tamanho) playerApaga[i] = '\0';
                    else playerApaga[i] = ' ';
            }

            //para nao sobrepor a barreira do mapa
            if(player2->posXPlayer2+player2->tamanho > mapa->colunas-1) {
                    player2->posXPlayer2 = mapa->colunas-1-player2->tamanho;
            }

            //apaga o player para ele assumir a nova posicao
            setCursor(player2->posXPlayer2, player2->posYPlayer2);
            puts(playerApaga);

            if(brutal == 0) {//nao eh modo brutal
                //funciona da forma analoga ao movimento do player1
                if(GetAsyncKeyState(0x41) && player2->posXPlayer2 > 1) {
                    player2->posXPlayer2--;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 > 1) {
                            player2->posXPlayer2--;
                        }
                    }
                    player2->velX = -1;
                }
                if(GetAsyncKeyState(0x44) && player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                    player2->posXPlayer2++;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                            player2->posXPlayer2++;
                        }
                    }
                    player2->velX = 1;
                }
            }
            else { //modo brutal
                if(GetAsyncKeyState(0x57) && player2->posYPlayer2 > 1) {
                        player2->posYPlayer2--;
                        for(i = 1; i < player2->dirY; i++) {
                            if(player2->posYPlayer2 > 2) {
                                player2->posYPlayer2--;
                                //for(j = 0; j < 5; j++) {
                                        //colisaoPlayer2(bola, player2, mapa, j);
                                //}
                            }
                        }
                }
                if(GetAsyncKeyState(0x53) && player2->posYPlayer2 < (mapa->linhas/2)) {
                        player2->posYPlayer2++;
                        for(i = 1; i < player2->dirY; i++) {
                            if(player2->posYPlayer2 < (mapa->linhas/2)) {
                                player2->posYPlayer2++;
                                //for(j = 0; j < 5; j++) {
                                //        colisaoPlayer2(bola, player2, mapa, j);
                                //}
                            }
                        }
                }
                if(GetAsyncKeyState(0x41) && player2->posXPlayer2 > 1) {
                    player2->posXPlayer2--;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 > 1) {
                            player2->posXPlayer2--;
                        }
                    }
                    player2->velX = -1;
                }
                if(GetAsyncKeyState(0x44) && player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                    player2->posXPlayer2++;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                            player2->posXPlayer2++;
                        }
                    }
                    player2->velX = 1;
                }

                //for(j = 0; j < 5; j++) {
                //    colisaoPlayer2(bola, player2, mapa, j);
                //}
            }

            mudaCor(12);
            //string que imprimirah o player 2
            //de forma analoga ao que acontece no movimento do player1
            strncpy(player, player2->raquete, player2->tamanho);
            player[player2->tamanho] = '\0';

            //nao sobrepoe a barreira do mapa
            if(player2->posXPlayer2+player2->tamanho > mapa->colunas-1) {
                    player2->posXPlayer2 = mapa->colunas-1-player2->tamanho;
            }

            //imprime o player 2 na sua nova posicao
            setCursor(player2->posXPlayer2, player2->posYPlayer2);
            puts(player);
        }
        else { //o player dois eh o computador
            mudaCor(12);
            //faz a string que desenha o player 2
            strncpy(player, player2->raquete, player2->tamanho);
            player[player2->tamanho] = '\0';
            //desenha o player2
            setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
            puts(player);

            //o computador se movimenta apenas algumas vezes, dependendo do nivel
            srand(time(NULL));
            if(rand()%player2->nivelIA != 1){
                //Player 2
                mudaCor(12);
                //faz a string que apaga o player
                for(i = 0; i <= player2->tamanho; i++) {
                        if(i == player2->tamanho) playerApaga[i] = '\0';
                        else playerApaga[i] = ' ';
                }

                if(player2->posXPlayer2+player2->tamanho > mapa->colunas-1) {
                    player2->posXPlayer2 = mapa->colunas-1-player2->tamanho;
                }

                //apaga o player2
                setCursor(player2->posXPlayer2, player2->posYPlayer2);
                puts(playerApaga);

                //o player 2 acompanha o posicao em x da bola
                if(player2->posXPlayer2 + player2->tamanho/2 > bola->posX[0] && player2->posXPlayer2 > 1) {
                    player2->posXPlayer2--;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 > 1) {
                            player2->posXPlayer2--;
                        }
                    }
                    player2->velX = -1;
                }
                if(player2->posXPlayer2+player2->tamanho/2 < bola->posX[0] && player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                    player2->posXPlayer2++;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                            player2->posXPlayer2++;
                        }
                    }
                    player2->velX = 1;
                }

                mudaCor(12);
                //string que imprime o player2
                strncpy(player, player2->raquete, player2->tamanho);
                player[player2->tamanho] = '\0';

                //para nao sobrepor as barreiras
                if(player2->posXPlayer2+player2->tamanho > mapa->colunas-1) {
                        player2->posXPlayer2 = mapa->colunas-1-player2->tamanho;
                }

                //imprime o player 2
                setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
                puts(player);
            }
        }
}

int movimentoPlayer3(PLAYER1 *player1, BOLA *bola, MAPA *mapa, int brutal) {
        int i;
        //para printar todo oplayer de uma vez e nao caracter por caracter
        char player[player1->tamanho+1], playerApaga[player1->tamanho+1];

        mudaCor(9);
        //fazer a string que apaga o player
        for(i = 0; i <= player1->tamanho; i++) {
                if(i == player1->tamanho) playerApaga[i] = '\0';
                else playerApaga[i] = ' ';
        }
        //para nao apagar a barreira se o tamanho (junto de sua posicao) for sobrepor a barriera
        if(player1->posXPlayer1+player1->tamanho > mapa->colunas-1) {
                player1->posXPlayer1 = mapa->colunas-1-player1->tamanho;
        }

        //apaga o player pois ele mudara sua posicao (ou nao)
        setCursor(player1->posXPlayer1, player1->posYPlayer1);
        puts(playerApaga);

            if(GetAsyncKeyState(0x49) && player1->posYPlayer1 > (mapa->linhas/2)+2) {
                    player1->posYPlayer1--;
                    for(i = 1; i < player1->dirY; i++) {
                        if(player1->posYPlayer1 > (mapa->linhas/2)+2) {
                            player1->posYPlayer1--;
                            //for(j = 0; j < 5; j++) {
                             //       colisaoPlayer1(bola, player1, mapa, j);
                            //}
                        }
                    }
            }
            if(GetAsyncKeyState(0x4B) && player1->posYPlayer1 < mapa->linhas) {
                    player1->posYPlayer1++;
                    for(i = 1; i < player1->dirY; i++) {
                        if(player1->posYPlayer1 < mapa->linhas) {
                            player1->posYPlayer1++;
                            //for(j = 0; j < 5; j++) {
                            //        colisaoPlayer1(bola, player1, mapa, j);
                           // }
                        }
                    }
            }
            if(GetAsyncKeyState(0x4A) && player1->posXPlayer1 > 1) {
                    player1->posXPlayer1--;
                    for(i = 1; i < player1->dirX; i++) {
                        if(player1->posXPlayer1 > 1) {
                            player1->posXPlayer1--;
                        }
                    }
                    player1->velX = -1;
            }
            if(GetAsyncKeyState(0x4C) && player1->posXPlayer1 < mapa->colunas-(player1->tamanho+1)) {
                    player1->posXPlayer1++;
                    for(i = 1; i < player1->dirX; i++) {
                        if(player1->posXPlayer1 < mapa->colunas-(player1->tamanho+1)) {
                            player1->posXPlayer1++;
                        }
                    }
                    player1->velX = 1;
            }

        mudaCor(9);
        //string player tem todos os caracteres do player e o tamanho do player
        strncpy(player, player1->raquete, player1->tamanho);
        player[player1->tamanho] = '\0';

        //para nao sobrepor o mapa
        if(player1->posXPlayer1+player1->tamanho > mapa->colunas-1) {
                player1->posXPlayer1 = mapa->colunas-1-player1->tamanho;
        }

        //printa o player na sua nova posicao
        setCursor(player1->posXPlayer1, player1->posYPlayer1); //altera a posicao do cursor paraa nova posica da bola
        puts(player);
}

int movimentoPlayer4(PLAYER2 *player2, BOLA *bola, MAPA *mapa, int brutal) {
        int i;

        //usaremos para printar como string nao caracter por caracter
        char player[player2->tamanho+1], playerApaga[player2->tamanho+1];

        if(player2->multiplayer == 1) { // dois jogadores humanos

            mudaCor(12);
            //faz a string que apagara o player 2
            for(i = 0; i <= player2->tamanho; i++) {
                    if(i == player2->tamanho) playerApaga[i] = '\0';
                    else playerApaga[i] = ' ';
            }

            //para nao sobrepor a barreira do mapa
            if(player2->posXPlayer2+player2->tamanho > mapa->colunas-1) {
                    player2->posXPlayer2 = mapa->colunas-1-player2->tamanho;
            }

            //apaga o player para ele assumir a nova posicao
            setCursor(player2->posXPlayer2, player2->posYPlayer2);
            puts(playerApaga);

            if(GetAsyncKeyState(0x54) && player2->posYPlayer2 > 1) {
                        player2->posYPlayer2--;
                        for(i = 1; i < player2->dirY; i++) {
                            if(player2->posYPlayer2 > 2) {
                                player2->posYPlayer2--;
                                //for(j = 0; j < 5; j++) {
                                        //colisaoPlayer2(bola, player2, mapa, j);
                                //}
                            }
                        }
                }
                if(GetAsyncKeyState(0x47) && player2->posYPlayer2 < (mapa->linhas/2)) {
                        player2->posYPlayer2++;
                        for(i = 1; i < player2->dirY; i++) {
                            if(player2->posYPlayer2 < (mapa->linhas/2)) {
                                player2->posYPlayer2++;
                                //for(j = 0; j < 5; j++) {
                                //        colisaoPlayer2(bola, player2, mapa, j);
                                //}
                            }
                        }
                }
                if(GetAsyncKeyState(0x46) && player2->posXPlayer2 > 1) {
                    player2->posXPlayer2--;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 > 1) {
                            player2->posXPlayer2--;
                        }
                    }
                    player2->velX = -1;
                }
                if(GetAsyncKeyState(0x48) && player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                    player2->posXPlayer2++;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                            player2->posXPlayer2++;
                        }
                    }
                    player2->velX = 1;
                }
            mudaCor(12);
            //string que imprimirah o player 2
            //de forma analoga ao que acontece no movimento do player1
            strncpy(player, player2->raquete, player2->tamanho);
            player[player2->tamanho] = '\0';

            //nao sobrepoe a barreira do mapa
            if(player2->posXPlayer2+player2->tamanho > mapa->colunas-1) {
                    player2->posXPlayer2 = mapa->colunas-1-player2->tamanho;
            }

            //imprime o player 2 na sua nova posicao
            setCursor(player2->posXPlayer2, player2->posYPlayer2);
            puts(player);
        }
        else { //o player dois eh o computador
            mudaCor(12);
            //faz a string que desenha o player 2
            strncpy(player, player2->raquete, player2->tamanho);
            player[player2->tamanho] = '\0';
            //desenha o player2
            setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
            puts(player);

            //o computador se movimenta apenas algumas vezes, dependendo do nivel
            srand(time(NULL));
            if(rand()%player2->nivelIA != 1){
                //Player 2
                mudaCor(12);
                //faz a string que apaga o player
                for(i = 0; i <= player2->tamanho; i++) {
                        if(i == player2->tamanho) playerApaga[i] = '\0';
                        else playerApaga[i] = ' ';
                }

                if(player2->posXPlayer2+player2->tamanho > mapa->colunas-1) {
                    player2->posXPlayer2 = mapa->colunas-1-player2->tamanho;
                }

                //apaga o player2
                setCursor(player2->posXPlayer2, player2->posYPlayer2);
                puts(playerApaga);

                //o player 2 acompanha o posicao em x da bola
                if(player2->posXPlayer2 + player2->tamanho/2 > bola->posX[0] && player2->posXPlayer2 > 1) {
                    player2->posXPlayer2--;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 > 1) {
                            player2->posXPlayer2--;
                        }
                    }
                    player2->velX = -1;
                }
                if(player2->posXPlayer2+player2->tamanho/2 < bola->posX[0] && player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                    player2->posXPlayer2++;
                    for(i = 1; i < player2->dirX; i++) {
                        if(player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                            player2->posXPlayer2++;
                        }
                    }
                    player2->velX = 1;
                }

                mudaCor(12);
                //string que imprime o player2
                strncpy(player, player2->raquete, player2->tamanho);
                player[player2->tamanho] = '\0';

                //para nao sobrepor as barreiras
                if(player2->posXPlayer2+player2->tamanho > mapa->colunas-1) {
                        player2->posXPlayer2 = mapa->colunas-1-player2->tamanho;
                }

                //imprime o player 2
                setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
                puts(player);
            }
        }
}
