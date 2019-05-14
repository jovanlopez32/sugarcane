#include <stdio.h>
#include <graphics.h>
#include <time.h>

#include "malla.h"


typedef char string [20];

//prototipos.
void printtime(int init, int mx, int my);
int creamalla(TNodoM **cabeza);

int juega(int mx, int my, string texto){

    setcolor(WHITE);
    //Variables de tiempo.
    int start, end;
    //Inilizacion de variables.
    int verf=0, mousx, mousy;

/*- Dibuja ambiente: -------------------------------------------------------------*/

    setcolor(LIGHTGREEN);
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(590, 30, "1PLAYER:"); //Etiqueta player.
    setcolor(WHITE);
    outtextxy(700, 30, texto);  //Nombre del jugador.
    //Area de juego.
    rectangle(60, 80, 1140, 600);
/*- Barra Exit. -----------------------------------------------------------------*/
    setlinestyle(0,0,3);
    rectangle(mx/8-90, my/8+530, mx/8+20, my/8+560);
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
    outtextxy(mx/8-60, my/8+535, "exit");
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
/* ------------------------------------------------------------------------------*/
    start=clock();

    // --- crea malla --------------------------------------------------------------------------------
        TNodoM *head=creanodo(); ///Se crea el primer nodo (head)
        TNodoM *pM=head;              ///y se define otro apuntador que nos ayudara a iniciar al principio de la malla.

        creamalla(&head);   ///Se crea los nuevos nodos y los enlaces.
    //--------------------------------------------------------------------------------------------------

    ///-- BORRAR ES UN TEST (CUADRO)------- ///

    int icuadrox=60, icuadroy=80; /// ancho 54 - alto 52
    /** 100 ->
        97 <-
        115 v
        119 ^   **/

    do{
        //funcion que imprime el tiempo
        printtime(start, mx, my);

        testmalla(&pM, &icuadrox, &icuadroy);


        // - Esta parte verifica si el usuario no selecciona el boton exit -----------------------------
        getmouseclick(WM_LBUTTONDOWN, mousx, mousy);
        if( mousx > mx/8-90 && mousy>my/8+530 && mousx<mx/8+20 && mousy<my/8+560 )
            verf=1;
        //------------------------------------------------------------------------------------------------

    }while(verf!=1 );


    end=clock();

    return verf;
}




void printtime(int init, int mx, int my){

    int seg, act;
    char reloj[30];


    act=clock();
    seg=(act-init)/CLK_TCK;
    //printf("%i", seg);
    sprintf(reloj, "Time | %d : %d |", seg/60, seg%60);

    /*setfillstyle(1, 0);
    bar(30, 30, 200, 90);*/
    //settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(LIGHTGREEN);
    outtextxy(60, 30, reloj);

}
