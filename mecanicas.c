#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.c"
extern int paso_pozo = 0;
extern int tiros = 0;

char buf_a[4][25];
char buf_n[4][25];

void desplazar(oca * verde,int n);
void ir_hasta(oca*verde,int f);
void c_oca(oca*verde);
void puente(oca*verde);
void posada (oca*verde);
void pozo (oca*verde);
void laberinto (oca*verde);
void carcel (oca*verde);
void dados(oca*verde);
void calavera(oca*verde);
void jardin(oca*verde);


/*void desplazar(oca * verde,int n){

    casilla * aux = verde->pos;

    int g = n,m=0;

    if (n>0) {
        while (g != 0) {
            if(aux->sgte != NULL) {
                aux = aux->sgte;
                g = g-1;

                if(aux->n == 42){
                    paso_pozo = 1;
                }
            } else {
                m=g;
                g=0;
            }
        }
        if (m != 0) {
            while (m != 0) {
                aux = aux->ant;
                m = m-1;

                if(aux->n == 42){
                    paso_pozo = 1;
                }
            }
        }
    } else{
     if (n<0) {
        while (g != 0) {
            aux = aux->ant;
            g = g+1;

            if(aux->n == 42){
                paso_pozo = 1;
            }
        }
    }
    }

    // retroceso para el jardin de la oca


    verde->pos = aux;
};*/

void desplazar(oca * verde,int n){

    casilla * aux = verde->pos;
    int m = 0;
    int g = n;

    if (n>0) {
        while (g != 0) {
            if(aux->sgte != NULL) {
                aux = aux->sgte;
                g = g-1;

                if(aux->n == 31){
                    paso_pozo = 1;

                }

            } else {
                m=g;
                g=0;
                if (m != 0) {
            while (m != 0) {
                aux = aux->ant;
                m = m-1;

                if(aux->n == 31){
                    paso_pozo = 1;
                }
            }
        }
            }
        }

        //jj


    } else if (n<0) {
        while (g != 0) {
            aux = aux->ant;
            g = g+1;

            if(aux->n == 31){
                paso_pozo = 1;
            }
        }
    }

    // retroceso para el jardin de la oca

    /*if (g != 0) {
        g = -g;
        while (g != 0) {
            aux = aux->ant;
            g = g+1;

            if(aux->n == 42){
                paso_pozo = 1;
            }
        }
    }*/
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
        } else {
            break;
        }
    }

    int z = pas->n;
    ir_hasta(verde,z);

    aux= verde ->pos;
    m = aux->n;
    printf("--- OCA El jugador cayo en una oca y se fue feliz a la casilla %i\n    Debe tirar el dado para avanzar!",aux->n);
    int u = dado();
    desplazar(verde,u);
    aux= verde ->pos;
    m = aux->n;
    printf("--- El jugador avanzo a la casilla %i\n",m);
    prenda(verde);
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
    desplazar(verde,-12);
    printf("--- LABERINTO a 30\n");
}

void carcel (oca*verde) {
    verde->hielo = verde->hielo + 2;
    printf("--- CARCEL a esperar 2 turnos\n");
}

void dados(oca*verde){
    printf("--- DADOS tire los dados para avanzar esas casillas...\n");
    int n=dado();
    desplazar(verde,n);
    casilla * loc = verde->pos;
    int i = loc->n;
    printf("--- El jugador avanzo a la casilla %i\n",i);
    prenda(verde);
}

void calavera(oca*verde){
    desplazar(verde,-57);
    printf("--- CALAVERAAAA MUAJAJAJAJJAJAJA\n");
}

void jardin(oca*verde){
    casilla * aux = verde->pos;
    if (aux->sgte==NULL) {
        verde->fin = 1;
        printf("--- EL JUGADOR %i HA LLEGADO AL JARDIN DE LA OCA, FELICITACIONES!!!!\n", verde->tag);
    } else {
        printf("\n*** imprimir");
        casilla * opo = aux->sgte;
        printf("\n*** num %i pre %i",opo->n,opo->prenda);
    }
}


