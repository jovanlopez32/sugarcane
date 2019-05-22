
typedef struct{
    int renglones;
    int columnas;
    int **mtrx;
}SPRITE;

///----------------------------------Abre el sprite de un archivo binario-----------------------------///
int abrirSprite(SPRITE *spr, char nombre[20]){
    char res[20];

    int i, j;
    int ren, col;
    int r[50][50];

    // copia el nombre y le agrega la extension .sprite
    strcpy(res, nombre);
    strcat(res, ".sprite");

    FILE *arch;
    arch = fopen(res, "r");
    if(arch != NULL){
        // Lee el numero de columnas
        fread(&ren, sizeof(int), 1, arch);
        // Lee el numero de renglones
        fread(&col, sizeof(int), 1, arch);

        int mx=getmaxx(), my=getmaxy();

        // va leyendo elemento por elemento del arreglo
        for(i = 0; i < ren; i++){

            for(j = 0; j < col; j++){
                fread(&r[i][j], sizeof(int), 1, arch);
                 setfillstyle(SOLID_FILL,  r[i][j]);
                 bar(470+(10*j),250+(10*i), 470+20+(10*j),250+20+(10*i)); /*    Carga sprites en grande */
                 bar(550+(2*j), 50+(2*i), 550+20+(2*j), 50+20+(2*i)); /*    Carga sprites para captura [getimage] */
                 //printf("%i - %i - %i - %i\n", 20+(5*i),20+(5*j), 40+(5*i),40+(5*j));
                 //putpixel(i,j,r[i][j]);
            }
        }
        fclose(arch);
        return 1;
    }
    fclose(arch);
    return 0;
}
