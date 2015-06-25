//guarda as informaçoes do nivel do jogo
//cada nivel com suas caracteristicas está salvo num arquivo binario

typedef struct nivel{
    int velPlayer1;//velocidade do player 1, (corresponde ao dirX/Yplayer1)
    int velPlayer2;//velocidade do player 1, (corresponde ao dirX/Yplayer1)
    int tamPlayer1;//tamanho da raquete do player 1
    int tamPlayer2;//tamanho da raquete do player 1
    int velBola;//velocidade do moivmento da bola
    int IAPlayer2;//nivel de dificuldade da inteligencia do oponente
}NIVEL;
