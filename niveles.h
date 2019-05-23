






#define ancho 54
#define alto 52

void movimiento(TNodoM **head, int *inix, int *iniy, void *plyr){

    int t;

    if( kbhit() ){

        t=getch();

        if(t==100 && (*head)->right){ /// ->
            *inix+=ancho;
            (*head)=(*head)->right;
        }
        if(t==97 && (*head)->left){    /// <-
            *inix-=ancho;
            (*head)=(*head)->left;
        }
        if(t==115 && (*head)->down){
            *iniy+=alto;
            (*head)=(*head)->down;
        }
        if(t==119 && (*head)->up){
            *iniy-=alto;
            (*head)=(*head)->up;
        }

    }
    putimage(*inix, *iniy, plyr, COPY_PUT);

}
