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
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
    setlinestyle(0,0,3);
    /// ----- CARGA DE IMAGENES -------------------------------------------------------------------------
    SPRITE *cargaSp=NULL;//variable para cargar la imagen.

    ///Requerimientos para la funcion getimage().
    void *jugador, *plant, *mosca, *explosive, *pesticida, *sun;         //Apuntadores a void para cargar el sprite.
    int imgsize;        // entero para valor de la imagen
    imgsize=imagesize(555, 55, 600, 95);    // Image size.
    /// reservar memoria para la imagen.
    jugador=malloc(imgsize);    plant=malloc(imgsize);
    mosca=malloc(imgsize);      explosive=malloc(imgsize);
    pesticida=malloc(imgsize);  sun=malloc(imgsize);

    outtextxy(530, 600, "CARGANDO...");

    abrirSprite(cargaSp, "player1");
    delay(900);
    getimage(555, 55, 600, 95, jugador);  /// -----> getimage

    abrirSprite(cargaSp, "mosca");
    delay(900);
    getimage(555, 55, 600, 95, mosca);

    abrirSprite(cargaSp, "plant");
    delay(900);
    getimage(555, 55, 600, 95, plant);

    abrirSprite(cargaSp, "explosive");
    delay(900);
    getimage(555, 55, 600, 95, explosive);

    abrirSprite(cargaSp, "pesticida");
    delay(900);
    getimage(555, 55, 600, 95, pesticida);

    abrirSprite(cargaSp, "sun");
    delay(900);
    getimage(555, 55, 600, 95, sun);

    cleardevice();
    ///---------------------------------------------------------------------------------------------------

    /// --- CREA MALLA --------------------------------------------------------------------------------
        TNodoM *head=creanodo(); ///Se crea el primer nodo (head)
        TNodoM *pM=head;              ///y se define otro apuntador que nos ayudara a iniciar al principio de la malla.

        creamalla(&head);   ///Se crea los nuevos nodos y los enlaces.
    /// --------------------------------------------------------------------------------------------------

    //funcion para imprimir el ambiente
    printEnvironmentWork(mx, my, texto);

    //Variables de tiempo.
    int start, end;
    //Inilizacion de variables.
    int verf=0, mousx, mousy;

    ///DIBUJAMALLA
    dibujaMalla(plant, explosive, sun);

    start=clock();


    /// TAMAÑO DE LA IMAGEN ancho 54 - alto 52
    Ticono player;
    player.psnodo=pM;
    player.cx=65;   player.cy=85;

    int page=1,tr, cxant=0, cyant=0;


    do{


        if(tr=='h' && player.psnodo->right)
            putimage(player.cx+54,player.cy, plant, COPY_PUT);

        //funcion que imprime el tiempo
        printtime(start);

        if(kbhit()){
            cxant=player.cx;
            cyant=player.cy;
            setfillstyle(4,BLACK);
            bar(cxant, cyant, cxant+40, cyant+40);
        }

        //movimiento del sprite
        tr=movimiento(&player.psnodo, &player.cx, &player.cy, jugador);
        // - Esta parte verifica si el usuario no selecciona el boton exit -----------------------------
        getmouseclick(WM_LBUTTONDOWN, mousx, mousy);
        if( mousx > mx/8-90 && mousy>my/8+530 && mousx<mx/8+20 && mousy<my/8+560 )
            verf=1;
        //-----------------------------------------------------------------------------------------------

    }while(verf!=1);
    /*int pass=0;

    pass=nivel1();

    if(pass==1){
        pass=nivel2()
        if(pass==1){
            pass=nivel3();
        }
    }*/

    ///Libera memoria de la imagen.
    free(jugador);free(plant);free(sun);
    free(pesticida);free(mosca);free(explosive);


    head=NULL;  /// Libera memoria de
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

    outtextxy(590, 30, "1PLAYER:"); //Etiqueta player.;
    outtextxy(700, 30, texto);  //Nombre del jugador.
    //Area de juego.
    rectangle(60, 80, 1140, 600);
/*- Barra Exit. -----------------------------------------------------------------*/

    rectangle(mx/8-90, my/8+530, mx/8+20, my/8+560);
    outtextxy(mx/8-60, my/8+535, "exit");
/* ------------------------------------------------------------------------------*/

}
