#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>


int records(int mx, int my){

    FILE *abrirR;

    abrirR=fopen("RecordSC.txt", "r");

    if(abrirR){
        char mostrar[50], buffer[20];
        int espacio=50;
        float comp;
        outtextxy(100, 180, "RECORDS");
        while(!feof(abrirR)){

                fscanf(abrirR, " %s ------------------------ %f \n", buffer, &comp);

                sprintf(mostrar, "%s ------------------------ %f \n", buffer, comp);

                outtextxy(200, 210+espacio, mostrar);
                espacio+=50;

                //printf(" %s ---- %f", texto, puntos);
        }



    }



    int mousx, mousy, verf=-1;
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



