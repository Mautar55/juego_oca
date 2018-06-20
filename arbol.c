#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c"

void enarbolar(nodo * top, alum * gan, int tiradas){ // raiz y nodo del jugador (alumno) que gano, la maestra tiene un nodo propio que se hara antes de la raiz

    if (top->ntiros == 1) {
        if (top->izq != NULL) {
            enarbolar(top->izq,gan,tiradas);
        } else {
            // se encontro, y es la raiz
            nodo * nv = malloc(sizeof(*nv));
            strcpy(nv->apellido,gan->apellido);
            strcpy(nv->nombre,gan->nombre);
            nv->ntiros=tiradas;
            top->izq=nv;
        }
    } else { // estamos en la raiz a lo mucho

        if (strcmp(top->apellido,gan->apellido) > 0) {
            // ir por izq
            if (top->izq != NULL) {
                enarbolar(top->izq,gan,tiradas);
            } else {
                nodo * nv = malloc(sizeof(*nv));
                strcpy(nv->apellido,gan->apellido);
                strcpy(nv->nombre,gan->nombre);
                nv->ntiros=tiradas;
                top->izq=nv;
            }
        } else if (strcmp(top->apellido,gan->apellido) < 0) {
            // ir por der
            if (top->der != NULL) {
                enarbolar(top->der,gan,tiradas);
            } else {
                nodo * nv = malloc(sizeof(*nv));
                strcpy(nv->apellido,gan->apellido);
                strcpy(nv->nombre,gan->nombre);
                nv->ntiros=tiradas;
                top->der=nv;
            }
        } else if ((strcmp(top->apellido,gan->apellido)) == 0) {
            // es igual y hay que ver el nombre

                if ((strcmp(top->nombre,gan->nombre)) > 0) {
                // ir por izq
                if (top->izq != NULL) {
                    enarbolar(top->izq,gan,tiradas);
                } else {
                    nodo * nv = malloc(sizeof(*nv));
                    strcpy(nv->apellido,gan->apellido);
                    strcpy(nv->nombre,gan->nombre);
                    nv->ntiros=tiradas;
                    top->izq=nv;
                }
            } else if ((strcmp(top->nombre,gan->nombre)) < 0) {
                // ir por der
                if (top->der != NULL) {
                    enarbolar(top->der,gan,tiradas);
                } else {
                    nodo * nv = malloc(sizeof(*nv));
                    strcpy(nv->apellido,gan->apellido);
                    strcpy(nv->nombre,gan->nombre);
                    nv->ntiros=tiradas;
                    top->der=nv;
                }
            } else if ((strcmp(top->nombre,gan->nombre)) == 0) {
                printf("El nodo que quiso insertar ya existe.");
            }

        }

    }

}

void recorrer_a(nodo * top) {

    if ( top->izq != NULL) {
        recorrer_a(top->izq);
    }
    printf("\n %s %s en %i tiros.",top->apellido,top->nombre,top->ntiros);

    if ( top->der != NULL) {
        recorrer_a(top->der);
    }
}
