typedef struct bola {
    int posX[MAXBOLAS]; // posicao X de cada bola
    int posY[MAXBOLAS]; // posicao Y de cada bola
    int dirX[MAXBOLAS]; // numero de espacos de caracter que cada bola anda ao se movimentar em x
    int dirY[MAXBOLAS]; // numero de espacos de caracter que cada bola anda ao se movimentar em y
    int numBolas; // numero de bolas em jogo
    int bolaFora; // o indice da bola que marcou o ponto
    char bola; // caracter que repsentara a bola
} BOLA;
