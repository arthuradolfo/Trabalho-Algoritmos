
typedef struct player2 {
    int posXPlayer2; // posicao em x do player 2
    int posYPlayer2; // posicao em y do player 2 (apenas para brutal mode)
    int tamanho; // quantidade de caracteres em largura que possui a raquete do player 2
    int dirX; // quantos espacos de caracter ele deve andar ao se movimentar no eixo x (eh a velocidade dele em x)
    int dirY; // quantos espacos de caracter ele deve andar ao se movimentar no eixo y (eh a velocidade dele em y)(apenas para brutal mode)
    int velX; // sentido em X para o qual ele segue. 0 significa parado, 1 singifica direita e -1 significa esquerda
    int velY; // sentido em y para o qual ele segue (apenas brutal mode)
    int nivelIA; //nivel da inteligencia aritificl para caso seja o computador jogando
    int multiplayer; // igual a 1 se o player 2 for humano e igual a 0 se player 2 for o comptuador
    AUMENTATAM aumentatam; //item (nao implementado)
    char raquete[MAXRAQUETE]; // caracteres que compoem a raquete (tem o tamanho maximo que a raquete pode assumir em um jogo hipotetico)
} PLAYER2;
