int movimentoPlayer1(PLAYER1 *player1, MAPA *mapa);
int movimentoPlayer2(PLAYER2 *player2, BOLA *bola, MAPA *mapa);

int movimentoPlayer1(PLAYER1 *player1, MAPA *mapa) {
        int i;
        char player[player1->tamanho+1], playerApaga[player1->tamanho+1];
        //Player 1
        mudaCor(9);
        for(i = 0; i <= player1->tamanho; i++) {
                    if(i == player1->tamanho) playerApaga[i] = '\0';
                    else playerApaga[i] = ' ';
            }
            setCursor(player1->posXPlayer1, player1->posYPlayer1); // altera a posicao do cursor para o da bola
            puts(playerApaga); // imprime um espaco sobre a bola
        // verifica colisoes

        //movimenta a bola
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
        mudaCor(9);
        strncpy(player, player1->raquete, player1->tamanho);
        player[player1->tamanho] = '\0';
        setCursor(player1->posXPlayer1, player1->posYPlayer1); //altera a posicao do cursor paraa nova posica da bola
        puts(player);
}

int movimentoPlayer2(PLAYER2 *player2, BOLA *bola, MAPA *mapa) {
        int i;
        char player[player2->tamanho+1], playerApaga[player2->tamanho+1];
        if(player2->multiplayer == 1) {
            //Player 2
            mudaCor(12);
            for(i = 0; i <= player2->tamanho; i++) {
                    if(i == player2->tamanho) playerApaga[i] = '\0';
                    else playerApaga[i] = ' ';
            }
            setCursor(player2->posXPlayer2, player2->posYPlayer2); // altera a posicao do cursor para o da bola
            puts(playerApaga); // imprime um espaco sobre a bola
            // verifica colisoes

            //movimenta a bola
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
            mudaCor(12);
            strncpy(player, player2->raquete, player2->tamanho);
            player[player2->tamanho] = '\0';
            setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
            puts(player);
        }
        else {
            //Player 2
            mudaCor(12);
            for(i = 0; i <= player2->tamanho; i++) {
                    if(i == player2->tamanho) playerApaga[i] = '\0';
                    else playerApaga[i] = ' ';
            }
            setCursor(player2->posXPlayer2, player2->posYPlayer2); // altera a posicao do cursor para o da bola
            puts(playerApaga); // imprime um espaco sobre a bola
            // verifica colisoes

            //movimenta a bola
            if(player2->posXPlayer2+5 > bola->posX[0] && player2->posXPlayer2 > 1) {
                player2->posXPlayer2--;
                for(i = 1; i < player2->dirX; i++) {
                    if(player2->posXPlayer2 > 1) {
                        player2->posXPlayer2--;
                    }
                }
                player2->velX = -1;
            }
            if(player2->posXPlayer2+5 < bola->posX[0] && player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                player2->posXPlayer2++;
                for(i = 1; i < player2->dirX; i++) {
                    if(player2->posXPlayer2 < mapa->colunas-(player2->tamanho+1)) {
                        player2->posXPlayer2++;
                    }
                }
                player2->velX = 1;
            }
            //for (i = 0; i < player2->tamanho; i++) {
            //    printf("="); //imprime a bola
            //}
            mudaCor(12);
            strncpy(player, player2->raquete, player2->tamanho);
            player[player2->tamanho] = '\0';
            setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
            puts(player);
        }
}
