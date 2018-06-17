#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c"


int nprenda(int c) {
    int r;

    if (c== 5|| c== 9|| c== 14|| c== 18|| c== 23|| c== 27|| c== 32|| c== 36|| c== 41|| c== 45|| c== 50|| c== 54|| c== 59){
        r = 1;
    } else if (c==6 || c==12) {
        r=2;
    } else if (c==19) {
        r=3;
    } else if (c==31) {
        r=4;
    } else if (c==42) {
        r=5;
    } else if (c==56) {
        r=6;
    } else if (c==26 || c==53) {
        r=7;
    } else if (c==58) {
        r=8;
    } else if (c==63) { /// jardin de la oca
        r=9;
    }

    return(r);
}

void prenda(oca*verde) {
    casilla * aux;
    aux = verde->pos;
    int z = aux->prenda;

    switch(z) {
        case 1:
            c_oca(verde);
            break;
        case 2:
            puente(verde);
            break;
        case 3:
            posada(verde);
            break;
        case 4:
            pozo(verde);
            break;
        case 5:
            laberinto(verde);
            break;
        case 6:
            carcel(verde);
            break;
        case 7:
            dados(verde);
            break;
        case 8:
            calavera(verde);
            break;
        case 9:
            jardin(verde);
            break;

    }
}
