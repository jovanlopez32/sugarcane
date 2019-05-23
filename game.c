#include <stdio.h>
#include <graphics.h>
#include <time.h>

#include "malla.h"
#include "sprites.h"


typedef char string [20];

//Estructura para sprites del juego.
typedef struct{
    int cx, cy;     ///Coordenada del icono.
    TNodoM *psnodo; ///Posicion de nodo.
}Ticono;

//prototipos.
void printtime(int init);
void printEnvironmentWork(int mx, int my, string texto);
int creamalla(TNodoM **cabeza);

int juega(int mx, int my, string texto){

    setcolor(WHITE);
    //Variables de tiempo.
    int start, end;
    //Inilizacion de variables.
    int verf=0, mousx, mousy;


     /// ----- carga imagenes -------------------------------------------------------------------------

    SPRITE *cargaSp=NULL;//variable para cargar la imagen.

    ///Requerimientos para la funcion getimage().
    void *plyr;         //Apuntadores a void para cargar el sprite.
    int imgsize;        // entero para valor de la imagen
    imgsize=imagesize(555, 55, 600, 95);    // Image size.
    plyr=malloc(imgsize); /// reservar memoria para la imagen.

    outtextxy(530, 600, "CARGANDO...");
    abrirSprite(cargaSp, "player1");
    delay(900);
    getimage(555, 55, 600, 95, plyr);  /// -----> getimage
    abrirSprite(cargaSp, "mosca");
    delay(900);
    abrirSprite(cargaSp, "plant");
    delay(900);
    abrirSprite(cargaSp, "explosive");
    delay(900);
    abrirSprite(cargaSp, "pesticida");
    delay(900);
    abrirSprite(cargaSp, "sun");
    delay(900);

    cleardevice();
    ///---------------------------------------------------------------------------------------------------

    start=clock();

    // --- crea malla --------------------------------------------------------------------------------
        TNodoM *head=creanodo(); ///Se crea el primer nodo (head)
        TNodoM *pM=head;              ///y se define otro apuntador que nos ayudara a iniciar al principio de la malla.

        creamalla(&head);   ///Se crea los nuevos nodos y los enlaces.
    //--------------------------------------------------------------------------------------------------


    int ix=65, iy=85; /// ancho 54 - alto 52 TAMAÑO DE LA IMAGEN
    Ticono player;
    player.psnodo=pM;


    //funcion para imprimir el ambiente
    printEnvironmentWork(mx, my, texto);


    do{

        //funcion que imprime el tiempo
        printtime(start);
        //movimiento del sprite
        movimiento(&player.psnodo, &ix, &iy, plyr);
        delay(20);



        // - Esta parte verifica si el usuario no selecciona el boton exit -----------------------------
        getmouseclick(WM_LBUTTONDOWN, mousx, mousy);
        if( mousx > mx/8-90 && mousy>my/8+530 && mousx<mx/8+20 && mousy<my/8+560 )
            verf=1;
        //------------------------------------------------------------------------------------------------

    }while(verf!=1);

    free(plyr); ///libera memoria de la imagen.

    head=NULL;  /// libera memoria de
    free(head); /// la mallla.


    end=clock();
    return verf;
}




void printtime(int init){

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

void printEnvironmentWork(int mx, int my, string texto){

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
    //return getactivepage();

}
