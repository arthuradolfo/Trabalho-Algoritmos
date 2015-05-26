int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa);
void colisaoBorda(BOLA *bola, MAPA *mapa, int i);
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa, int i);
void colisaoObstaculo(BOLA *bola, MAPA *mapa, int i);

int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa) {
        int i, j;
        for (i = 0; i < bola->numBolas; i++) {
            //bola
            setCursor(bola->posX[i], bola->posY[i]); // altera a posicao do cursor para o da bola
            printf(" "); // imprime um espaco sobre a bola
            // verifica colisoes
                    //movimenta a bola
            for(j = 0; j < abs(bola->dirY[i]); j++) {
                if(bola->posY[i] < mapa->linhas && bola->posY[i] > 0) {
                    bola->posY[i]+=bola->dirY[i]/abs(bola->dirY[i]);
                }
            }
            for(j = 0; j < abs(bola->dirX[i]); j++) {
                if(bola->posX[i] <= mapa->colunas-2 && bola->posX[i] >= 2) {
                    bola->posX[i]+=bola->dirX[i]/abs(bola->dirX[i]);
                }
            }
            colisaoObstaculo(bola, mapa, i);
            colisaoBorda(bola, mapa, i);
            colisaoPlayer(bola, player1, player2, mapa, i);
            mudaCor(15);
            setCursor(bola->posX[i], bola->posY[i]); //altera a posicao do cursor paraa nova posica da bola
            printf("0"); //imprime a bola
            if(bola->posY[i] < 2) {
                bola->bolaFora = i;
                return 1;
            }
            else if(bola->posY[i] > mapa->linhas-1) {
                bola->bolaFora = i;
                return 2;
            }
        }
        return 0;
}
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa, int i) {
        if(bola->posY[i] >= player1->posYPlayer1-1) {
                if (player1->velX == 0) {
                    if(bola->posX[i] >= player1->posXPlayer1+1 && bola->posX[i] <= player1->posXPlayer1+(player1->tamanho-1)) {
                        bola->dirY[i]*=-1;
                    }
                    else if(bola->posX[i] == player1->posXPlayer1) {
                        bola->dirY[i]*=-1;
                        bola->dirX[i]=-abs(bola->dirX[i]);
                    } else if(bola->posX[i] == player1->posXPlayer1+player1->tamanho) {
                        bola->dirY[i]*=-1;
                        bola->dirX[i]=abs(bola->dirX[i]);
                    }
                }
                else {
                    if(bola->posX[i] >= player1->posXPlayer1 && bola->posX[i] <= player1->posXPlayer1+player1->tamanho) {
                        if(player1->velX == 1) {
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=abs(bola->dirX[i]);
                        }
                        else if(player1->velX == -1) {
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=-abs(bola->dirX[i]);
                        }
                    }
                }
        }

        if(bola->posY[i] <= player2->posYPlayer2+1) {
                if (player2->velX == 0) {
                    if(bola->posX[i] >= player2->posXPlayer2+1 && bola->posX[i] <= player2->posXPlayer2+(player2->tamanho-1)) {
                        bola->dirY[i]*=-1;
                    }
                    else if(bola->posX[i] == player2->posXPlayer2) {
                        bola->dirY[i]*=-1;
                        bola->dirX[i]=-abs(bola->dirX[i]);
                    } else if(bola->posX[i] == player2->posXPlayer2+player2->tamanho) {
                        bola->dirY[i]*=-1;
                        bola->dirX[i]=abs(bola->dirX[i]);
                    }
                }
                else {
                    if(bola->posX[i] >= player2->posXPlayer2 && bola->posX[i] <= player2->posXPlayer2+player2->tamanho) {
                        if(player2->velX == 1) {
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=abs(bola->dirX[i]);
                        }
                        else if(player2->velX == -1) {
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=-abs(bola->dirX[i]);
                        }
                    }
                }
        }
}

void colisaoBorda(BOLA *bola, MAPA *mapa, int i) {
        if(bola->posX[i] <= 2 || bola->posX[i] >= mapa->colunas-3) bola->dirX[i]*=-1;
}

void colisaoObstaculo(BOLA *bola, MAPA *mapa, int i) {
    if(mapa->mapa[bola->posY[i]+1][bola->posX[i]+1] == 1) {
        bola->dirX[i]*=-1;
        bola->dirY[i]*=-1;
    }
}
