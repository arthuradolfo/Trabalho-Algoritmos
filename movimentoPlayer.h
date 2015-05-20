int movimentoPlayer1(PLAYER1 *player1);
int movimentoPlayer2(PLAYER2 *player2, BOLA *bola);

int movimentoPlayer1(PLAYER1 *player1) {
        int i;
        char player[player1->tamanho+1];
        //Player 1
        setCursor(player1->posXPlayer1, player1->posYPlayer1); // altera a posicao do cursor para o da bola
        printf("          "); // imprime um espaco sobre a bola
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
        if(GetAsyncKeyState(VK_RIGHT) && player1->posXPlayer1 < WIDTH-(player1->tamanho+1)) {
                player1->posXPlayer1++;
                for(i = 1; i < player1->dirX; i++) {
                    if(player1->posXPlayer1 < WIDTH-(player1->tamanho+1)) {
                        player1->posXPlayer1++;
                    }
                }
                player1->velX = 1;
        }

        setCursor(player1->posXPlayer1, player1->posYPlayer1); //altera a posicao do cursor paraa nova posica da bola
        strncpy(player, player1->raquete, player1->tamanho);
        player[player1->tamanho] = '\0';
        puts(player);
}

int movimentoPlayer2(PLAYER2 *player2, BOLA *bola) {
        int i;
        char player[player2->tamanho+1];
        if(player2->multiplayer == 1) {
            //Player 2
            setCursor(player2->posXPlayer2, player2->posYPlayer2); // altera a posicao do cursor para o da bola
            printf("          "); // imprime um espaco sobre a bola
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
            if(GetAsyncKeyState(0x44) && player2->posXPlayer2 < WIDTH-(player2->tamanho+1)) {
                player2->posXPlayer2++;
                for(i = 1; i < player2->dirX; i++) {
                    if(player2->posXPlayer2 < WIDTH-(player2->tamanho+1)) {
                        player2->posXPlayer2++;
                    }
                }
                player2->velX = 1;
            }

            setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
            for (i = 0; i < player2->tamanho; i++) {
                printf("="); //imprime a bola
            }
        }
        else {
            //Player 2
            setCursor(player2->posXPlayer2, player2->posYPlayer2); // altera a posicao do cursor para o da bola
            printf("          "); // imprime um espaco sobre a bola
            // verifica colisoes

            //movimenta a bola
            if(player2->posXPlayer2+5 > bola->posX && player2->posXPlayer2 > 1) {
                player2->posXPlayer2--;
                for(i = 1; i < player2->dirX; i++) {
                    if(player2->posXPlayer2 > 1) {
                        player2->posXPlayer2--;
                    }
                }
                player2->velX = -1;
            }
            if(player2->posXPlayer2+5 < bola->posX && player2->posXPlayer2 < WIDTH-(player2->tamanho+1)) {
                player2->posXPlayer2++;
                for(i = 1; i < player2->dirX; i++) {
                    if(player2->posXPlayer2 < WIDTH-(player2->tamanho+1)) {
                        player2->posXPlayer2++;
                    }
                }
                player2->velX = 1;
            }

            setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
            //for (i = 0; i < player2->tamanho; i++) {
            //    printf("="); //imprime a bola
            //}
            strncpy(player, player2->raquete, player2->tamanho);
            player[player2->tamanho] = '\0';
            puts(player);
        }
}
