#include <stdio.h>
typedef struct nivel{
    int velPlayer1;
    int velPlayer2;
    int tamPlayer1;
    int tamPlayer2;
    int velBola;
    int IAPlayer2;
}NIVEL;

int main(int argc,char** argv){
    FILE* arqNiv;
    arqNiv = fopen("arqNiv","r+b");
    NIVEL novo;

    if(argc == 1){
        while(!feof(arqNiv)){
            if(fread(&novo,sizeof(NIVEL),1,arqNiv)){
                printf("%d %d %d %d %d %d\n",novo.velPlayer1,novo.velPlayer2,novo.tamPlayer1,novo.tamPlayer2,novo.velBola,novo.IAPlayer2);
            }
        }
        printf("%d niveis prontos!\n",ftell(arqNiv)/sizeof(NIVEL));
    }else if(argc==7){

        novo.velPlayer1 = atoi(argv[1]);
        novo.velPlayer2 = atoi(argv[2]);
        novo.tamPlayer1 = atoi(argv[3]);
        novo.tamPlayer2 = atoi(argv[4]);
        novo.velBola = atoi(argv[5]);
        novo.IAPlayer2 = atoi(argv[6]);

/*
        int i;

        for(i=0;i<3;i++){
        novo.velPlayer1 = 1;
        novo.velPlayer2 = 1;
        novo.tamPlayer1 = 25 - 2*i;
        novo.tamPlayer2 = 10 + 2*i;
        novo.velBola = 3;
        novo.IAPlayer2 = 11;

        fseek(arqNiv, 0 ,SEEK_END);
        if(fwrite(&novo,sizeof(NIVEL),1,arqNiv))
            printf("O nivel %d foi criado com sucesso!\n",ftell(arqNiv)/sizeof(NIVEL));
        }
        for(i=1;i<=4;i++){
        novo.velPlayer1 = 2;
        novo.velPlayer2 = 3;
        novo.tamPlayer1 = 21 - 2*i;
        novo.tamPlayer2 = 14 + 2*i;
        novo.velBola = 3;
        novo.IAPlayer2 = 11;

        fseek(arqNiv, 0 ,SEEK_END);
        if(fwrite(&novo,sizeof(NIVEL),1,arqNiv))
            printf("O nivel %d foi criado com sucesso!\n",ftell(arqNiv)/sizeof(NIVEL));
        }
        for(i=1;i<=3;i++){
            novo.velPlayer1 = 3;
            novo.velPlayer2 = 2;
            novo.tamPlayer1 = 13 - i;
            novo.tamPlayer2 = 22 + i;
            novo.velBola = 3;
            novo.IAPlayer2 = 11;

            fseek(arqNiv, 0 ,SEEK_END);
            if(fwrite(&novo,sizeof(NIVEL),1,arqNiv))
                printf("O nivel %d foi criado com sucesso!\n",ftell(arqNiv)/sizeof(NIVEL));
        }
*/
    }
    fclose(arqNiv);
    //fseek(arqNiv,sizeof(NIVEL),SEEK_SET);
    //fread(&novo,sizeof(NIVEL),1,arqNiv);
    //printf("%d",novo.tamPlayer1);
    //fclose(arqNiv);
}
