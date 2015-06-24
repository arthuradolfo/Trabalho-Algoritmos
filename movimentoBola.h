int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, PLAYER1 *player3, PLAYER2 *player4, MAPA *mapa, int brutal, int *colidiuPlayer1, int *colidiuPlayer2);
void colisaoBorda(BOLA *bola, MAPA *mapa, int i);
void colisaoPlayer(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa, int i);
void colisaoPlayer1(BOLA *bola, PLAYER1 *player1, MAPA *mapa, int i, int *colidiuPlayer1, int *colidiuPlayer2);
void colisaoPlayer2(BOLA *bola, PLAYER2 *player2, MAPA *mapa, int i, int *colidiuPlayer1, int *colidiuPlayer2);
void colisaoObstaculo(BOLA *bola, MAPA *mapa, int i);

int movimentoBola(BOLA *bola, PLAYER1 *player1, PLAYER2 *player2, PLAYER1 *player3, PLAYER2 *player4, MAPA *mapa, int brutal, int *colidiuPlayer1, int *colidiuPlayer2) {
        int i, j;
        for (i = 0; i < bola->numBolas; i++) {

            colisaoBorda(bola, mapa, i);
            setCursor(bola->posX[i], bola->posY[i]);
            printf(" ");
            if(brutal == 1) {
                    if(bola->posY[i] == mapa->linhas/2+1) {
                        setCursor(bola->posX[i], bola->posY[i]);
                        printf("-");
                    }
            }
            for(j = 0; j < abs(bola->dirY[i]); j++) {
                setCursor(bola->posX[i], bola->posY[i]); // altera a posicao do cursor para o da bola
                printf(" "); // imprime um espaco sobre a bola
                if(brutal == 1) {
                        if(bola->posY[i] == mapa->linhas/2+1) {
                            mudaCor(15);
                            setCursor(bola->posX[i], bola->posY[i]);
                            printf("-");
                        }
                }
                if(bola->posY[i] < mapa->linhas && bola->posY[i] > 0) {
                    bola->posY[i]+=bola->dirY[i]/abs(bola->dirY[i]);
                    //colisaoBorda(bola, mapa, i);
                }
            //}
            //for(j = 0; j < abs(bola->dirX[i]); j++) {
                if(bola->posX[i] <= mapa->colunas-2 && bola->posX[i] >= 1) {
                    bola->posX[i]+=bola->dirX[i]/abs(bola->dirX[i]);
                    //colisaoBorda(bola, mapa, i);
                    //colisaoObstaculo(bola, mapa, i);
                    //colisaoPlayer(bola, player1, player2, mapa, i);
                }
                //colisaoBorda(bola, mapa, i);
                colisaoObstaculo(bola, mapa, i);
                if(brutal == 0) {
                    colisaoPlayer(bola, player1, player2, mapa, i);
                }
                else {
                        colisaoPlayer1(bola, player1, mapa, j, colidiuPlayer1, colidiuPlayer2);
                        colisaoPlayer2(bola, player2, mapa, j, colidiuPlayer1, colidiuPlayer2);
                        if(player3)colisaoPlayer1(bola, player3, mapa, j, colidiuPlayer1, colidiuPlayer2);
                        if(player4)colisaoPlayer2(bola, player4, mapa, j, colidiuPlayer1, colidiuPlayer2);
                }
                mudaCor(15);
                setCursor(bola->posX[i], bola->posY[i]); //altera a posicao do cursor paraa nova posica da bola
                printf("0"); //imprime a bola

            }
            //colisaoObstaculo(bola, mapa, i);
//          colisaoBorda(bola, mapa, i);
            //colisaoPlayer(bola, player1, player2, mapa, i);
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
        if(bola->posY[i] == player1->posYPlayer1-1) {
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
        if(bola->posY[i] == player2->posYPlayer2+1) {
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

void colisaoPlayer1(BOLA *bola, PLAYER1 *player1, MAPA *mapa, int i, int *colidiuPlayer1, int *colidiuPlayer2) {
        if(*colidiuPlayer1 == 0) {
            if(bola->posY[i] >= player1->posYPlayer1-1 && bola->posY[i] <= player1->posYPlayer1+1) {
                    if (player1->velX == 0) {
                        if(bola->posX[i] >= player1->posXPlayer1+1 && bola->posX[i] <= player1->posXPlayer1+(player1->tamanho-1)) {
                            bola->dirY[i]*=-1;
                            *colidiuPlayer1 = 1;
                            *colidiuPlayer2 = 0;
                            //bola->posY[i] += 2*bola->dirY[i];
                        }
                        else if(bola->posX[i] == player1->posXPlayer1) {
                            bola->dirY[i]*=-1;
                            //bola->posY[i] += 2*bola->dirY[i];
                            bola->dirX[i]=-abs(bola->dirX[i]);
                            *colidiuPlayer1 = 1;
                            *colidiuPlayer2 = 0;
                        } else if(bola->posX[i] == player1->posXPlayer1+player1->tamanho) {
                            bola->dirY[i]*=-1;
                            //bola->posY[i] += 2*bola->dirY[i];
                            bola->dirX[i]=abs(bola->dirX[i]);
                            *colidiuPlayer1 = 1;
                            *colidiuPlayer2 = 0;
                        }
                    }
                    else {
                        if(bola->posX[i] >= player1->posXPlayer1 && bola->posX[i] <= player1->posXPlayer1+player1->tamanho) {
                            if(player1->velX == 1) {
                                bola->dirY[i]*=-1;
                                //bola->posY[i] += 2*bola->dirY[i];
                                bola->dirX[i]=abs(bola->dirX[i]);
                                *colidiuPlayer1 = 1;
                                *colidiuPlayer2 = 0;
                            }
                            else if(player1->velX == -1) {
                                bola->dirY[i]*=-1;
                                //bola->posY[i] += 2*bola->dirY[i];
                                bola->dirX[i]=-abs(bola->dirX[i]);
                                *colidiuPlayer1 = 1;
                                *colidiuPlayer2 = 0;
                            }
                        }
                    }
            }
        }
}

void colisaoPlayer2(BOLA *bola, PLAYER2 *player2, MAPA *mapa, int i, int *colidiuPlayer1, int *colidiuPlayer2) {
        if(*colidiuPlayer2 == 0) {
            if(bola->posY[i] <= player2->posYPlayer2+1 && bola->posY[i] >= player2->posYPlayer2-1) {
                    if (player2->velX == 0) {
                        if(bola->posX[i] >= player2->posXPlayer2+1 && bola->posX[i] <= player2->posXPlayer2+(player2->tamanho-1)) {
                            bola->dirY[i]*=-1;
                            *colidiuPlayer2 = 1;
                            *colidiuPlayer1 = 0;
                            //bola->posY[i] += 2*bola->dirY[i];
                        }
                        else if(bola->posX[i] == player2->posXPlayer2) {
                            bola->dirY[i]*=-1;
                            //bola->posY[i] += 3*bola->dirY[i];
                            bola->dirX[i]=-abs(bola->dirX[i]);
                            *colidiuPlayer2 = 1;
                            *colidiuPlayer1 = 0;
                        } else if(bola->posX[i] == player2->posXPlayer2+player2->tamanho) {
                            bola->dirY[i]*=-1;
                            //bola->posY[i] += 2*bola->dirY[i];
                            bola->dirX[i]=abs(bola->dirX[i]);
                            *colidiuPlayer2 = 1;
                            *colidiuPlayer1 = 0;
                        }
                    }
                    else {
                        if(bola->posX[i] >= player2->posXPlayer2 && bola->posX[i] <= player2->posXPlayer2+player2->tamanho) {
                            if(player2->velX == 1) {
                                bola->dirY[i]*=-1;
                                //bola->posY[i] += 2*bola->dirY[i];
                                bola->dirX[i]=abs(bola->dirX[i]);
                                *colidiuPlayer2 = 1;
                                *colidiuPlayer1 = 0;
                            }
                            else if(player2->velX == -1) {
                                bola->dirY[i]*=-1;
                                //bola->posY[i] += 2*bola->dirY[i];
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
        }
    }
}
