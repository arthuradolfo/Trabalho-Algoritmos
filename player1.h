typedef struct player1 {
    int posXPlayer1; // posicao em x do player 1
    int posYPlayer1; // posicao em y do player 2 (caso haja mudanca de mapa eh preciso mudar a posicao) (usa-se no brutal mode)
    int tamanho; // numero de caracteres que compoem a raquete
    int dirX; // quantos espacos de caracter deve andar em x a cada vez que se movimenta em x
    int dirY;// quantos espacos de caracter deve andar em y a cada vez que se movimenta em y (brutal mode)
    int velX; // sentido do movimento em X
    int velY; // sentido do movimento em Y (apenas brutal mode)
    AUMENTATAM aumentaTam;
    char raquete[MAXRAQUETE]; // caracteres que compoem a raquete do player 1
} PLAYER1;
