typedef struct mapa {
    int linhas;
    int colunas;
    int borda;
    int mapa[40][81];
} MAPA;

void desenhaLogo();
void printaMapa(MAPA *mapa);

//funcao para mudar a cor do que sera escrito
void mudaCor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//funcao para posicionar o cursor
void setCursor(int x, int y) {
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(screen, coordinate);
}
//funcao que carrega mapas para uma structure MAPA
void carregaMapaOnePlayer(char nomeMapa[], MAPA *mapa) {

    FILE *mapaFile;
    int i,j;
    if((mapaFile = fopen(nomeMapa, "r"))) {
        //testamos se ha os tres inteiros no inicio do arquivo (padrao pessoal do jogo)
        //mas se nao tiver entao atribuimos os valores padroes
        if(fscanf(mapaFile, "%d %d %d ", &mapa->linhas, &mapa->colunas, &mapa->borda) != 3){
            fseek(mapaFile,0,SEEK_SET);
            mapa->linhas = 40;
            mapa->colunas = 80;
            mapa->borda = 186;
        }
        //leitura do desenho do mapa
        for (i = 0; i < mapa->linhas; i++) {
                for(j = 0; j < mapa->colunas; j++) {
                    char buff;
                    fscanf(mapaFile, " %c ", &buff);
                    //MAPA.mapa é uma matriz de inteiros
                    //1 é barreira e 0 é espaço livre
                    if(buff == 'X') mapa->mapa[i][j] = 1;
                    if(buff == '_') mapa->mapa[i][j] = 0;
                }
        }
        fclose(mapaFile);
    }
}

void carregaMapaEdicao(char nomeMapa[], MAPA *mapa){
    //igual ao carregaMapaOnePlayer
    FILE *mapaFile;
    int i,j;
    if((mapaFile = fopen(nomeMapa, "r"))) {
        if(fscanf(mapaFile, "%d %d %d ", &mapa->linhas, &mapa->colunas, &mapa->borda) != 3){
            fseek(mapaFile,0,SEEK_SET);
            mapa->linhas = 40;
            mapa->colunas = 80;
            mapa->borda = 186;
        }
        for (i = 0; i < mapa->linhas; i++) {
                for(j = 0; j < mapa->colunas; j++) {
                    char buff;
                    fscanf(mapaFile, " %c ", &buff);
                    if(buff == 'X') mapa->mapa[i][j] = 1;
                    if(buff == '_') mapa->mapa[i][j] = 0;
                }
        }
        fclose(mapaFile);
    }
}
