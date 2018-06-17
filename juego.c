#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.c"
int paso_pozo;

int dado() {
    int n = 0;
    n = (rand() % 6)+1;
    printf(">>> Dado tirado: %i\n",n);
    return (n);
};

void crear(casilla *p, int g){
    casilla * act = p;
    casilla * aux;
    while (act->sgte != NULL) {
        act = act-> sgte;
    }
    act->sgte = malloc(sizeof(casilla));
    aux = act;
    act = act->sgte;
    act->n=g;
    act->prenda=nprenda(g);
    act->ant = aux;
}

void recorrer_c(casilla * p){
    casilla * aux = p;
    while (aux != NULL) {
        printf("Casilla %i - Prenda %i\n",aux->n,aux->prenda);
        aux = aux->sgte;
    }
}

void cargar_c(casilla * m) {
    casilla *p =m;
    FILE * arch;
    if((arch = fopen("circuito_clasico.bin","rb"))==NULL){
        printf("error 1 LEYENDO archivo\n");
    }
    while(!feof(arch)){
        fread(&cars,sizeof(struct casarch),1,arch);

        crear(p,cars.n);
    }

    fclose(arch);
}

void archivar(casilla * p) {

    FILE * arch;
    if ((arch = fopen("circuito_clasico.bin","wb"))==NULL){
        printf("error 1 archivo\n");
    }

    casilla * aux = p;

    while (aux != NULL) {
        printf("entra en el bucle   ");
        // inicio guardado
        cars.n=aux->n;
        cars.prenda=aux->prenda;
        printf("\ncarsn: %i - carsp; %i - auxn %i - auxp %i\n",cars.n,cars.prenda,aux->n,aux->prenda);
        fwrite(&cars,sizeof(struct casarch),1,arch);

        // fin guardado

        aux = aux->sgte;
    }

    fclose(arch);

}




void limpiar_tablero(casilla * p){
    casilla * aux = p;
    casilla * aux2;
    while (aux != NULL) {

        aux2=aux;
        aux = aux->sgte;

        free(aux2);
    }
}

void tomar_turno(oca * verde) {
    if (verde->pozo == 0) {
        if (verde->hielo == 0) {
            if (verde->fin == 0) {
                printf ("### EL JUGADOR %i COMIENZA SU TURNO ###\n",verde->tag);
                casilla * aux;
                int d6 = dado();

                desplazar(verde,d6);

                aux = verde -> pos;
                int m = aux->n;

                printf(">>> Jugador %i avanza a la casilla %i\n",verde->tag,m);
                prenda(verde);
                printf ("### EL JUGADOR %i FINALIZA SU TURNO ###\n\n",verde->tag);

            }

        } else {
            verde->hielo = verde->hielo-1;
            printf("--- El jugador %i omite este turno.\n\n",verde->tag);
        }
    } else {
        printf("--- El jugador %i esta en el pozo, dicho eso omite su turno.\n\n",verde->tag);
    }
}

void jugar(int *j1p,int *j2p,int *j3p,int *j4p)
{
    //lectura desde archivo
    casilla * p = malloc(sizeof(casilla));
    cargar_c(p);
    casilla * t = p->sgte;

    // generacion de las casillas
    /*casilla * t = malloc(sizeof(casilla));
    t->n=1;
    t->prenda=nprenda(t->n);
    int i =2;
    while (i<=63) {
        crear(t,i);
        i++;
    }*/

    recorrer_c(t);
    //archivar(t);
    printf("\n-----------------------------------------------------\n");

    // creacion de jugadores

    oca * jug1 = malloc(sizeof(oca));
    if (*j1p == 1){
        jug1 -> pos = t;
        jug1->tag = 1;
        jug1->hielo = 0;
        jug1->pozo=0;
        jug1->fin=0;
    } else { jug1->fin=1; }

    oca * jug2 = malloc(sizeof(oca));
    if (*j2p == 1){
        jug2 -> pos = t;
        jug2->tag = 2;
        jug2->hielo = 0;
        jug2->pozo=0;
        jug2->fin=0;
    } else { jug2->fin=1; }

    oca * jug3 = malloc(sizeof(oca));
    if (*j3p == 1){
        jug3 -> pos = t;
        jug3->tag = 3;
        jug3->hielo = 0;
        jug3->pozo=0;
        jug3->fin=0;
    } else { jug3->fin=1; }

    oca * jug4 = malloc(sizeof(oca));
    if (*j4p == 1){
        jug4 -> pos = t;
        jug4->tag = 4;
        jug4->hielo = 0;
        jug4->pozo=0;
        jug4->fin=0;
    } else { jug4->fin=1; }

    // comienzo del juego

    int ubic = 0;
    int j1res =0;
    int j2res =0;
    int j3res =0;
    int j4res =0;


    casilla * posa;
    casilla * posp;

    while ((jug1->fin == 0)||(jug2->fin == 0)||(jug3->fin == 0)||(jug4->fin == 0)) {
        if (jug1->tag != NULL) {
            tomar_turno(jug1);

            if (paso_pozo == 1) {
                jug1->pozo = 0;
                jug2->pozo = 0;
                jug3->pozo = 0;
                jug4->pozo = 0;
                paso_pozo = 0;
            }
        }
        if ((jug1->fin == 1) && (*j1p != 0) && (j1res==0)) {
            j1res = ubic+1;
            ubic = ubic+1;
        }

        if (jug2->tag != NULL) {
            tomar_turno(jug2);
            if (paso_pozo == 1) {
                jug1->pozo = 0;
                jug2->pozo = 0;
                jug3->pozo = 0;
                jug4->pozo = 0;
                paso_pozo = 0;
            }
        }
        if ((jug2->fin == 1) && (*j2p != 0) && (j2res==0)) {
            j2res = ubic+1;
            ubic = ubic+1;
        }


        if (jug3->tag != NULL) {
            tomar_turno(jug3);
            if (paso_pozo == 1) {
                jug1->pozo = 0;
                jug2->pozo = 0;
                jug3->pozo = 0;
                jug4->pozo = 0;
                paso_pozo = 0;
            }
        }
        if ((jug3->fin == 1) && (*j3p != 0) && (j3res==0)) {
            j3res = ubic+1;
            ubic = ubic+1;
        }


        if (jug4->tag != NULL) {
        tomar_turno(jug4);
        if (paso_pozo == 1) {
                jug1->pozo = 0;
                jug2->pozo = 0;
                jug3->pozo = 0;
                jug4->pozo = 0;
                paso_pozo = 0;
            }
        }
        if ((jug4->fin == 1) && (*j4p != 0) && (j4res==0)) {
            j4res = ubic+1;
            ubic = ubic+1;
        }

        // terminar si solo queda uno

        if ((jug2->fin==1)&&(jug3->fin==1)&&(jug4->fin==1)) {
            if ((*j1p)&&(j1res==0)) {
                jug1->fin=1;
                j1res = ubic+1;
                ubic = ubic+1;
                printf("### El jugador 1 es el unico que queda, se da por sentado que pierde la partida.\n");
            }

        }
        if ((jug1->fin==1)&&(jug3->fin==1)&&(jug4->fin==1)) {
            if ((*j2p)&&(j2res==0)) {
                jug2->fin=1;
                j2res = ubic+1;
                ubic = ubic+1;
                printf("### El jugador 2 es el unico que queda, se da por sentado que pierde la partida.\n");
            }
        }
        if ((jug2->fin==1)&&(jug1->fin==1)&&(jug4->fin==1)) {
            if ((*j3p)&&(j3res==0)) {
                jug3->fin=1;
                j3res = ubic+1;
                ubic = ubic+1;
                printf("### El jugador 3 es el unico que queda, se da por sentado que pierde la partida.\n");
            }
        }
        if ((jug2->fin==1)&&(jug3->fin==1)&&(jug1->fin==1)) {
            if ((*j4p)&&(j4res==0)) {
                jug4->fin=1;
                j4res = ubic+1;
                ubic = ubic+1;
                printf("### El jugador 4 es el unico que queda, se da por sentado que pierde la partida.\n");
            }
        }

    }

    printf("\n--- FIN DEL JUEGO\n");

    *j1p = j1res;
    *j2p = j2res;
    *j3p = j3res;
    *j4p = j4res;

    // limpieza

    free(jug1);
    free(jug2);
    free(jug3);
    free(jug4);
    limpiar_tablero(t);

}

