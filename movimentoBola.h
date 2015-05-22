int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa);
void colisaoBorda(BOLA *bola, MAPA *mapa);
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa);

int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa) {
        int i;
        //bola
        setCursor(bola->posX, bola->posY); // altera a posicao do cursor para o da bola
        printf(" "); // imprime um espaco sobre a bola
        // verifica colisoes
                //movimenta a bola
        colisaoBorda(bola, mapa);
        if(bola->posY < mapa->linhas) {
                for(i = 0; i < abs(bola->dirY); i++) {
                    if(bola->posY < mapa->linhas-1 && bola->posY > 0) {
                        bola->posY+=bola->dirY/abs(bola->dirY);
                    }
                }
        }
        colisaoPlayer(bola, player1, player2, mapa);
        setCursor(bola->posX, bola->posY); //altera a posicao do cursor paraa nova posica da bola
        printf("0"); //imprime a bola
        if(bola->posY < 1) {
            return 1;
        }
        else if(bola->posY > mapa->linhas-2) {
            return 2;
        }
        else {
            return 0;
        }
}
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa) {
    if(bola->posX+bola->dirX == 1 || bola->posX+bola->dirX == mapa->colunas-2) bola->dirX*=-1;
        if(bola->posY >= player1->posYPlayer1-2) {
                if (player1->velX == 0) {
                    if(bola->posX >= player1->posXPlayer1+1 && bola->posX <= player1->posXPlayer1+(player1->tamanho-1)) {
                        bola->dirY*=-1;
                    }
                    else if(bola->posX == player1->posXPlayer1) {
                        bola->dirY*=-1;
                        bola->dirX=-abs(bola->dirX);
                    } else if(bola->posX == player1->posXPlayer1+player1->tamanho) {
                        bola->dirY*=-1;
                        bola->dirX=abs(bola->dirX);
                    }
                }
                else {
                    if(bola->posX >= player1->posXPlayer1 && bola->posX <= player1->posXPlayer1+player1->tamanho) {
                        if(player1->velX == 1) {
                            bola->dirY*=-1;
                            bola->dirX=abs(bola->dirX);
                        }
                        else if(player1->velX == -1) {
                            bola->dirY*=-1;
                            bola->dirX=-abs(bola->dirX);
                        }
                    }
                }
        }

        if(bola->posY <= player2->posYPlayer2+2) {
                if (player2->velX == 0) {
                    if(bola->posX >= player2->posXPlayer2+1 && bola->posX <= player2->posXPlayer2+(player2->tamanho-1)) {
                        bola->dirY*=-1;
                    }
                    else if(bola->posX == player2->posXPlayer2) {
                        bola->dirY*=-1;
                        bola->dirX=-abs(bola.dirX);
                    } else if(bola->posX == player2->posXPlayer2+player2->tamanho) {
                        bola->dirY*=-1;
                        bola->dirX=abs(bola->dirX);
                    }
                }
                else {
                    if(bola->posX >= player2->posXPlayer2 && bola->posX <= player2->posXPlayer2+player2->tamanho) {
                        if(player2->velX == 1) {
                            bola->dirY*=-1;
                            bola->dirX=abs(bola->dirX);
                        }
                        else if(player2->velX == -1) {
                            bola->dirY*=-1;
                            bola->dirX=-abs(bola->dirX);
                        }
                    }
                }
        }
}

void colisaoBorda(BOLA *bola, MAPA *mapa) {
    int i;
    if(bola->posX > 1) {
        if(bola->dirX > 0) {
            for(i = 0; i < abs(bola->dirX); i++) {
                if(bola->posX < mapa->colunas-2) {
                    bola->posX++;
                }
            }
        }
    }
    if(bola->posX < mapa->colunas-1) {
        if(bola->dirX < 0) {
            for(i = 0; i < abs(bola->dirX); i++) {
                if(bola->posX > 2) {
                    bola->posX--;
                }
            }
        }
    }
    if(bola->posX < 0) {
        bola->posX = 2;
    }
    if(bola->posX > mapa->colunas-1) {
        bola->posX = mapa->colunas-2;
    }
}
