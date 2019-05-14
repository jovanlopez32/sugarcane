#include <stdio.h>
#include <graphics.h>

int opcayuda(int mx, int my){
    /* Variable usada para mantener el ciclo activo */
    int mousx, mousy, verf=-1;

    //Coordenadas maximas divididas entre dos.
    mx=mx/2;
    my=my/2;
/* .:::: LEEE ARCHIVO DE TEXTO ::::. */

    char c[2];
    char cp;
    //Abriendo el achivo.
    FILE *HLPSC;
    HLPSC=fopen("HLPSC.txt", "rt");

    //Verifica si exite el archivo.
    if(HLPSC==NULL){                                        //Si no existe el archivo crea una nuevo archivo
        outtextxy(30, 30, ".:: No existe archivo ::.");
    }
    else{
        settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
        int i=0, j=0, tamx=150;
        while(!feof(HLPSC)){
            fscanf(HLPSC, "%c", c);
            outtextxy(15+i,150+j,c);
            if(!strcmp(c, "\n")){
                setcolor(WHITE);
                j+=25;
                i=0;
            }
            if(!strcmp(c, "\t")){
                i+=50;
                setcolor(GREEN);
            }

            tamx=textwidth(c);
            i+=tamx;
        }

    }




/* ...:::::: BOTON DE RETROCESO ::::::...   */


    //Boton de retroceso
    setfillstyle(SOLID_FILL,  GREEN);
    bar(mx/8-60, my/8, mx/8+90, my/8+30);
    outtextxy(mx/8-10, my/8+5, "BACK");


    //Verificacion del click.
    do{
        getmouseclick(WM_LBUTTONDOWN, mousx, mousy);

        if( mousx > mx/8-60 && mousy>my/8 && mousx<mx/8+90 && mousy<my/8+30 )
            verf=1;

    }while(verf == -1);

/* .:::::::::::::::::::::::::::::::::::::.   */

    return verf;

}
