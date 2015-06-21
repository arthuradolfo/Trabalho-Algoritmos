typedef struct frame {
    int idMapa;
    int posicaoXplayer1;
    int posicaoYplayer1;
    int posicaoXplayer2;
    int posicaoYplayer2;
    int posicaoXbola[5];
    int posicaoYbola[5];
    int pontuacaoPlayer1;
    int pontuacaoPlayer2;
    int nivel;
} FRAME;
void salvaReplay(int idMapa, PLAYER1 *player1, PLAYER2 *player2, BOLA *bola, int pontuacaoPlayer1, int pontuacaoPlayer2, int nivel, FILE *replay);
void rodaReplay();

void salvaReplay(int idMapa, PLAYER1 *player1, PLAYER2 *player2, BOLA *bola, int pontuacaoPlayer1, int pontuacaoPlayer2, int nivel, FILE *replay) {
    int i;
    FRAME frame = {0, 0, 0, 0, 0, {-1, -1, -1, -1, -1}, {-1, -1, -1, -1, -1}, 0, 0, 0};
    frame.idMapa = idMapa;
    frame.posicaoXplayer1 = player1->posXPlayer1;
    frame.posicaoYplayer1 = player1->posYPlayer1;
    frame.posicaoXplayer2 = player2->posXPlayer2;
    frame.posicaoYplayer2 = player2->posYPlayer2;
    for(i = 0; i < bola->numBolas; i++) {
        frame.posicaoXbola[i] = bola->posX[i];
        frame.posicaoYbola[i] = bola->posY[i];
    }
    frame.pontuacaoPlayer1 = pontuacaoPlayer1;
    frame.pontuacaoPlayer2 = pontuacaoPlayer2;
    frame.nivel = nivel;
    fwrite(&frame, sizeof(FRAME), 1, replay);
    fflush(replay);
}

void rodaReplay() {
    FRAME frame;
    MAPA mapa;
    char qualMapa[30] = "maps";
    char idMapa[5];
    int i, primeira = 1;
    FILE *replay;
    replay  = fopen("replay", "rb");
    NIVEL st_nivel;
    FILE* arqNivel;
    arqNivel = fopen("arqNiv","rb");
    fseek(arqNivel,(frame.nivel-1)*sizeof(NIVEL),SEEK_SET);
    fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
    fclose(arqNivel);
    PLAYER1 player1 = {frame.posicaoXplayer1, frame.posicaoYplayer1, st_nivel.tamPlayer1, st_nivel.velPlayer1, 0, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    PLAYER2 player2 = {frame.posicaoXplayer2, frame.posicaoYplayer2, st_nivel.tamPlayer2, st_nivel.velPlayer2, 0, 0, st_nivel.IAPlayer2, 0, {0, 0, 0}, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
    char raquetePlayer1[player1.tamanho+1], raquetePlayer2[player2.tamanho+1], raquetePlayerApaga1[player1.tamanho+1], raquetePlayerApaga2[player2.tamanho+1];
    int idMapaAnt, pontuacaoPlayer1Ant, pontuacaoPlayer2Ant, posicaoXplayer1Ant, posicaoXplayer2Ant, posicaoXbolaAnt[5], posicaoYbolaAnt[5];
    while(!feof(replay)) {
        if(fread(&frame, sizeof(FRAME), 1, replay) == 1) {
            arqNivel = fopen("arqNiv","rb");
            fseek(arqNivel,(frame.nivel-1)*sizeof(NIVEL),SEEK_SET);
            fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
            fclose(arqNivel);
            player1.dirX = st_nivel.velPlayer1;
            player2.dirX = st_nivel.velPlayer2;
            player1.tamanho = st_nivel.tamPlayer1;
            player2.tamanho = st_nivel.tamPlayer2;
            if(idMapaAnt != frame.idMapa) {
                system("cls");
            }
            if(primeira == 1) {
                posicaoXplayer1Ant = frame.posicaoXplayer1;
                posicaoXplayer2Ant = frame.posicaoXplayer2;
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
            setCursor(posicaoXplayer2Ant, frame.posicaoYplayer2); // altera a posicao do cursor para o da bola
            puts(raquetePlayerApaga2); // imprime um espaco sobre a bola
            for(i = 0; i <= player1.tamanho; i++) {
                    if(i == player1.tamanho) raquetePlayerApaga1[i] = '\0';
                    else raquetePlayerApaga1[i] = ' ';
            }
            setCursor(posicaoXplayer1Ant, frame.posicaoYplayer1); // altera a posicao do cursor para o da bola
            puts(raquetePlayerApaga1); // imprime um espaco sobre a bola
            for(i = 0; i < 5; i++) {\
                if(frame.posicaoXbola[i] != -1) {
                    setCursor(posicaoXbolaAnt[i], posicaoYbolaAnt[i]); // altera a posicao do cursor para o da bola
                    printf(" "); // imprime um espaco sobre a bola
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
                setCursor(0, frame.posicaoYplayer1+1);
                printf("SCORE: %3d_____________________________________________________________________", frame.pontuacaoPlayer1);
            }
            setCursor(frame.posicaoXplayer1, frame.posicaoYplayer1);
            mudaCor(9);
            strncpy(raquetePlayer1, player1.raquete, player1.tamanho);
            raquetePlayer1[player1.tamanho] = '\0';
            puts(raquetePlayer1);
            setCursor(frame.posicaoXplayer2, frame.posicaoYplayer2);
            mudaCor(12);
            strncpy(raquetePlayer2, player2.raquete, player2.tamanho);
            raquetePlayer2[player2.tamanho] = '\0';
            puts(raquetePlayer2);
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
            posicaoXplayer2Ant = frame.posicaoXplayer2;
            setCursor(0, 0);
            Sleep(1000/20);
        }
    }
    fclose(replay);
}
