typedef struct mapa {
    int linhas;
    int colunas;
    int borda;
    int mapa[40][81];
} MAPA;

void carregaMapaOnePlayer(char nomeMapa[], MAPA *mapa) {
    FILE *mapaFile;
    int i,j;
    if(mapaFile = fopen(nomeMapa, "r")) {
        fscanf(mapaFile, "%d %d %d ", &mapa->linhas, &mapa->colunas, &mapa->borda);
        for (i = 0; i < mapa->linhas; i++) {
                for(j = 0; j < mapa->colunas; j++) {
                    fscanf(mapaFile, "%d", &mapa->mapa[i][j]);
                }
        }
        fclose(mapaFile);
    }
}
