#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.c"
int paso_pozo;
int tiros;
extern char buf_a[4][25];
extern char buf_n[4][25];

char buf_a[4][25];
char buf_n[4][25];

void generar_cola(alum*p);
void recorrer(alum*pc);
// mecanicas
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
//prendas
int nprenda(int c);
void prenda(oca*verde);
//juego
void jugar(int *ju1p,int *ju2p,int *ju3p,int *ju4p,int *numtir);
void crear(casilla *p, int g);
void recorrer_c(casilla * p);
void cargar_c(casilla * m);
void archivar(casilla * p);
void limpiar_tablero(casilla * p);
void tomar_turno(oca * verde);
//cola
void recorrer(alum*pc);
void encolar(alum *pc, alum*nv);
void generar_cola(alum*p);
//arbol
void enarbolar(nodo * top, alum * gan, int tiradas);
void recorrer_a(nodo * top);

void pausa() {
    char uj = fgetc(stdin);
    uj = fgetc(stdin);
}

void buffear(alum *j1,int n){

    printf("BUFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");

    if (j1 != NULL) {
        printf("\n  buf %s - alum %s   \n",buf_a[n-1],j1->apellido);
        strcpy(buf_a[n-1],j1->apellido);
        strcpy(buf_n[n-1],j1->nombre);
        printf("\n  buf %s - alum %s   \n",buf_a[n-1],j1->apellido);
    }

    printf("BUFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4\n");
}
int main () {
    srand(time(NULL));
    printf("-------------------------------------------------------\n");
    printf("------------    OOO     EL JUEGO       ----------------\n");
    printf("------------   OOOO     DE LA          ----------------\n");
    printf("------------     OO     OCA            ----------------\n");
    printf("------------     OO                    ----------------\n");
    printf("------------     OOO                   ----------------\n");
    printf("------------     OOOOOOOOOOOOOOOOO     ----------------\n");
    printf("------------      OOOOOOOOOOOOOO       ----------------\n");
    printf("------------         OOOOOOOO          ----------------\n");
    printf("-------------------------------------------------------\n");
    printf("  BIENVENIDO AL JUEGO DE LA OCA!!!\n  Esperamos que disfrute de esta actividad recreativa.\n-------------------------------------------------------\n   --- Pulse cualquier tecla para continuar ---\n");
    pausa();
    system("clear");
    // cola
    alum *pc = malloc(sizeof(*pc));  /*primer nodo de la cola que siempre va a estar vacio*/
    generar_cola(pc); // primer nodo estara vacio
    recorrer(pc);

    printf("\n   --- Pulse cualquier tecla para continuar ---");
    pausa();
    system("clear");

    // buffer en 0
    strcpy(buf_a[0],"000");
    strcpy(buf_a[1],"000");
    strcpy(buf_a[2],"000");
    strcpy(buf_a[3],"000");
    strcpy(buf_n[0],"000");
    strcpy(buf_n[1],"000");
    strcpy(buf_n[2],"000");
    strcpy(buf_n[3],"000");
    printf("\n    %s \n",buf_n[0]);

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
    strcpy(mae->apellido,"Mc.Teacher");
    strcpy(mae->nombre,"Profe");

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
            buffear(jug1,1);
            buffear(mae,2);
            printf("\ndepuracion gg: %s %s .\n",buf_n[1],buf_a[1]);
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
                buffear(jug1,1);
                buffear(jug2,2);
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
                    buffear(jug1,1);
                    buffear(jug2,2);
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
                    buffear(jug1,1);
                    buffear(jug2,2);
                    buffear(jug3,3);
                    buffear(jug4,4);
                    jugar(&j1p,&j2p,&j3p,&j4p,&numt);
                    printf("\nInicia 9 proceso de partida \n");

                    printf("\n  %i %i %i %i %i  \n", j1p,j2p,j3p,j4p,numt);

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

    /*printf("\nantes de antes de jugar!\n");
    int ju1p;
    int ju2p;
    int ju3p;
    int ju4p;
    int numtir;

    ju1p=1;
    ju2p=1;
    ju3p=1;
    ju4p=1;
    numtir=0;
    printf("\nantes de jugar!\n");
    printf("\n%i",ju1p);
    printf("\n%i",ju2p);
    printf("\n%i",ju3p);
    printf("\n%i",ju4p);
    printf("\n%i",numtir);
    fflush(stdin);
    jugar(&ju1p,&ju2p,&ju3p,&ju4p,&numtir);
    fflush(stdin);

    printf("\n despues de jugar!\n");
    printf("\n%d",ju1p);
    printf("\n%d",ju2p);
    printf("\n%d",ju3p);
    printf("\n%d",ju4p);
    printf("\n%d",numtir);

    /*printf("\n########################################\n");
    printf("\njugadores insertados 1 2 3 4 : %i %i %i %i -- Nro de tiros: %i.\n",ju1p, ju2p, ju3p, ju4p,numtir);
    printf("\n########################################\n");*/

    system("clear");
    printf("\n ---  LISTADO ALFABETICO DE GANADORES !!!!!!! --- ");
    printf("\n   (o mejor dicho arbolado?...  )");
    recorrer_a(ta);

    printf("\n\n FIN .");


    return 0;
};
