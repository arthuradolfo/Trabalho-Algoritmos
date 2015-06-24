int pausaEd(char nome[], MAPA *mapaEd);
int editarMapa(char nome[], MAPA* mapaEd);
int abrirMapaEd(char from){
    system("cls");
    clearBuff();
    char nomeMapaEd[30];
    setCursor(0,0);

    printf("CARREGAR MAPA\n");
    printf("Insira o nome do mapa:\n");
    clearBuff();
    scanf("%s",nomeMapaEd);
    MAPA mapaEd;
    carregaMapaEdicao(nomeMapaEd, &mapaEd);
    system("cls");
    editarMapa(nomeMapaEd, &mapaEd);
}
int newMapa(){
    system("cls");
    clearBuff();
    MAPA novoMapa;
    char nomeNovoMapa[30];
    printf("Defina um nome para o mapa");
    scanf("%s",nomeNovoMapa);
    clearBuff();
    printf("Defina a altura do mapa: \n");
    scanf("%d",&novoMapa.linhas);
    printf("Defina a largura do mapa: \n");
    scanf("%d",&novoMapa.colunas);
    printf("Defina o tipo de borda: (se estiver em duvida, ponha 186)\n");
    scanf("%d",&novoMapa.borda);
    int i,j;
    for(i=0;i<novoMapa.linhas;i++){
        for(j=0;j<novoMapa.colunas;j++){
            if(j==0 || j==novoMapa.colunas - 1) novoMapa.mapa[i][j] = 1;
            else novoMapa.mapa[i][j] = 0;
        }
    }
    if(salvarMapa(nomeNovoMapa,&novoMapa)){
        system("cls");
        editarMapa(nomeNovoMapa,&novoMapa);
    }
}
int salvarMapa(char nome[], MAPA* mapaEd){
    system("cls");
    //clearBuff();
    char novoNome[30];
    strcpy(novoNome,nome);
    //printf("Confirme ou troque o nome para o mapa! O nome atual eh %s\n",nome);
    //clearBuff();
    //fflush(stdin);
    //scanf("%s",novoNome);
    FILE* arqMapa;
    int i,j;
    if( (arqMapa = fopen(novoNome,"w+") ) ){
        fprintf(arqMapa,"%d %d %d\n", mapaEd->linhas, mapaEd->colunas, mapaEd->borda);
        for (i = 0; i < mapaEd->linhas; i++) {
            for(j = 0; j < mapaEd->colunas; j++) {
                if(mapaEd->mapa[i][j] == 1) fprintf(arqMapa,"X");
                if(mapaEd->mapa[i][j] == 0) fprintf(arqMapa,"_");
            }
            fprintf(arqMapa,"\n");
        }
        printf("O mapa foi salvo no arquivo %s!\n",novoNome);
        fclose(arqMapa);
        strcpy(nome,novoNome);
        Sleep(750);
    }else{
        printf("O arquivo não foi aberto. Desculpe, você perdeu tudo\n");
        return 0;
    }
    return 1;
}
int editarMapa(char nome[], MAPA* mapaEd){
    int i,j;
    printf("'ESC' = Pausar edicao _'B' = Inserir objeto_'N' = Deletar objeto _______________");
    printaMapa(mapaEd);
    printf("________________________________________________________________________________");
    setCursor(0, 0);
    int posx = 1, posy = 2;
    setCursor(posx,posy);
    while(!GetAsyncKeyState(VK_ESCAPE)){
        if(mapaEd->mapa[posy-1][posx] == 0){
            setCursor(posx,posy);
            printf(" ");
        }else {
            setCursor(posx,posy);
            printf("%c",219);
        }
        if(GetAsyncKeyState(0x42)){// 0x42 é letra B
             //mapaEd->mapa[posy-1][posx] = !mapaEd->mapa[posy-1][posx];
             mapaEd->mapa[posy-1][posx] = 1;
        }
        if(GetAsyncKeyState(0x4E)){// 0x42 é letra B
             //mapaEd->mapa[posy-1][posx] = !mapaEd->mapa[posy-1][posx];
             mapaEd->mapa[posy-1][posx] = 0;
        }
        if(GetAsyncKeyState(VK_UP) && posy-1 != 1) posy--;
        if(GetAsyncKeyState(VK_DOWN) && posy+1 != mapaEd->linhas + 1 -1) posy++;
        if(GetAsyncKeyState(VK_RIGHT) && posx+1 != mapaEd->colunas-1) posx++;
        if(GetAsyncKeyState(VK_LEFT) && posx-1 != 0) posx--;
        if(GetAsyncKeyState(0x42)){// 0x42 é letra B
             //mapaEd->mapa[posy-1][posx] = !mapaEd->mapa[posy-1][posx];
             mapaEd->mapa[posy-1][posx] = 1;
        }
        if(GetAsyncKeyState(0x4E)){// 0x42 é letra B
             //mapaEd->mapa[posy-1][posx] = !mapaEd->mapa[posy-1][posx];
             mapaEd->mapa[posy-1][posx] = 0;
        }
        setCursor(posx,posy);
        printf("O");
        Sleep(100);
    }
    system("cls");
    pausaEd(nome, mapaEd);
}

int pausaEd(char nome[], MAPA *mapaEd){
    char menuPausaEdicao[7][80] = { "                                   EDITAR                              ",
                              "                      ________________________________                 ",
                              "                     |                                |                ",
                              "                     |   Continuar                    |                ",
                              "                     |   Salvar como                  |                ",
                              "                     |   Sair da Edicao               |                ",
                              "                     |________________________________|                "
    };
    int i;
    for(i=0;i<7;i++) printf("%s\n",menuPausaEdicao[i]);
    int posXed = 50;
    int posYed = 3;
    GetAsyncKeyState(VK_RETURN);
    Sleep(500);
    while(!GetAsyncKeyState(VK_RETURN)) {
        setCursor(posXed, posYed);
        printf("<-");
        if(GetAsyncKeyState(VK_DOWN) && posYed < 5) {
            setCursor(posXed, posYed);
            printf("  ");
            posYed++;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_UP) && posYed > 3) {
            setCursor(posXed, posYed);
            printf("  ");
            posYed--;
            Sleep(100);
        }
        Sleep(1000/30);
    }
    posYed-=2;
    system("cls");
    switch(posYed){
        case 1:
            editarMapa(nome, mapaEd);
            break;

        case 2:
            salvarMapa(nome, mapaEd);
            system("cls");
            editarMapa(nome, mapaEd);
            break;

        case 3:
            menuEdicao();
            break;
    }
    return 1;
}
int menuEdicao(){
    system("cls");
    char menuEdicaoPrincipal[7][80] = { "                                   EDITAR                              ",
                              "                      ________________________________                 ",
                              "                     |                                |                ",
                              "                     |   Abrir Mapa                   |                ",
                              "                     |   Novo Mapa                    |                ",
                              "                     |   Menu Principal               |                ",
                              "                     |________________________________|                "
    };
    int i;
    for(i=0;i<7;i++) printf("%s\n",menuEdicaoPrincipal[i]);
    int posXed = 50;
    int posYed = 3;
    Sleep(500);
    while(!GetAsyncKeyState(VK_RETURN)) {
        setCursor(posXed, posYed);
        printf("<-");
        if(GetAsyncKeyState(VK_DOWN) && posYed < 5) {
            setCursor(posXed, posYed);
            printf("  ");
            posYed++;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_UP) && posYed > 3) {
            setCursor(posXed, posYed);
            printf("  ");
            posYed--;
            Sleep(100);

        }
        Sleep(1000/30);
    }
    posYed-=2;
    switch(posYed){
        case 1:
            abrirMapaEd('c');
            break;

        case 2:
            newMapa();
            break;

        case 3:
            return 1;
            break;
    }
}

