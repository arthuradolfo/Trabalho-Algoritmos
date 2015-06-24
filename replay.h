typedef struct frame {
    int idMapa; // qual mapa esta sendo jogado
    int posicaoXplayer1; // posicao em x do player 1
    int posicaoYplayer1; // posicao em y do player 1
    int posicaoXplayer2; // posicao em x do player 2
    int posicaoYplayer2; // posicao em y do player 2
    int posicaoXplayer3; // posicao em x do player 1
    int posicaoYplayer3; // posicao em y do player 1
    int posicaoXplayer4; // posicao em x do player 2
    int posicaoYplayer4; // posicao em y do player 2
    int posicaoXbola[MAXBOLAS]; // posicao em x de cada bola
    int posicaoYbola[MAXBOLAS]; // posicao em y de cada bola
    int pontuacaoPlayer1; // pontuacao do player1
    int pontuacaoPlayer2; // pontuacao do player2
    int nivel; // nivel
} FRAME;

void salvaReplay(int idMapa, PLAYER1 *player1, PLAYER2 *player2, PLAYER1 *player3, PLAYER2 *player4, BOLA *bola, int pontuacaoPlayer1, int pontuacaoPlayer2, int nivel, FILE *replay);
void rodaReplay();

void salvaReplay(int idMapa, PLAYER1 *player1, PLAYER2 *player2, PLAYER1 *player3, PLAYER2 *player4, BOLA *bola, int pontuacaoPlayer1, int pontuacaoPlayer2, int nivel, FILE *replay) {
    int i;
    //inicializa o frame
    FRAME frame = {0, 0, 0, 0, 0, INATIVA, INATIVA, INATIVA, INATIVA, {INATIVA, INATIVA, INATIVA, INATIVA, INATIVA}, {INATIVA, INATIVA, INATIVA, INATIVA, INATIVA}, 0, 0, 0};

    //atribui os valores do momento atual do jogo ao frame
    frame.idMapa = idMapa;
    frame.posicaoXplayer1 = player1->posXPlayer1;
    frame.posicaoYplayer1 = player1->posYPlayer1;
    frame.posicaoXplayer2 = player2->posXPlayer2;
    frame.posicaoYplayer2 = player2->posYPlayer2;
    if(player3) {
        frame.posicaoXplayer3 = player3->posXPlayer1;
    }
    else {
        frame.posicaoXplayer3 = INATIVA;
    }
    if(player3) {
        frame.posicaoYplayer3 = player3->posYPlayer1;
    }
    else {
        frame.posicaoYplayer3 = INATIVA;
    }
    if(player4) {
        frame.posicaoXplayer4 = player4->posXPlayer2;
    }
    else {
        frame.posicaoXplayer4 = INATIVA;
    }
    if(player4) {
        frame.posicaoYplayer4 = player4->posYPlayer2;
    }
    else {
        frame.posicaoYplayer4 = INATIVA;
    }
    frame.pontuacaoPlayer1 = pontuacaoPlayer1;
    frame.pontuacaoPlayer2 = pontuacaoPlayer2;
    frame.nivel = nivel;
    //atribui a posicao de cada bola ao frame
    for(i = 0; i < bola->numBolas; i++) {
        frame.posicaoXbola[i] = bola->posX[i];
        frame.posicaoYbola[i] = bola->posY[i];
    }

    //escreve o frame no arquivo replay
    fwrite(&frame, sizeof(FRAME), 1, replay);
    fflush(replay);
}

void rodaReplay() { // reproduz o replay salvo no arquivo replay (correspondente ao ultimo jogo)

    FRAME frame;
    MAPA mapa;
    char qualMapa[MAXNAME] = "maps";
    char idMapa[5];

    int i, primeira = 1;
    FILE *replay;
    //abre arquivo replay, que eh padrado do jogo e portanto existe obrigatoriamente
    if((replay  = fopen("replay", "rb"))) {

        NIVEL st_nivel;
        FILE* arqNivel;
        arqNivel = fopen("arqNiv","rb");

        fseek(arqNivel,(frame.nivel-1)*sizeof(NIVEL),SEEK_SET);
        fread(&st_nivel,sizeof(NIVEL),1,arqNivel);

        fclose(arqNivel);
        PLAYER1 player1 = {frame.posicaoXplayer1, frame.posicaoYplayer1, st_nivel.tamPlayer1, st_nivel.velPlayer1, st_nivel.velPlayer1, 0, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
        PLAYER2 player2 = {frame.posicaoXplayer2, frame.posicaoYplayer2, st_nivel.tamPlayer2, st_nivel.velPlayer2, st_nivel.velPlayer1, 0, 0, st_nivel.IAPlayer2, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
        PLAYER1 player3 = {frame.posicaoXplayer3, frame.posicaoYplayer3, 20, 0, 0, 0, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
        PLAYER2 player4 = {frame.posicaoXplayer4, frame.posicaoYplayer4, 20, 0, 0, 0, 0, 0, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
        char raquetePlayer1[player1.tamanho+1], raquetePlayer2[player2.tamanho+1], raquetePlayerApaga1[player1.tamanho+1], raquetePlayerApaga2[player2.tamanho+1];
        int idMapaAnt, pontuacaoPlayer1Ant, pontuacaoPlayer2Ant, posicaoXplayer1Ant, posicaoXplayer2Ant ,posicaoXplayer3Ant, posicaoXplayer4Ant, posicaoYplayer1Ant, posicaoYplayer2Ant ,posicaoYplayer3Ant, posicaoYplayer4Ant, posicaoXbolaAnt[5], posicaoYbolaAnt[5];
        while(!feof(replay)) {
            if(fread(&frame, sizeof(FRAME), 1, replay) == 1) {
                arqNivel = fopen("arqNiv","rb");
                fseek(arqNivel,(frame.nivel-1)*sizeof(NIVEL),SEEK_SET);
                fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
                fclose(arqNivel);
                player3.posXPlayer1 = frame.posicaoXplayer3;
                player3.posYPlayer1 = frame.posicaoYplayer3;
                player4.posXPlayer2 = frame.posicaoXplayer4;
                player4.posYPlayer2 = frame.posicaoYplayer4;
                player1.dirX = st_nivel.velPlayer1;
                player2.dirX = st_nivel.velPlayer2;
                if(frame.nivel == -1 || frame.nivel == -2) player1.tamanho = 20;
                else player1.tamanho = st_nivel.tamPlayer1;
                if(frame.nivel == -1 || frame.nivel == -2) player2.tamanho = 20;
                else player2.tamanho = st_nivel.tamPlayer2;
                if(idMapaAnt != frame.idMapa) {
                    system("cls");
                }
                if(primeira == 1) {
                    posicaoXplayer1Ant = frame.posicaoXplayer1;
                    posicaoYplayer1Ant = frame.posicaoYplayer1;
                    posicaoXplayer2Ant = frame.posicaoXplayer2;
                    posicaoYplayer2Ant = frame.posicaoYplayer2;
                    if(player3.posXPlayer1 != INATIVA) posicaoXplayer3Ant = frame.posicaoXplayer3;
                    if(player3.posYPlayer1 != INATIVA) posicaoYplayer3Ant = frame.posicaoYplayer3;
                    if(player4.posXPlayer2 != INATIVA) posicaoXplayer4Ant = frame.posicaoXplayer4;
                    if(player4.posYPlayer2 != INATIVA) posicaoYplayer4Ant = frame.posicaoYplayer4;
                    for(i = 0; i < 5; i++) {
                        posicaoXbolaAnt[i] = frame.posicaoXbola[i];
                        posicaoYbolaAnt[i] = frame.posicaoYbola[i];
                    }
                    primeira = 0;
                }
                for(i = 0; i <= player2.tamanho; i++) {
                        if(i == player2.tamanho) raquetePlayerApaga2[i] = '\0';
                        else raquetePlayerApaga2[i] = ' ';
                }
                setCursor(posicaoXplayer2Ant, posicaoYplayer2Ant);
                puts(raquetePlayerApaga2);
                if(player4.posXPlayer2 != INATIVA) {
                    for(i = 0; i <= player4.tamanho; i++) {
                        if(i == player4.tamanho) raquetePlayerApaga2[i] = '\0';
                        else raquetePlayerApaga2[i] = ' ';
                    }
                    setCursor(posicaoXplayer4Ant, posicaoYplayer4Ant);
                    puts(raquetePlayerApaga2);
                }
                for(i = 0; i <= player1.tamanho; i++) {
                        if(i == player1.tamanho) raquetePlayerApaga1[i] = '\0';
                        else raquetePlayerApaga1[i] = ' ';
                }
                setCursor(posicaoXplayer1Ant, posicaoYplayer1Ant);
                puts(raquetePlayerApaga1);
                if(player3.posXPlayer1 != INATIVA) {
                    for(i = 0; i <= player3.tamanho; i++) {
                            if(i == player3.tamanho) raquetePlayerApaga1[i] = '\0';
                            else raquetePlayerApaga1[i] = ' ';
                    }
                    setCursor(posicaoXplayer3Ant, posicaoYplayer3Ant);
                    puts(raquetePlayerApaga1);
                }
                for(i = 0; i < 5; i++) {\
                    if(frame.posicaoXbola[i] != -1) {
                        setCursor(posicaoXbolaAnt[i], posicaoYbolaAnt[i]);
                        printf(" ");
                    }
                }
                if(pontuacaoPlayer2Ant != frame.pontuacaoPlayer2 || idMapaAnt != frame.idMapa){
                    setCursor(0, 0);
                    pontuacaoPlayer2Ant = frame.pontuacaoPlayer2;
                    printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", frame.pontuacaoPlayer2, frame.nivel);
                }
                setCursor(0, 1);
                if(idMapaAnt != frame.idMapa) {
                    idMapaAnt = frame.idMapa;
                    itoa(frame.idMapa, idMapa, 10);
                    strcpy(qualMapa, "maps");
                    strcat(qualMapa, idMapa);
                    strcat(qualMapa, ".txt");
                    carregaMapaOnePlayer(qualMapa, &mapa);
                    printaMapa(&mapa);
                }
                if(pontuacaoPlayer1Ant != frame.pontuacaoPlayer1 || idMapaAnt != frame.idMapa){
                    pontuacaoPlayer1Ant = frame.pontuacaoPlayer1;
                    setCursor(0, mapa.linhas+1);
                    printf("SCORE: %3d_____________________________________________________________________", frame.pontuacaoPlayer1);
                }
                if(frame.nivel == -2) {
                    setCursor(1, (mapa.linhas/2)+1);
                    printf("------------------------------------------------------------------------------");
                }
                setCursor(frame.posicaoXplayer1, frame.posicaoYplayer1);
                mudaCor(9);
                strncpy(raquetePlayer1, player1.raquete, player1.tamanho);
                raquetePlayer1[player1.tamanho] = '\0';
                puts(raquetePlayer1);
                if(player3.posXPlayer1 != INATIVA) {
                    setCursor(frame.posicaoXplayer3, frame.posicaoYplayer3);
                    mudaCor(9);
                    strncpy(raquetePlayer1, player3.raquete, player3.tamanho);
                    raquetePlayer1[player3.tamanho] = '\0';
                    puts(raquetePlayer1);
                }
                setCursor(frame.posicaoXplayer2, frame.posicaoYplayer2);
                mudaCor(12);
                strncpy(raquetePlayer2, player2.raquete, player2.tamanho);
                raquetePlayer2[player2.tamanho] = '\0';
                puts(raquetePlayer2);
                if(player4.posXPlayer2 != INATIVA) {
                    setCursor(frame.posicaoXplayer4, frame.posicaoYplayer4);
                    mudaCor(12);
                    strncpy(raquetePlayer2, player4.raquete, player4.tamanho);
                    raquetePlayer2[player4.tamanho] = '\0';
                    puts(raquetePlayer2);
                }
                mudaCor(15);
                for(i = 0; i < 5; i++) {
                    if(frame.posicaoXbola[i] != -1) {
                        setCursor(frame.posicaoXbola[i], frame.posicaoYbola[i]);
                        printf("0");
                    }
                }
                for(i = 0; i < 5; i++) {
                    posicaoXbolaAnt[i] = frame.posicaoXbola[i];
                    posicaoYbolaAnt[i] = frame.posicaoYbola[i];
                }
                posicaoXplayer1Ant = frame.posicaoXplayer1;
                posicaoYplayer1Ant = frame.posicaoYplayer1;
                posicaoXplayer2Ant = frame.posicaoXplayer2;
                posicaoYplayer2Ant = frame.posicaoYplayer2;
                if(player3.posXPlayer1 != INATIVA)posicaoXplayer3Ant = frame.posicaoXplayer3;
                if(player3.posYPlayer1 != INATIVA)posicaoYplayer3Ant = frame.posicaoYplayer3;
                if(player4.posXPlayer2 != INATIVA)posicaoXplayer4Ant = frame.posicaoXplayer4;
                if(player4.posYPlayer2 != INATIVA)posicaoYplayer4Ant = frame.posicaoYplayer4;
                setCursor(0, 0);
                Sleep(1000/20);
            }
        }
        fclose(replay);
    }
    else {
        printf("Nao existe replay salvo!");
    }
}
