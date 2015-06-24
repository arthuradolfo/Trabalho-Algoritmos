void movimentoItem(int item, int velY, int posX, int posY, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa);
void apareceItem(int item, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa);

void apareceItem(int item, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa) {
    int velY, posX, posY;
    srand(time(NULL));
    if(rand()%2 == 0) {
        velY = 1;
    }
    else {
        velY = -1;
    }
    posX = (rand()%70)+2;
    posY = mapa.linhas/2;
    movimentoItem(item, velY, posX, posY, player1,player2, mapa);
}

void movimentoItem(int item, int velY, int posX, int posY, PLAYER1 *player1, PLAYER2 *player2, MAPA *mapa) {
    char itemCarac;
    if(item == 1) itemCarac = 'A';
    setCursor(posX, posY);
    printf("%c", itemCarac);

}
