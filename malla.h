#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

typedef struct nodo{
	struct nodo *up;
	struct nodo *down;
	struct nodo *left;
	struct nodo *right;
}TNodoM;


///CREA NODOS
TNodoM *creanodo(){

	TNodoM *nuevo;

	nuevo = (TNodoM *)malloc(sizeof(TNodoM));

	if(nuevo){
		nuevo->down=NULL;
		nuevo->left=NULL;
		nuevo->right=NULL;
		nuevo->up=NULL;
	}

	return nuevo;
}

///INSERTA LA PRIMERA LINEA DE NODOS
int insertarNodo(TNodoM **p){

	TNodoM *New;
	int ret=0;

	New=creanodo();

	if(New){

		if(*p==NULL){
			*p=New;
			ret++;
		}
		else{
			TNodoM *aux, *aux2;

			for(aux=aux2=*p; aux; aux2=aux, aux=aux->right);

			if(aux==NULL){
				aux2->right=New;
				New->left=aux2;
				ret++;
			}
		}

	}

	return ret;

}


///INSERTA NODOS SECUNDARIOS
int insertarNodoS(TNodoM **p, TNodoM **q){		//TNodoM **p nos apunta a la cabeza del renglon
												//TNodoM **q nos ayudara como el apuntador que recorre el renglon anterior para poder asi
	TNodoM *New;								//			 a enlazar la parte de arriba con la de abajo.
	New=creanodo();

	int ret=0;
	if(New){

		//En esta parte no verificamos si la cabeza del reglon esta vacia puesto que ya la creamos
		//en el ciclo for de la funcion main.
		TNodoM *aux, *aux2, *AUX;
		//	aux y aux2 nos ayudaran a desplazarnos para encontrar el ultimo nodo en el renglon que queremos poner el nuevo nodo
		//	AUX nos ayudara para moverse en el renglon anterior para asi poder enlazar los nodos de arriba a abajo
		for(aux=aux2=*p, AUX=*q; aux; aux2=aux, aux=aux->right, AUX=AUX->right);
		//Con el ciclo nos movemos primero los del renglon actual (aux - aux2) y despues el renglon anterior (AUX)

		if(aux==NULL){
			//Enlazamos horizontalmente.
			aux2->right=New;
			New->left=aux2;
			//Enlazamos verticalmente.
			New->up=AUX;
			AUX->down=New;

			ret++;
		}
	}

	return ret;
}


///CREA MALLA
int creamalla(TNodoM **cabeza){

    TNodoM *cabezant=NULL; //creamos para poder desplazarnos en el renglon anterior
	//variables de verificacion y ciclos.
	int i, j, verf;
	int mxn=10, mxm=20;
		//mxn = renglon			Nos sirven para definir los renglones y columnas
		//mxm = columna			de la mallla.

	//creamalla
	for(i=0; i<mxn; i++){
		TNodoM *nuevod;			// nuevod nos ayudara a crear un nuevo nodo que se va a ir desplazando hacia abajo.
		nuevod=creanodo();
		for(j=0; j<mxm-1; j++){
			//separamos la primera lista
			if(i==0){
				verf=insertarNodo( &(*cabeza) );			//insertamos todos los nodos de una columna

			}
			else{
				verf=insertarNodoS( &(*cabeza), &cabezant);
			}
		}
		printf("%d",i);
		//despues de que se halla creado los nodos de una columna |cabezad| nos ayuda a crear un nodo
		//que avance hacia abajo para poder crear asi todos los nodos de la siguiente columna.
		if((*cabeza)->down==NULL && i!=mxn-1){
			//la condicion nos sirve para saber si se estan creando nodos (cabeza->down==NULL)
			//y no crear un nodo de mas (i!=renglon-1) ya que al ultimo crea un ultimo nodo en la fila pero no sus nodos de la columna.
			(*cabeza)->down=nuevod;	 // se crea el nodo de abajo
			nuevod->up=(*cabeza);		// y se enlaza con el nodo de arriba


			cabezant=(*cabeza);		//dejamos a cabezant en el renglon anterior.
			(*cabeza)=(*cabeza)->down;
			//AVANZAMOS LA CABEZA EN LOS RENGLONES PARA PODER CREAR LOS NODOS DE LAS COLUMNAS.
		}

	}

        return verf;
}

#define ancho 54
#define alto 52

void dibujaMalla(void *plant,void *explosive,void *sun){


    FILE *M;
    char buffer[2];

    M=fopen("Nivel1.bin", "rb");

    int i=65, j=85, tamx=ancho;

    if(M!=NULL)
        while(!feof(M)){
        fread(buffer,sizeof(char), 1, M);

        if(!strcmp(buffer, "\n")){
            setcolor(WHITE);
            j+=alto;
            i=65;
            }
        if(!strcmp(buffer, "1")){
           putimage(i,j,plant,COPY_PUT);
        }
        if(!strcmp(buffer, "2")){
            putimage(i,j,sun,COPY_PUT);
        }
        if(!strcmp(buffer, "3")){
            putimage(i,j,explosive,COPY_PUT);
        }

        i+=ancho;
    }




}




///TESTMALLA

int movimiento(TNodoM **head, int *inix, int *iniy, void *plyr){

    int t;

    if( kbhit() ){

        t=getch();

        if(t=='d' && (*head)->right){ /// ->
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

    return t;

}
