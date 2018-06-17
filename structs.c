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

struct casarch {
    int n, prenda;
}cars;
