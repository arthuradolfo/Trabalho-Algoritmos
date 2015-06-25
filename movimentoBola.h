int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, PLAYER1 *player3, PLAYER2 *player4, MAPA *mapa, int brutal, int *colidiuPlayer1, int *colidiuPlayer2);
void colisaoBorda(BOLA *bola, MAPA *mapa, int i);
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa, int i);
void colisaoPlayer1(BOLA *bola, PLAYER1 *player1, MAPA *mapa, int i, int *colidiuPlayer1, int *colidiuPlayer2);
void colisaoPlayer2(BOLA *bola, PLAYER2 *player2, MAPA *mapa, int i, int *colidiuPlayer1, int *colidiuPlayer2);
void colisaoObstaculo(BOLA *bola, MAPA *mapa, int i);

int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, PLAYER1 *player3, PLAYER2 *player4, MAPA *mapa, int brutal, int *colidiuPlayer1, int *colidiuPlayer2) {
        int i, j;
        for (i = 0; i < bola->numBolas; i++) {//movimento para cada bola em jogo
            //apaga bola pois ela se moveu
            setCursor(bola->posX[i], bola->posY[i]);
            printf(" ");

            //se for brutalMode tem uma linha no meio, entao tem que repor a linha se a bola passar por ali
            if(brutal == 1) {
                    if(bola->posY[i] == mapa->linhas/2+1) {
                        setCursor(bola->posX[i], bola->posY[i]);
                        printf("-");
                    }
            }

            for(j = 0; j < abs(bola->dirY[i]); j++) {
                //move a bola quantas vezes for dito pra ela se mover
                setCursor(bola->posX[i], bola->posY[i]);
                printf(" ");

                if(brutal == 1) {
                        if(bola->posY[i] == mapa->linhas/2+1) {
                            mudaCor(15);
                            setCursor(bola->posX[i], bola->posY[i]);
                            printf("-");
                        }
                }

                if(bola->posY[i] < mapa->linhas && bola->posY[i] > 0) {
                    bola->posY[i]+=bola->dirY[i]/abs(bola->dirY[i]);
                }

                if(bola->posX[i] <= mapa->colunas-2 && bola->posX[i] >= 1) {
                    bola->posX[i]+=bola->dirX[i]/abs(bola->dirX[i]);
                }

                //testa se a bola bateu em obstaculo
                colisaoObstaculo(bola, mapa, i);

                //testa se a bola bate em algum player
                if(brutal == 0) {
                    colisaoPlayer(bola, player1, player2, mapa, i);
                }
                else {
                        colisaoPlayer1(bola, player1, mapa, j, colidiuPlayer1, colidiuPlayer2);
                        colisaoPlayer2(bola, player2, mapa, j, colidiuPlayer1, colidiuPlayer2);
                        if(player3)colisaoPlayer1(bola, player3, mapa, j, colidiuPlayer1, colidiuPlayer2);
                        if(player4)colisaoPlayer2(bola, player4, mapa, j, colidiuPlayer1, colidiuPlayer2);
                }

                //imprime a bola
                mudaCor(15);
                setCursor(bola->posX[i], bola->posY[i]);
                printf("0");

            }

            //ponto do player 1
            if(bola->posY[i] < 2) {
                bola->bolaFora = i;
                return 1;
            }
            //ponto do player 2
            else if(bola->posY[i] > mapa->linhas-1) {
                bola->bolaFora = i;
                return 2;
            }

        }
        return 0;
}
//colisao usada no modo one player e two player
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa, int i) {
        if(bola->posY[i] == player1->posYPlayer1-1) {//se a bola esta na frente do player1
                if (player1->velX == 0) {//player parado
                    //colisao no corpo da barra
                    if(bola->posX[i] >= player1->posXPlayer1+1 && bola->posX[i] <= player1->posXPlayer1+(player1->tamanho-1)) {
                        bola->dirY[i]*=-1;
                    }
                    //colisao na quina esquerda
                    else if(bola->posX[i] == player1->posXPlayer1) {
                        bola->dirY[i]*=-1;
                        bola->dirX[i]=-abs(bola->dirX[i]);
                    } else if(bola->posX[i] == player1->posXPlayer1+player1->tamanho) {//colisao na quina direita
                        bola->dirY[i]*=-1;
                        bola->dirX[i]=abs(bola->dirX[i]);
                    }
                }
                else {//player em movimento
                    if(bola->posX[i] >= player1->posXPlayer1 && bola->posX[i] <= player1->posXPlayer1+player1->tamanho) {
                        if(player1->velX == 1) {//player vai pra direita
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=abs(bola->dirX[i]);//se o player vai pra direita a bola tambem
                        }
                        else if(player1->velX == -1) {//player vai pra esquerda
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=-abs(bola->dirX[i]);//se o player vai pra esquerda a bola também
                        }
                    }
                }
        }
        //testa colisao para o player 2
        if(bola->posY[i] == player2->posYPlayer2+1) {
                player2->qualBola = (player2->qualBola+1)%bola->numBolas; //segue a proxima bola
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

//colisao usada no brutal mode pro player 1
void colisaoPlayer1(BOLA *bola, PLAYER1 *player1, MAPA *mapa, int i, int *colidiuPlayer1, int *colidiuPlayer2) {
        if(*colidiuPlayer1 == 0) {//so faz se ainda nao tiver colidido
            if(bola->posY[i] >= player1->posYPlayer1-1 && bola->posY[i] <= player1->posYPlayer1+1) {//se a bola esta na na linha da frente do player1 ou em cima dele ou atras
                    if (player1->velX == 0) {//player1 esta parado

                        //colsisao no corpo da barra
                        if(bola->posX[i] >= player1->posXPlayer1+1 && bola->posX[i] <= player1->posXPlayer1+(player1->tamanho-1)) {
                            bola->dirY[i]*=-1;
                            *colidiuPlayer1 = 1;
                            *colidiuPlayer2 = 0;
                        }

                        else if(bola->posX[i] == player1->posXPlayer1) {//colisao na quina esquerda
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=-abs(bola->dirX[i]);
                            *colidiuPlayer1 = 1;
                            *colidiuPlayer2 = 0;
                        } else if(bola->posX[i] == player1->posXPlayer1+player1->tamanho) {//colisao na quina direita
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=abs(bola->dirX[i]);
                            *colidiuPlayer1 = 1;
                            *colidiuPlayer2 = 0;
                        }
                    }
                    else { //player 1 se move
                        if(bola->posX[i] >= player1->posXPlayer1 && bola->posX[i] <= player1->posXPlayer1+player1->tamanho) {
                            if(player1->velX == 1) {//player1 se move pra direita
                                bola->dirY[i]*=-1;
                                bola->dirX[i]=abs(bola->dirX[i]); //a bola sempre vai acabar indo pra direita também
                                *colidiuPlayer1 = 1;
                                *colidiuPlayer2 = 0;
                            }
                            else if(player1->velX == -1) {//player1 se move pra esquerda
                                bola->dirY[i]*=-1;
                                bola->dirX[i]=-abs(bola->dirX[i]);//a bola sempre vai acabar indo pra esquerda também
                                *colidiuPlayer1 = 1;
                                *colidiuPlayer2 = 0;
                            }
                        }
                    }
            }
        }
}

//colisao usada no brutal mode com o player 2, analoga à usada com o player 1 no brutal mode
void colisaoPlayer2(BOLA *bola, PLAYER2 *player2, MAPA *mapa, int i, int *colidiuPlayer1, int *colidiuPlayer2) {
        if(*colidiuPlayer2 == 0) {
            if(bola->posY[i] <= player2->posYPlayer2+1 && bola->posY[i] >= player2->posYPlayer2-1) {
                    if (player2->velX == 0) {
                        if(bola->posX[i] >= player2->posXPlayer2+1 && bola->posX[i] <= player2->posXPlayer2+(player2->tamanho-1)) {
                            bola->dirY[i]*=-1;
                            *colidiuPlayer2 = 1;
                            *colidiuPlayer1 = 0;
                        }
                        else if(bola->posX[i] == player2->posXPlayer2) {
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=-abs(bola->dirX[i]);
                            *colidiuPlayer2 = 1;
                            *colidiuPlayer1 = 0;
                        } else if(bola->posX[i] == player2->posXPlayer2+player2->tamanho) {
                            bola->dirY[i]*=-1;
                            bola->dirX[i]=abs(bola->dirX[i]);
                            *colidiuPlayer2 = 1;
                            *colidiuPlayer1 = 0;
                        }
                    }
                    else {
                        if(bola->posX[i] >= player2->posXPlayer2 && bola->posX[i] <= player2->posXPlayer2+player2->tamanho) {
                            if(player2->velX == 1) {
                                bola->dirY[i]*=-1;

                                bola->dirX[i]=abs(bola->dirX[i]);
                                *colidiuPlayer2 = 1;
                                *colidiuPlayer1 = 0;
                            }
                            else if(player2->velX == -1) {
                                bola->dirY[i]*=-1;

                                bola->dirX[i]=-abs(bola->dirX[i]);
                                *colidiuPlayer2 = 1;
                                *colidiuPlayer1 = 0;
                            }
                        }
                    }
            }
        }
}

void colisaoBorda(BOLA *bola, MAPA *mapa, int i) {
    if(bola->posX[i] <= 2 || bola->posX[i] >= mapa->colunas-1) bola->dirX[i]*=-1;
}

void colisaoObstaculo(BOLA *bola, MAPA *mapa, int i) {
    if(bola->dirY[i] > 0) {
        if(bola->dirX[i] > 0) {
            if(mapa->mapa[bola->posY[i]-1][bola->posX[i]+1] == 1 && mapa->mapa[bola->posY[i]][bola->posX[i]] == 1 && mapa->mapa[bola->posY[i]][bola->posX[i]+1] == 1) {
                bola->dirX[i]*=-1;
                bola->dirY[i]*=-1;
            }
            //bola bate na base do obstaculo e volta em Y
            else if(mapa->mapa[bola->posY[i]][bola->posX[i]] == 1) {
                bola->dirY[i]*=-1;
            }
            //bola bate na lateral do obstaculo e volta em X
            else if(mapa->mapa[bola->posY[i]-1][bola->posX[i]+1] == 1) {
                bola->dirX[i]*=-1;
            }
            //bola bate na quina do obstaculo, volta em X e Y
            else if(mapa->mapa[bola->posY[i]][bola->posX[i]+1] == 1) {
                bola->dirX[i]*=-1;
                bola->dirY[i]*=-1;
            }
            else if(bola->posX[i] <= 2 || bola->posX[i] >= mapa->colunas-1) bola->dirX[i]*=-1;
        }
        else if(bola->dirX[i] < 0) {
            if (mapa->mapa[bola->posY[i]-1][bola->posX[i]-1] == 1 && mapa->mapa[bola->posY[i]][bola->posX[i]] == 1 && mapa->mapa[bola->posY[i]][bola->posX[i]-1] == 1) {
                bola->dirX[i]*=-1;
                bola->dirY[i]*=-1;
            }
            //bola bate na base do obstaculo e volta em Y
            else if(mapa->mapa[bola->posY[i]][bola->posX[i]] == 1) {
                bola->dirY[i]*=-1;
            }
            //bola bate na lateral do obstaculo e volta em X
            else if(mapa->mapa[bola->posY[i]-1][bola->posX[i]-1] == 1) {
                bola->dirX[i]*=-1;
            }
            //bola bate na quina do obstaculo, volta em X e Y
            else if(mapa->mapa[bola->posY[i]][bola->posX[i]-1] == 1) {
                bola->dirX[i]*=-1;
                bola->dirY[i]*=-1;
            }
            else if(bola->posX[i] <= 2 || bola->posX[i] >= mapa->colunas-1) bola->dirX[i]*=-1;
        }
    }
    else {
        if(bola->dirX[i] > 0) {
            if (mapa->mapa[bola->posY[i]-1][bola->posX[i]+1] == 1 && mapa->mapa[bola->posY[i]-1][bola->posX[i]] == 1 && mapa->mapa[bola->posY[i]][bola->posX[i]+1] == 1) {
                bola->dirX[i]*=-1;
                bola->dirY[i]*=-1;
            }
            //bola bate na base do obstaculo e volta em Y
            else if(mapa->mapa[bola->posY[i]-2][bola->posX[i]] == 1) {
                bola->dirY[i]*=-1;
            }
            //bola bate na lateral do obstaculo e volta em X
            else if(mapa->mapa[bola->posY[i]-1][bola->posX[i]+1] == 1) {
                bola->dirX[i]*=-1;
            }
            //bola bate na quina do obstaculo, volta em X e Y
            else if(mapa->mapa[bola->posY[i]-2][bola->posX[i]+1] == 1) {
                bola->dirX[i]*=-1;
                bola->dirY[i]*=-1;
            }
            else if(bola->posX[i] <= 2 || bola->posX[i] >= mapa->colunas-1) bola->dirX[i]*=-1;
        }
        else if(bola->dirX[i] < 0) {
            if (mapa->mapa[bola->posY[i]-1][bola->posX[i]-1] == 1 && mapa->mapa[bola->posY[i]-1][bola->posX[i]] == 1 && mapa->mapa[bola->posY[i]][bola->posX[i]-1] == 1) {
                bola->dirX[i]*=-1;
                bola->dirY[i]*=-1;
            }
            //bola bate na base do obstaculo e volta em Y
            else if(mapa->mapa[bola->posY[i]-2][bola->posX[i]] == 1) {
                bola->dirY[i]*=-1;
            }
            //bola bate na lateral do obstaculo e volta em X
            else if(mapa->mapa[bola->posY[i]-1][bola->posX[i]-1] == 1) {
                bola->dirX[i]*=-1;
            }
            //bola bate na quina do obstaculo, volta em X e Y
            else if(mapa->mapa[bola->posY[i]-2][bola->posX[i]-1] == 1) {
                bola->dirX[i]*=-1;
                bola->dirY[i]*=-1;
            }
            else if(bola->posX[i] <= 2 || bola->posX[i] >= mapa->colunas-1) bola->dirX[i]*=-1;
        }
    }
}
