#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.c"
int paso_pozo;

int main () {

    srand(time(NULL));

    int j1p, j2p, j3p, j4p;
    j1p=1;
    j2p=1;
    j3p=1;
    j4p=1;

    jugar(&j1p,&j2p,&j3p,&j4p);

    printf("\n########################################\n");
    printf("\njugadores insertados 1 2 3 4 : %i %i %i %i\n",j1p, j2p, j3p, j4p);
    printf("\n########################################\n");



    return 0;
};
