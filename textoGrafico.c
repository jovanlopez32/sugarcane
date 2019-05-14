#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

typedef char string [20];

//numero ASCII del retroceso: 8
//numero ASCII del enter: 13


void inittextxy(int Xmax, int Ymax, string texto){

    //Coordenadas donde se apuntara el cursor.
    int x=(Xmax/4)+20, y=(Ymax/4+110)-3, i=0;
    //Variable que almacenara los caracteres que digitemos las cuales se guardaran en la cadena que se
    //convertira a entero. el [0] con el numero caracter y el [1] con el fin de cadena siempre.
    char tecla[2];


    settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);

    do{

        fflush(stdin);
        /*-----  Animacion del cursor  -----------*/
        do{

            setcolor(WHITE);       //visualizamos.
            outtextxy(x, y, "|");
            delay(100);
            setcolor(BLACK);        //escondemos.
            outtextxy(x, y, "|");
            delay(100);

        }while(!kbhit());

        tecla[0]=getch(); //capturamos el numero de tipo caracter.
        tecla[1]='\0';      //cerramos la cadena.

        if(tecla[0]!=8 && tecla[0]!=13 && i<=4 && i>=0){

            //Imprime el valor capturado.
            setcolor(WHITE);
            outtextxy(x, y, tecla);
            //Avanza segun el tamaño de un caracter en modo grafico.
            x+=textwidth(tecla);
            //Guarda el caracter dentro de la cadena a convertir a entero.
            texto[i++]=tecla[0];    //Aumenta i++ para poder guardar en texto[0] un caracter y despues
            texto[i]='\0';          //incrementa el i para poder guardar el fin de cadena en el siguiente espacio.

        }
        else{

            //si la tecla fue retroceso se viene al else y se comprueba que alla escrito algo validando la
            // i mayor a 0.
            if(tecla[0]==8 && i>0){

                tecla[0]=texto[--i]; //se decrementa la i para poder establecer en el ultimo casillero se toma el valor del ultimo
                tecla[1]=texto[i]='\0'; //y se sustituye con el cierre de caracter
                x-=textwidth(tecla); //Retrocede segun el tamaño de caracter en modo grafico.
                //se dibuja el caracter tecla para borrar el ultimo caracter dado.
                setcolor(BLACK);
                outtextxy(x,y,tecla);
            }

        }


    }while(tecla[0]!=13 );


}
