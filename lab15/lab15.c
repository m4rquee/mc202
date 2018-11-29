#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int *safe_array_malloc(int n) {
    int *ret = malloc(n * sizeof(int));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

void le_grupo(Grafo grafo) {
    int tam, i, j, aux, *pessoas;

    scanf("%d", &tam);
    pessoas = safe_array_malloc(tam);

    for (i = 0; i < tam; i++) {
        scanf("%d", &aux);
        pessoas[i] = aux;
    }

    for (i = 0; i < tam - 1; i++)
        for (j = i; j < tam; j++)
            cria_conexao(grafo, i, j);

    free(pessoas);
}

int main() {
    int n, k, i;
    Grafo grafo;

    scanf("%d %d", &n, &k);
    grafo = cria_grafo(n);

    for (i = 0; i < k; i++)
        le_grupo(grafo);

    destroi_grafo(grafo);
    return 0;
}
