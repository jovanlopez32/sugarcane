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
void printtime(int init, float *puntos);
void printEnvironmentWork(int mx, int my, string texto);
int creamalla(TNodoM **cabeza);

int juega(int mx, int my, string texto){

    setcolor(WHITE);
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
    setlinestyle(0,0,3);
    /// ----- CARGA DE IMAGENES -------------------------------------------------------------------------
    SPRITE *cargaSp=NULL;// qvariable para cargar la imagen.

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
        TNodoM *pM=head; TNodoM *dibmall=head;     ///y se define otro apuntador que nos ayudara a iniciar al principio de la malla.

        creamalla(&head);   ///Se crea los nuevos nodos y los enlaces.
    /// --------------------------------------------------------------------------------------------------

    //funcion para imprimir el ambiente
    printEnvironmentWork(mx, my, texto);

    //Variables de tiempo.
    int start, end;
    //Inilizacion de variables.
    int verf=0, mousx, mousy;
    //VARIABLE DE VIDAS.
    int vidas=3;

    ///DIBUJAMALLA
    dibujaMalla(plant, explosive, mosca, &dibmall);

    start=clock();


    /// TAMAÑO DE LA IMAGEN ancho 54 - alto 52
    Ticono player;
    player.psnodo=pM;
    player.cx=65;   player.cy=85;

    int tecla, cxant=0, cyant=0;
    float puntos=200, win=0;
    char life[20];


    do{


        if(tecla=='h' && player.psnodo->right && player.psnodo->right->dato==3){
            putimage(player.cx+54,player.cy, plant, COPY_PUT);
            player.psnodo->right->dato=2;
            win++;
        }

        if(player.psnodo->dato==1){
            player.psnodo->dato=0;
            vidas--;
        }


        //funcion que imprime el tiempo
        printtime(start, &puntos);
        sprintf(life, "Vidas: %i ", vidas);
        outtextxy(780,30, life);

        if(kbhit()){
            cxant=player.cx;
            cyant=player.cy;
            setfillstyle(4,BLACK);
            bar(cxant, cyant, cxant+40, cyant+40);
        }

        //movimiento del sprite
        tecla=movimiento(&player.psnodo, &player.cx, &player.cy, jugador);
        // - Esta parte verifica si el usuario no selecciona el boton exit -----------------------------
        getmouseclick(WM_LBUTTONDOWN, mousx, mousy);
        if( mousx > mx/8-90 && mousy>my/8+530 && mousx<mx/8+20 && mousy<my/8+560)
            verf=1;
        //-----------------------------------------------------------------------------------------------



    }while(verf!=1 && puntos>0 && vidas!=0 && win!=21);

    if(puntos<0 || vidas==0){
        cleardevice();
        setcolor(WHITE);
        outtextxy(mx/2, my/2, "GAME OVER");
        outtextxy(mx/2, my/2+50, "[ Presiona cualquier tecla para continuar ]");
        delay(1000);
        getch();
        verf=1;
    }
    if(win==21){
        cleardevice();
        outtextxy(mx/2, my/2+100, " [ Presiona cualquier tecla para continuar ] ");
        settextstyle(COMPLEX_FONT,0, 6);
        outtextxy(mx/2+200, my/2, " WIN ");
        putimage(mx/2+150, my/2, plant, COPY_PUT);
        delay(1000);
        getch();

        FILE *recrd;
        float comp;
        char buffer[10];
        recrd=fopen("RecordSC.txt", "r+");

        if(recrd){
            while(!feof(recrd)){

                fscanf(recrd, " %s ------------------------ %f \n",buffer, &comp);
                printf("\n %f \n",comp);


                if(puntos>comp){
                    rewind(recrd);
                        fprintf(recrd, " %s ------------------------ %f \n", texto, puntos);
                    break;
                }

                printf(" %s ---- %f", texto, puntos);
            }
        }
        fclose(recrd);
        verf=1;
    }



    ///Libera memoria de la imagen.
    free(jugador);free(plant);free(sun);
    free(pesticida);free(mosca);free(explosive);


    head=NULL;  /// Libera memoria de
    free(head); /// la mallla.


    end=clock();
    return verf;
}




void printtime(int init, float *puntos){

    int seg, act;
    char reloj[30];
    char record[30];

    act=clock();
    seg=(act-init)/CLK_TCK;
    //printf("%d", *puntos);
    sprintf(reloj, "Time | %d : %d |", seg/60, seg%60);
    sprintf(record, "Score | %.0f |", *puntos);
    *puntos-=15*.001;

    setcolor(LIGHTGREEN);
    outtextxy(60, 30, reloj);
    outtextxy(980, 30, record);

}

void printEnvironmentWork(int mx, int my, string texto){

/*- Dibuja ambiente: -------------------------------------------------------------*/

    outtextxy(490, 30, "1PLAYER:"); //Etiqueta player.;
    outtextxy(600, 30, texto);  //Nombre del jugador.
    //Area de juego.
    rectangle(60, 80, 1140, 600);
/*- Barra Exit. -----------------------------------------------------------------*/

    rectangle(mx/8-90, my/8+530, mx/8+20, my/8+560);
    outtextxy(mx/8-60, my/8+535, "exit");
/* ------- NIVEL -----------------------------------------------------------------------*/
    outtextxy(300, 30, "NIVEL: 1");


}
