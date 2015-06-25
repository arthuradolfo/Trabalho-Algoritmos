int pausaEd(char nome[], MAPA *mapaEd);
int editarMapa(char nome[], MAPA* mapaEd);
int salvarMapa(char nome[], MAPA* mapaEd);
int menuEdicao();

//carrega o mapa cujo o nome foi inserido pelo usuario e depois leva pra edicao
int abrirMapaEd(){
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
    return 1;
}

//cria um mapa novo com os dados inseridos pelo usuario e leva para a edicao
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
    return 1;
}

//salva o mapa
int salvarMapa(char nome[], MAPA* mapaEd){
    system("cls");
    char novoNome[30];
    strcpy(novoNome,nome);
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
//edita o mapa
int editarMapa(char nome[], MAPA* mapaEd){
    printf("'ESC' = Pausar edicao _'B' = Inserir objeto_'N' = Deletar objeto _______________");
    printaMapa(mapaEd);
    printf("________________________________________________________________________________");

    setCursor(0, 0);
    int posx = 1, posy = 2;
    setCursor(posx,posy);
    while(!GetAsyncKeyState(VK_ESCAPE)){
        //se nao existir obstaculo no mapa carregado, apaga o lugar
        if(mapaEd->mapa[posy-1][posx] == 0){
            setCursor(posx,posy);
            printf(" ");
        }else {//se existir, escreve o bloco
            setCursor(posx,posy);
            printf("%c",219);
        }

        //se clicar B poem um obstaculo
        if(GetAsyncKeyState(0x42)){// 0x42 é letra B
             mapaEd->mapa[posy-1][posx] = 1;
        }

        //se clicar N, tira o obstaculo
        if(GetAsyncKeyState(0x4E)){// 0x42 é letra N
             mapaEd->mapa[posy-1][posx] = 0;
        }

        //mexe o posicionador de blocos
        if(GetAsyncKeyState(VK_UP) && posy-1 != 1) posy--;
        if(GetAsyncKeyState(VK_DOWN) && posy+1 != mapaEd->linhas + 1 -1) posy++;
        if(GetAsyncKeyState(VK_RIGHT) && posx+1 != mapaEd->colunas-1) posx++;
        if(GetAsyncKeyState(VK_LEFT) && posx-1 != 0) posx--;

        //se clicar B poem um obstaculo
        if(GetAsyncKeyState(0x42)){// 0x42 é letra B
             mapaEd->mapa[posy-1][posx] = 1;
        }
        //se clicar N tira um obstaculo
        if(GetAsyncKeyState(0x4E)){// 0x42 é letra N
             mapaEd->mapa[posy-1][posx] = 0;
        }

        setCursor(posx,posy);
        printf("O");
        Sleep(100);
    }
    system("cls");
    pausaEd(nome, mapaEd);
    return 1;
}

//pausa durante a edicao de mapa
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

//menu principal da edicao
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
            return 1;
            break;

        case 2:
            newMapa();
            return 1;
            break;

        case 3:
            return 1;
            break;
    }
    return 1;
}

