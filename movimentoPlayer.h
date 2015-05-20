int movimentoPlayer1(PLAYER1 *player1);
int movimentoPlayer2(PLAYER2 *player2, BOLA *bola);

int movimentoPlayer1(PLAYER1 *player1) {
        int i;
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
        if(GetAsyncKeyState(VK_RIGHT) && player1->posXPlayer1 < WIDTH-11) {
                player1->posXPlayer1++;
                for(i = 1; i < player1->dirX; i++) {
                    if(player1->posXPlayer1 < WIDTH-11) {
                        player1->posXPlayer1++;
                    }
                }
                player1->velX = 1;
        }

        setCursor(player1->posXPlayer1, player1->posYPlayer1); //altera a posicao do cursor paraa nova posica da bola
        printf("!========!"); //imprime a bola
}

int movimentoPlayer2(PLAYER2 *player2, BOLA *bola) {
        int i;
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
            if(GetAsyncKeyState(0x44) && player2->posXPlayer2 < WIDTH-11) {
                player2->posXPlayer2++;
                for(i = 1; i < player2->dirX; i++) {
                    if(player2->posXPlayer2 < WIDTH-11) {
                        player2->posXPlayer2++;
                    }
                }
                player2->velX = 1;
            }

            setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
            printf("!========!"); //imprime a bola
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
            if(player2->posXPlayer2+5 < bola->posX && player2->posXPlayer2 < WIDTH-11) {
                player2->posXPlayer2++;
                for(i = 1; i < player2->dirX; i++) {
                    if(player2->posXPlayer2 < WIDTH-11) {
                        player2->posXPlayer2++;
                    }
                }
                player2->velX = 1;
            }

            setCursor(player2->posXPlayer2, player2->posYPlayer2); //altera a posicao do cursor paraa nova posica da bola
            printf("!========!"); //imprime a bola
        }
}
