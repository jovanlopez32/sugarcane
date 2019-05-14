#include <stdio.h>
#include <graphics.h>

void portada(int centerx, int centery){

    /** IMAGENES **/
    /* Sugar Cane */
    readimagefile("SugCane.jpg", 300, 20, 850, 320);

    settextstyle(COMPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(centerx/2-80, centery/2+40, "INTEGRANTES");

    settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
    outtextxy(centerx/2-110, centery/2+80, "Mae de Anda Garcia");
    outtextxy(centerx/2-140, centery/2+100, "Jorge Jovan Liñan Lopez");

    outtextxy(centerx/2-300, centery/2+160, "Estructura de Datos II - Lenguajes de Programacion");
    rectangle(250, 350, 900, 540);

    //* Click para continuar... */
    settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(centerx/2-390, centery/2+250, "-- ¡ PRESIONE CUALQUIER TECLA PARA CONTINUAR ! --");

}
