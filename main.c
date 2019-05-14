#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

typedef char string[10];

//Prototipos
void portada(int centerx, int centery);
int menu(int mx, int my);
int juega(int mx, int my, string texto);
void inittextxy(int Xmax, int Ymax, string texto);
int opcayuda(int mx, int my);

int main(void){

    initwindow(1200, 650);

    /*Valores maximos de x y*/
    int maxx, maxy;
    maxx = getmaxx();
    maxy = getmaxy();

    /* Iniliacion de variables */
    int opc, back;
    string text;

    /** portada **/
    portada(maxx, maxy);
    getch();
    cleardevice();

    //opcion regreso por si el usario vuelve al menu.
    regreso:
        cleardevice();

    /** menu **/
    opc=menu(maxx, maxy);

    /** opciones **/
    switch(opc){

    ///Juego.
    case 0:{
        cleardevice();
        //Ingresa ID del jugador.
        outtextxy(250, 210, "Name (ID): ");
        rectangle(250, 260, 750, 300);
        inittextxy(maxx, maxy, text);
        cleardevice();
        back=juega(maxx, maxy, text);
        //back no comunica que le usuario aplano el boton de regreso.
        if(back == 1)
            goto regreso; //El goto nos regresa a la parte de arriba "regreso".
        break;
    }

    ///Records.
    case 1:{
        cleardevice();

        break;
    }

    ///Ayuda.
    case 2:{
        cleardevice();
        back=opcayuda(maxx, maxy);
        //back no comunica que le usuario aplano el boton de regreso.
        if(back == 1)
            goto regreso; //El goto nos regresa a la parte de arriba "regreso".
        break;
    }

    ///Salir.
    case 3:{
        exit(1);
        break;
    }

    }

    system("pause");
    closegraph();
}

