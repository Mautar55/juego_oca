#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ficha {
    struct casilla *pos;
    int hielo;
    int pozo;
    int tag;
    int fin;
}oca;

typedef struct cas {
    int n;
    int prenda;
    struct casilla *sgte;
    struct casilla *ant;
}casilla;

typedef struct alm{ /*alumnos*/
    char *nombre[25];
    char *apellido[25];
    struct alum *sgte;
}alum;

typedef struct arbol{
    char *nombre[25];
    char *apellido[25];
    struct nodo *izq;
    struct nodo *der;
    int ntiros;
}nodo;

typedef struct casr {
    int n, prenda;
}casarch;
