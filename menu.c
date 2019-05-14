#include <stdio.h>
#include <graphics.h>

typedef char string[10];

//prototypes
int clickBoton(int clkx, int clky, int mx);

int menu(int mx, int my){

    int i, msx, msy, verf=-1;
    string textbox[4]={"JUGAR", "RECORDS", "AYUDA", "SALIR"};

    /* Dibuja botones */
    setlinestyle(SOLID_LINE, 0, 6);
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);

    for(i=0; i<4; i++){
        setcolor(GREEN);
        rectangle( (mx/2)-300, (i*150)+(150/2), (mx/2)+300, (i*150)+150 );
        ///printf("%i %i %i %i", (mx/2)-300, (i*150)+(150/2), (mx/2)+300, (i*150)+150);
        setcolor(WHITE);
        outtextxy((mx/2)-20, (i*150)+100, textbox[i]);
    }

    /* Selecciona boton */
    do{
    getmouseclick(WM_LBUTTONDOWN, msx, msy);

    verf=clickBoton(msx, msy, mx);

    }while(verf < 0);

    return verf;
}

int clickBoton(int clkx, int clky, int mx){

    int i, rverf=-1;

    for(i=0; i<4; i++){
        if( clkx>(mx/2)-300 && clky>(i*150)+(150/2) && clkx<(mx/2)+300 && clky<(i*150)+150 ){
            //printf(" %i ", i);
            rverf=i;
        }
    }

    return rverf;
}
