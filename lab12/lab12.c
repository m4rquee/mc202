#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main() {
    int i, j;
    Heap aux;
    aux = cria_heap(max, 5);

    for (i = 0; i < 5; i++) {
        int n = rand() % 100;
        insere(&aux, cria_caixa("asd", n));
        printf("n = %d topo = %d\n", n, olha_topo(&aux).peso);
    }

    printf("\n");
    for (i = 0; i < 5; i++)
        printf("%i ", pega_topo(&aux).peso);
    printf("\n");

    destroi_heap(aux);
    return 0;
}
