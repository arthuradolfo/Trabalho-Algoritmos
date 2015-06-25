typedef struct frame {
    int idMapa; // qual mapa esta sendo jogado
    int posicaoXplayer1; // posicao em x do player 1
    int posicaoYplayer1; // posicao em y do player 1
    int posicaoXplayer2; // posicao em x do player 2
    int posicaoYplayer2; // posicao em y do player 2
    int posicaoXplayer3; // posicao em x do player 3
    int posicaoYplayer3; // posicao em y do player 3
    int posicaoXplayer4; // posicao em x do player 4
    int posicaoYplayer4; // posicao em y do player 4
    int posicaoXbola[MAXBOLAS]; // posicao em x de cada bola
    int posicaoYbola[MAXBOLAS]; // posicao em y de cada bola
    int pontuacaoPlayer1; // pontuacao do player1
    int pontuacaoPlayer2; // pontuacao do player2
    int nivel; // nivel (REPBRUTAL para modo brutal e REP2PLAYER para modo two player)
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
    //abre arquivo replay, que eh padrao do jogo e portanto existe obrigatoriamente
    if((replay  = fopen("replay", "rb"))) {

        NIVEL st_nivel;
        FILE* arqNivel;

        //abre arquivo o arquivo do nivel corrspondente ao frame
        arqNivel = fopen("arqNiv","rb");
        fseek(arqNivel,(frame.nivel-1)*sizeof(NIVEL),SEEK_SET);
        fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
        fclose(arqNivel);

        //atribui os valores pra cada player correspondentes ao frame
        PLAYER1 player1 = {frame.posicaoXplayer1, frame.posicaoYplayer1, st_nivel.tamPlayer1, st_nivel.velPlayer1, st_nivel.velPlayer1, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
        PLAYER2 player2 = {frame.posicaoXplayer2, frame.posicaoYplayer2, st_nivel.tamPlayer2, st_nivel.velPlayer2, st_nivel.velPlayer1, 0, 0, st_nivel.IAPlayer2, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
        PLAYER1 player3 = {frame.posicaoXplayer3, frame.posicaoYplayer3, 20, 0, 0, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
        PLAYER2 player4 = {frame.posicaoXplayer4, frame.posicaoYplayer4, 20, 0, 0, 0, 0, 0, 0, 0, {219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219}};
        char raquetePlayer1[player1.tamanho+1], raquetePlayer2[player2.tamanho+1], raquetePlayerApaga1[player1.tamanho+1], raquetePlayerApaga2[player2.tamanho+1];

        //salva as caracteristicas do frame anterior
        int idMapaAnt, pontuacaoPlayer1Ant, pontuacaoPlayer2Ant, posicaoXplayer1Ant, posicaoXplayer2Ant ,posicaoXplayer3Ant, posicaoXplayer4Ant, posicaoYplayer1Ant, posicaoYplayer2Ant ,posicaoYplayer3Ant, posicaoYplayer4Ant, posicaoXbolaAnt[5], posicaoYbolaAnt[5];

        while(!feof(replay)) {
            if(fread(&frame, sizeof(FRAME), 1, replay) == 1) {
                //abre arquivo o arquivo do nivel corrspondente ao frame
                arqNivel = fopen("arqNiv","rb");
                fseek(arqNivel,(frame.nivel-1)*sizeof(NIVEL),SEEK_SET);
                fread(&st_nivel,sizeof(NIVEL),1,arqNivel);
                fclose(arqNivel);

                //atribui os valores pra cada player correspondentes ao frame

                player3.posXPlayer1 = frame.posicaoXplayer3;
                player3.posYPlayer1 = frame.posicaoYplayer3;
                player4.posXPlayer2 = frame.posicaoXplayer4;
                player4.posYPlayer2 = frame.posicaoYplayer4;
                player1.dirX = st_nivel.velPlayer1;
                player2.dirX = st_nivel.velPlayer2;

                //valores padrao de tamanho dos players pros determinados tipos de jogo
                if(frame.nivel == REP2PLAYER || frame.nivel == REPBRUTAL) player1.tamanho = 20;
                else player1.tamanho = st_nivel.tamPlayer1;
                if(frame.nivel == REP2PLAYER || frame.nivel == REPBRUTAL) player2.tamanho = 20;
                else player2.tamanho = st_nivel.tamPlayer2;

                if(idMapaAnt != frame.idMapa) {//se nao forem igual tem que mudar o mapa do replay
                    system("cls");
                }

                if(primeira == 1) {//se for o primeiro frame
                    //posicao antiga recebe a posicao atual logo no inicio do loop

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
                    primeira = 0; // nao acontece mais esse loop
                }

                //string para apagar raquete player2
                for(i = 0; i <= player2.tamanho; i++) {
                        if(i == player2.tamanho) raquetePlayerApaga2[i] = '\0';
                        else raquetePlayerApaga2[i] = ' ';
                }

                //apaga o local antigo do player 2
                setCursor(posicaoXplayer2Ant, posicaoYplayer2Ant);
                puts(raquetePlayerApaga2);

                //string pra apagar raquete do player 4
                if(player4.posXPlayer2 != INATIVA) {
                    for(i = 0; i <= player4.tamanho; i++) {
                        if(i == player4.tamanho) raquetePlayerApaga2[i] = '\0';
                        else raquetePlayerApaga2[i] = ' ';
                    }
                    //apaga
                    setCursor(posicaoXplayer4Ant, posicaoYplayer4Ant);
                    puts(raquetePlayerApaga2);
                }

                //strin para apagar raquete do player1
                for(i = 0; i <= player1.tamanho; i++) {
                        if(i == player1.tamanho) raquetePlayerApaga1[i] = '\0';
                        else raquetePlayerApaga1[i] = ' ';
                }
                //apaga
                setCursor(posicaoXplayer1Ant, posicaoYplayer1Ant);
                puts(raquetePlayerApaga1);

                //string para apagar raquete do player 3
                if(player3.posXPlayer1 != INATIVA) {
                    for(i = 0; i <= player3.tamanho; i++) {
                            if(i == player3.tamanho) raquetePlayerApaga1[i] = '\0';
                            else raquetePlayerApaga1[i] = ' ';
                    }
                    //apaga
                    setCursor(posicaoXplayer3Ant, posicaoYplayer3Ant);
                    puts(raquetePlayerApaga1);
                }

                for(i = 0; i < 5; i++) {//apaga cada bola
                    if(frame.posicaoXbola[i] != -1) {
                        setCursor(posicaoXbolaAnt[i], posicaoYbolaAnt[i]);
                        printf(" ");
                    }
                }

                //se mudar a pontuaçao do player 2, ou o mapa, tem que printar o score atualizado
                if(pontuacaoPlayer2Ant != frame.pontuacaoPlayer2 || idMapaAnt != frame.idMapa){
                    setCursor(0, 0);
                    pontuacaoPlayer2Ant = frame.pontuacaoPlayer2;//nova pontuacao antiga
                    printf("SCORE: %3d_____________________________________________________________NIVEL: %2d", frame.pontuacaoPlayer2, frame.nivel);
                }

                setCursor(0, 1);//printa depois do score (por isso o 1)

                //se mudar o mapa, tem que printar ele de novo
                if(idMapaAnt != frame.idMapa) {
                    idMapaAnt = frame.idMapa;
                    itoa(frame.idMapa, idMapa, 10);
                    strcpy(qualMapa, "maps");
                    strcat(qualMapa, idMapa);
                    strcat(qualMapa, ".txt");
                    carregaMapaOnePlayer(qualMapa, &mapa);
                    printaMapa(&mapa);
                }

                //se mudar, atualiza score do player 1
                if(pontuacaoPlayer1Ant != frame.pontuacaoPlayer1 || idMapaAnt != frame.idMapa){
                    pontuacaoPlayer1Ant = frame.pontuacaoPlayer1;
                    setCursor(0, mapa.linhas+1);
                    printf("SCORE: %3d_____________________________________________________________________", frame.pontuacaoPlayer1);
                }

                if(frame.nivel == REPBRUTAL) {//no brutal mode tem uma linha que tem que ser printada se for brutal
                    setCursor(1, (mapa.linhas/2)+1);
                    printf("------------------------------------------------------------------------------");
                }

                setCursor(frame.posicaoXplayer1, frame.posicaoYplayer1);
                mudaCor(9);

                //string para printar player1 e printamento do player1
                strncpy(raquetePlayer1, player1.raquete, player1.tamanho);
                raquetePlayer1[player1.tamanho] = '\0';
                puts(raquetePlayer1);

                if(player3.posXPlayer1 != INATIVA) {//se tiver player 3, printa ele
                    setCursor(frame.posicaoXplayer3, frame.posicaoYplayer3);
                    mudaCor(9);
                    strncpy(raquetePlayer1, player3.raquete, player3.tamanho);
                    raquetePlayer1[player3.tamanho] = '\0';
                    puts(raquetePlayer1);
                }

                //printa o player 2
                setCursor(frame.posicaoXplayer2, frame.posicaoYplayer2);
                mudaCor(12);
                strncpy(raquetePlayer2, player2.raquete, player2.tamanho);
                raquetePlayer2[player2.tamanho] = '\0';
                puts(raquetePlayer2);


                if(player4.posXPlayer2 != INATIVA) {//se tiver player 4, printa ele
                    setCursor(frame.posicaoXplayer4, frame.posicaoYplayer4);
                    mudaCor(12);
                    strncpy(raquetePlayer2, player4.raquete, player4.tamanho);
                    raquetePlayer2[player4.tamanho] = '\0';
                    puts(raquetePlayer2);
                }

                //printa cada bola
                mudaCor(15);
                for(i = 0; i < 5; i++) {
                    if(frame.posicaoXbola[i] != INATIVA) {
                        setCursor(frame.posicaoXbola[i], frame.posicaoYbola[i]);
                        printf("0");
                    }
                }

                //atualiza as posicoes antigas das bolas
                for(i = 0; i < 5; i++) {
                    posicaoXbolaAnt[i] = frame.posicaoXbola[i];
                    posicaoYbolaAnt[i] = frame.posicaoYbola[i];
                }

                //atualiza as posições antigas dos players
                //(se eles estiverem no jogo)
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
