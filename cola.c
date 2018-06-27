#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c"

void recorrer(alum*pc) {
    alum * aux=pc; /* declaro y asigno el primer nodo*/
    aux=aux->sgte; /* avanzo xq esta vacio*/
    while(aux != NULL){
        printf("\n Alumno: %s, %s -\n",aux->apellido, aux->nombre);
        aux=aux->sgte;
    }
    printf("\nFIn del recorrido de la cola\n");
} /* veo que esta todo ok en la cola*/

void encolar(alum *pc, alum*nv){
    alum * aux = pc;
    alum * aux2;
    while(aux->sgte != NULL) {
        aux=aux->sgte;
    }
    aux->sgte=nv;
};

void generar_cola(alum*p){

    int i = 0;
    printf("\nIngrese el numero de alumnos a cargar: ");
    fflush(stdin);
    scanf("%i",&i);
    fflush(stdin);

    char nombr[50];  /* declaro variables para copiar strcpy a la estructura*/
    char apell[50];

    alum*aux; /* declaro puntero nuevo de alumno*/

    while (i != 0) {
        printf("\nEscriba un %i nombre y luego un apellido: ",i);
        fflush(stdin);
        scanf("%s",nombr);
        fflush(stdin);
        scanf("%s",apell);
        fflush(stdin);
        aux=malloc(sizeof(aux));  /* pido memoria */
        strcpy(aux->apellido,apell);
        strcpy(aux->nombre,nombr); /* copio a struct alm*/
        encolar(p,aux);
        i=i-1;
    }
    system("clear");
};

