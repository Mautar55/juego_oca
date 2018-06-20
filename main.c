#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.c"
int paso_pozo;
int tiros;

int main () {
    srand(time(NULL));

    // cola
    alum *pc = malloc(sizeof(*pc));  /*primer nodo de la cola que siempre va a estar vacio*/
    generar_cola(pc); // primer nodo estara vacio
    recorrer(pc);

    //arbol
    printf("\nDEP: antes de plntar semilla.");
    nodo * ta = malloc(sizeof(*ta)); /* creo variable de la struct arbol y pido espacio al tope del arbol*/
    printf("\nDEP: paso 1 listo.");
    ta->ntiros=(1); // notable que es el primero
    printf("\nDEP: arbol entopado.\n"); /* tope de pila solo va a tener 1 tiro para identificar xq nunca la partida del ganador se v a a tirar 1 sola vez*/
    /// seleccion para jugar
    // al que resulte ganador se le asigna un nodo al arbol
    alum * ocu = pc; /* principio de la cola*/

    int j1p, j2p, j3p, j4p, numt;

    j1p=1;
    j2p=1;
    j3p=1;
    j4p=1;
    numt=0;

    alum * mae = malloc(sizeof(*mae));
    strcpy(mae->apellido,"Krickenguinder");
    strcpy(mae->nombre,"Vraska");

    alum * jug1;
    alum * jug2;
    alum * jug3;
    alum * jug4;

    while(ocu->sgte != NULL) {
    int j1p, j2p, j3p, j4p, numt;
    printf("\nInicia un proceso de partida\n");
        tiros=0;
        printf("\nInicia 2 proceso de partida\n");
        jug1 = ocu->sgte;
        printf("\nInicia 3 proceso de partida\n");

        if (jug1->sgte == NULL) {
            // juega el ultimo sig con la maestra
            printf("\nInicia 4 proceso de partida\n");
            j1p=1;
            j2p=1;
            j3p=0;
            j4p=0;
            numt=0;
            jugar(&j1p,&j2p,&j3p,&j4p,&numt);
            if (j1p == 1) {
                // gano el jugador 1
                enarbolar(ta,jug1,tiros);
            } else {
                // gano la maestra
                enarbolar(ta,mae,tiros);
            }
            ocu = jug1;
        } else {
            jug2=jug1->sgte;
            if (jug2->sgte == NULL) {
                // juegan los 2 sig
                printf("\nInicia 5 proceso de partida\n");
                j1p=1;
                j2p=1;
                j3p=0;
                j4p=0;
                numt=0;
                jugar(&j1p,&j2p,&j3p,&j4p,&numt);
                if (j1p == 1) {
                // gano el jugador 1
                enarbolar(ta,jug1,tiros);
                } else {
                // gano el j2
                enarbolar(ta,jug2,tiros);
                }
                ocu = jug2;
            } else {
                jug3 = jug2->sgte;
                if (jug3->sgte==NULL) {
                    // juegan los 2 sig
                    printf("\nInicia 6 proceso de partida\n");
                    j1p=1;
                    j2p=1;
                    j3p=0;
                    j4p=0;
                    numt=0;
                    jugar(&j1p,&j2p,&j3p,&j4p,&numt);
                    if (j1p == 1) {
                        // gano el jugador 1
                        enarbolar(ta,jug1,tiros);
                    } else {
                        // gano el 2
                        enarbolar(ta,jug2,tiros);
                    }
                    ocu = jug2;
                } else {
                    jug4 = jug3->sgte;
                    // juegan los 4 sig
                    printf("\nInicia 7 proceso de partida\n");
                    j1p=1;
                    j2p=1;
                    j3p=1;
                    j4p=1;
                    numt=0;
                    printf("\nInicia 8 proceso de partida\n");
                    printf("\n  %i %i %i %i %i  \n", j1p,j2p,j3p,j4p,numt);
                    jugar(&j1p,&j2p,&j3p,&j4p,&numt);
                    printf("\nInicia 9 proceso de partida \n");

                    //printf("\n  %i %i %i %i %i  \n", j1p,j2p,j3p,j4p,numt);

                    printf("\n ggg %i",j2p);

                    if (j1p == 1) {
                        enarbolar(ta,jug1,tiros);
                    }
                    if (j2p == 1) {
                        enarbolar(ta,jug2,tiros);
                    }
                    if (j3p == 1) {
                        enarbolar(ta,jug3,tiros);
                    }
                    if (j4p == 1) {
                        enarbolar(ta,jug4,tiros);
                    }
                    printf("\nInicia 10 proceso de partida\n");
                    ocu = jug4;
                    printf("\npartida de 4 jug celebrada\n");
                }
            }
        }

    };

    //int j1p, j2p, j3p, j4p, numt;
    /*j1p=1;
    j2p=1;
    j3p=1;
    j4p=1;
    numt=0;

    jugar(&j1p,&j2p,&j3p,&j4p,&numt);

    printf("\n########################################\n");
    printf("\njugadores insertados 1 2 3 4 : %i %i %i %i || Nro de tiros: %i.\n",j1p, j2p, j3p, j4p,numt);
    printf("\n########################################\n");*/

    recorrer_a(ta);


    return 0;
};
