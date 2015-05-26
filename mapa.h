typedef struct mapa {
    int linhas;
    int colunas;
    int borda;
    int mapa[80][40];
} MAPA;

void carregaMapaOnePlayer(char nomeMapa[], MAPA *mapa) {
    FILE *mapaFile;
    int i,j;
    system("cls");
    if(mapaFile = fopen(nomeMapa, "r")) {
        setCursor(10, 10);
        fscanf(mapaFile, "%d %d %d", &mapa->linhas, &mapa->colunas, &mapa->borda);
        printf("%d %d %d\n", mapa->linhas, mapa->colunas, mapa->borda);
        Sleep(1000);
        for (i = 0; i < mapa->linhas; i++) {
            for(j = 0; j < mapa->colunas; j++) {
                fscanf(mapaFile, "%d", &mapa->mapa[i][j]);
            }
            //printf("\n");
        }
        fclose(mapaFile);
    }
    setCursor(10, 10);
}
