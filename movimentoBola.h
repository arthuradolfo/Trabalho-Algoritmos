int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2);
void colisaoBorda(BOLA *bola);
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2);

int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2) {
        int i;
        //bola
        setCursor(bola->posX, bola->posY); // altera a posicao do cursor para o da bola
        printf(" "); // imprime um espaco sobre a bola
        // verifica colisoes
                //movimenta a bola
        colisaoBorda(bola);
        if(bola->posY < HEIGHT) {
            if(bola->dirY > 0) {
                bola->posY++;
                for(i = 1; i < abs(bola->dirY); i++) {
                    if(bola->posY < HEIGHT-2) {
                        bola->posY++;
                    }
                }
            }
        }
        if(bola->posY > 0) {
            if(bola->dirY < 0) {
                bola->posY--;
                for(i = 1; i < abs(bola->dirY); i++) {
                    if(bola->posY > 4) {
                        bola->posY--;
                    }
                }
            }
        }
        colisaoPlayer(bola, player1, player2);
        setCursor(bola->posX, bola->posY); //altera a posicao do cursor paraa nova posica da bola
        printf("0"); //imprime a bola
        if(bola->posY < 1) {
            return 1;
        }
        else if(bola->posY > HEIGHT-2) {
            return 2;
        }
        else {
            return 0;
        }
}
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2) {
    if(bola->posX+bola->dirX == 1 || bola->posX+bola->dirX == WIDTH-2) bola->dirX*=-1;
        if(bola->posY >= player1->posYPlayer1-1) {
                if (player1->velX == 0) {
                    if(bola->posX >= player1->posXPlayer1+1 && bola->posX <= player1->posXPlayer1+(player1->tamanho-1)) {
                        bola->dirY*=-1;
                    }
                    else if(bola->posX == player1->posXPlayer1) {
                        bola->dirY*=-1;
                        bola->dirX=-1;
                    } else if(bola->posX == player1->posXPlayer1+player1->tamanho) {
                        bola->dirY*=-1;
                        bola->dirX=1;
                    }
                }
                else {
                    if(bola->posX >= player1->posXPlayer1 && bola->posX <= player1->posXPlayer1+player1->tamanho) {
                        if(player1->velX == 1) {
                            bola->dirY*=-1;
                            bola->dirX=1;
                        }
                        else if(player1->velX == -1) {
                            bola->dirY*=-1;
                            bola->dirX=-1;
                        }
                    }
                }
        }

        if(bola->posY <= player2->posYPlayer2+1) {
                if (player2->velX == 0) {
                    if(bola->posX >= player2->posXPlayer2+1 && bola->posX <= player2->posXPlayer2+(player2->tamanho-1)) {
                        bola->dirY*=-1;
                    }
                    else if(bola->posX == player2->posXPlayer2) {
                        bola->dirY*=-1;
                        bola->dirX=-1;
                    } else if(bola->posX == player2->posXPlayer2+player2->tamanho) {
                        bola->dirY*=-1;
                        bola->dirX=1;
                    }
                }
                else {
                    if(bola->posX >= player2->posXPlayer2 && bola->posX <= player2->posXPlayer2+player2->tamanho) {
                        if(player2->velX == 1) {
                            bola->dirY*=-1;
                            bola->dirX=1;
                        }
                        else if(player2->velX == -1) {
                            bola->dirY*=-1;
                            bola->dirX=-1;
                        }
                    }
                }
        }
}

void colisaoBorda(BOLA *bola) {
    int i;
    if(bola->posX > 1) {
        if(bola->dirX > 0) {
            bola->posX++;
            for(i = 1; i < abs(bola->dirX); i++) {
                if(bola->posX < WIDTH-2) {
                    bola->posX++;
                }
            }
        }
    }
    if(bola->posX < WIDTH-1) {
        if(bola->dirX < 0) {
            bola->posX--;
            for(i = 1; i < abs(bola->dirX); i++) {
                if(bola->posX > 2) {
                    bola->posX--;
                }
            }
        }
    }
    if(bola->posX < 0) {
        bola->posX = 2;
    }
    if(bola->posX > WIDTH-1) {
        bola->posX = WIDTH-2;
    }
}
