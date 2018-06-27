#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.c"
int paso_pozo;
int tiros;

char buf_a[4][25];
char buf_n[4][25];

int dado() {
    int n = 0;

    while ((n>6)||(n<1)) {

        printf("\n### Tire un dado de 6 caras, no mas ni menos: ");
        fflush(stdin);
        scanf("%i",&n);
        fflush(stdin);
    }
    tiros=tiros+1; // linea que faltaba.

    // codigo del dado automatizado de 6 caras.
    /*int n = 0;
    n = (rand() % 6)+1;
    printf(">>> Dado tirado: %i\n",n);
    tiros=tiros+1;*/ // la linea que faltaba la primera vez que mostramos, por la que no se guardaba un numero de tiros.

    return (n);
}

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
    printf ("\nEL juego trata de cargar\n");
    casilla *p =m;
    printf ("\nEL juego trata 2 de cargar\n");
    FILE * arch;
    printf ("\nEL juego trata 3 de cargar\n");
    if((arch = fopen("circuito_clasico.bin","rb"))==NULL){
        printf("error 1 LEYENDO archivo\n");
    }
    printf ("\nEL juego trata 4 de cargar\n");
    casarch * cam;
    while(!feof(arch)){
        fread(cam,sizeof(cam),1,arch);

        crear(p,cam->n);
    }
    printf ("\nEL juego trata 5 de cargar\n");
    fclose(arch);
}

void archivar(casilla * p) {

    FILE * arch;
    if ((arch = fopen("circuito_clasico.bin","wb"))==NULL){
        printf("error 1 archivo\n");
    }

    casilla * aux = p;
    casarch * cam;
    while (aux != NULL) {
        printf("entra en el bucle   ");
        // inicio guardado
        cam->n=aux->n;
        cam->prenda=aux->prenda;
        printf("\ncarsn: %i - carsp; %i - auxn %i - auxp %i\n",cam->n,cam->prenda,aux->n,aux->prenda);
        fwrite(cam,sizeof(cam),1,arch);

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
                printf ("### JUGADOR/A %s %s (%i) COMIENZA SU TURNO ###\n",buf_n[verde->tag-1],buf_a[verde->tag-1],verde->tag);
                casilla * aux;
                int d6 = dado();

                desplazar(verde,d6);

                aux = verde -> pos;
                int m = aux->n;

                printf(">>> Jugador/a %s %s (%i) avanza a la casilla %i\n",buf_n[verde->tag-1],buf_a[verde->tag-1],verde->tag,m);
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

void jugar(int *j1p,int *j2p,int *j3p,int *j4p,int *ntiros)
{

    printf ("\nEL juego trata de iniciar\n");
    paso_pozo=0;
    printf ("\nEL juego trata 2 de iniciar\n");

    /*//lectura desde archivo
    casilla * p = malloc(sizeof(casilla));
    printf ("\nEL juego trata 3 de iniciar\n");
    cargar_c(p);
    printf ("\nEL juego trata 4 de iniciar\n");
    casilla * t = p->sgte;
    printf ("\nEL juego trata 5 de iniciar\n");*/


    // generacion de las casillas
    casilla * t=NULL;
    int i=1;
    casilla *aux=t,*aux3;

    while (i<=63) {

        if(t==NULL){
            t=malloc(sizeof(casilla));
            t->n = i;
            t->prenda = nprenda(i);
            t->ant = NULL;
            t->sgte= NULL;
            i ++;
            aux=t;

        }else{
            aux3 = aux;
            aux->sgte = malloc(sizeof(casilla));
            aux = aux->sgte;
            aux->ant = aux3;
            aux->n = i;
            aux->prenda = nprenda(i);
            if(i==63){
                aux->sgte = NULL;
            }
            i ++;

        }
    }
    printf ("\nEL juego trata 2-1 de iniciar\n");

    //recorrer_c(t);
    //archivar(t);
    printf("\n-----------------------------------------------------\n");

    // creacion de jugadores
    printf ("\nEL juego trata 2-2 de iniciar\n");
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
    printf ("\nEL juego trata 2-3 de iniciar\n");

    int ubic = 0;
    int j1res =0;
    int j2res =0;
    int j3res =0;
    int j4res =0;


    casilla * posa;
    casilla * posp;
    system("clear");
    printf("\n          --- COMIENZA UNA PARTIDA NUEVAAAAA --- \n");
    printf("   JUGADORES:  \n");

    printf("1: %s %s .\n",buf_n[0],buf_a[0]);
    printf("2: %s %s .\n",buf_n[1],buf_a[1]);

    if (*j3p == 1) {
        printf("3: %s %s .\n",buf_n[2],buf_a[2]);
        printf("4: %s %s .\n",buf_n[3],buf_a[3]);
    }

    printf("--- Pulse cualquier tecla para continuar ---\n");
    pausa();
    system("clear");

    casilla * eax;

    while ((jug1->fin == 0)||(jug2->fin == 0)||(jug3->fin == 0)||(jug4->fin == 0)) {

        system("clear");
        printf("--- ESTADOS ---------------------------------------\n");
        eax = jug1->pos;
        printf("JUG 1: %s %s | Pos: %i | Hielo: %i | Pozo: %i | Fin: %i.\n",buf_n[0],buf_a[0],eax->n,jug1->hielo,jug1->pozo,jug1->fin);
        eax = jug2->pos;
        printf("JUG 2: %s %s | Pos: %i | Hielo: %i | Pozo: %i | Fin: %i.\n",buf_n[1],buf_a[1],eax->n,jug2->hielo,jug2->pozo,jug2->fin);

        if (*j3p == 1) {
            eax = jug3->pos;
            printf("JUG 3: %s %s | Pos: %i | Hielo: %i | Pozo: %i | Fin: %i.\n",buf_n[2],buf_a[2],eax->n,jug3->hielo,jug3->pozo,jug3->fin);
            eax = jug4->pos;
            printf("JUG 4: %s %s | Pos: %i | Hielo: %i | Pozo: %i | Fin: %i.\n",buf_n[3],buf_a[3],eax->n,jug4->hielo,jug4->pozo,jug4->fin);
        }
        printf("---------------------------------------------------\n");

        if (jug1->tag != NULL) {
            tomar_turno(jug1);

            if (paso_pozo == 1) {
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
                paso_pozo = 0;
            }
        }
        if ((jug4->fin == 1) && (*j4p != 0) && (j4res==0)) {
            j4res = ubic+1;
            ubic = ubic+1;
        }
        printf("   --- Pulse cualquier tecla para proseguir ---   ");
        pausa();
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
    if (j1res==1) {
        printf("\n   %s %s SE CONDECORA CON EL PRIMER LUGAR!!!!",buf_n[0],buf_a[0]);
    }
    if (j2res==1) {
        printf("\n   %s %s SE CONDECORA CON EL PRIMER LUGAR!!!!",buf_n[1],buf_a[1]);
    }
    if (j3res==1) {
        printf("\n   %s %s SE CONDECORA CON EL PRIMER LUGAR!!!!",buf_n[2],buf_a[2]);
    }
    if (j4res==1) {
        printf("\n   %s %s SE CONDECORA CON EL PRIMER LUGAR!!!!",buf_n[3],buf_a[3]);
    }
    printf("\n          --- presione cualquier tecla para continuar.");
    pausa();
    system("clear");

    *j1p = j1res;
    *j2p = j2res;
    *j3p = j3res;
    *j4p = j4res;
    *ntiros = tiros;

    printf("\n ++++++ %i %i %i %i %i  \n", *j1p,*j2p,*j3p,*j4p,*ntiros);

    // limpieza

    free(jug1);
    free(jug2);
    free(jug3);
    free(jug4);
    limpiar_tablero(t);

}

