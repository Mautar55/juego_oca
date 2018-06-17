#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c"
extern int paso_pozo = 0;

void desplazar(oca * verde,int n){

    casilla * aux = verde->pos;

    int g = n;

    if (n>0) {
        while (g != 0) {
            if(aux->sgte != NULL) {
                aux = aux->sgte;
                g = g-1;

                if(aux->n == 42){
                    paso_pozo = 1;
                }

            } else {
                break;
            }
        }
    } else if (n<0) {
        while (g != 0) {
            aux = aux->ant;
            g = g+1;

            if(aux->n == 42){
                paso_pozo = 1;
            }
        }
    }

    // retroceso para el jardin de la oca

    if (g != 0) {
        g = -g;
        while (g != 0) {
            aux = aux->ant;
            g = g+1;

            if(aux->n == 42){
                paso_pozo = 1;
            }
        }
    }
    verde->pos = aux;
};

void ir_hasta(oca*verde,int f) {
    casilla * aux;
    aux = verde->pos;
    int a = aux->n;
    if (a<f) {
        while (aux->n != f) {
            desplazar(verde,1);
            aux = verde->pos;
            a = aux->n;
        }
    } else if (a>f) {
        while (aux->n != f) {
            desplazar(verde,-1);
            aux = verde->pos;
            int a = aux->n;
        }
    }
};

void c_oca(oca*verde) {
    casilla * aux = verde->pos;
    int m = aux->n;

        //(c== 5|| c== 9|| c== 14|| c== 18|| c== 23|| c== 27|
        // c== 32|| c== 36|| c== 41|| c== 45|| c== 50|| c== 54|| c== 59)

    casilla * pas = aux;
    if (pas->sgte != NULL) {
        pas = pas->sgte;
    }
    while ((pas->prenda != 1) || (pas->n < m)) {
        if(pas->sgte !=NULL) {
            pas = pas->sgte;
        } else { break; }
    }

    int z = pas->n;
    ir_hasta(verde,z);

    aux= verde ->pos;
    m = aux->n;
    printf("--- OCA El jugador cayo en una oca y se fue feliz a la casilla %i\n",aux->n);
}



void puente(oca*verde) {
    printf("--- PUENTE a la posada 19\n");
    ir_hasta(verde,19);
    prenda(verde);
}

void posada (oca*verde) {
    verde->hielo=verde->hielo +1;
    printf("--- POSADA a esperar en la posada\n");
}

void pozo (oca*verde) {
    verde->pozo = 1;
    printf("--- CAYO EN EL POZOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
}

void laberinto (oca*verde) {
    ir_hasta(verde,30);
    printf("--- LABERINTO a 30\n");
}

void carcel (oca*verde) {
    verde->hielo = verde->hielo + 2;
    printf("--- CARCEL a esperar 2 turnos\n");
}

void dados(oca*verde){
    int n=dado();
    desplazar(verde,n);
    printf("--- DADOS marca para avanzar %i\n",n);
}

void calavera(oca*verde){
    ir_hasta(verde,1);
    printf("--- CALAVERAAAA MUAJAJAJAJJAJAJA\n");
}

void jardin(oca*verde){
    casilla * aux = verde->pos;
    if (aux->sgte==NULL) {
        verde->fin = 1;
        printf("--- EL JUGADOR %i HA LLEGADO AL JARDIN DE LA OCA, FELICITACIONES!!!!\n", verde->tag);
    }
}


