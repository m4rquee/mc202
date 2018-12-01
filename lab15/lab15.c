#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int *safe_array_malloc(int n) {
    int *ret = malloc(n * sizeof(int));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

void imprime_resultado(int *distancias, int n) {
    int i, max = 0;
    for (i = 0; i < n; i++) {
        max = MAX(max, distancias[i]);
        if (distancias[i] == -1) /* Nao existe caminho que ligue os nos */
            printf("%d ", i);
    }

    printf("- %d\n", max);
}

void le_grupo(Grafo grafo) {
    int tam, i, j, aux, *pessoas;

    scanf("%d", &tam);
    pessoas = safe_array_malloc(tam);

    for (i = 0; i < tam; i++) { /* Le todas as pessoas */
        scanf("%d", &aux);
        pessoas[i] = aux;
        adiciona_grupo(grafo, aux);
    }

    /* Adiciona uma conexao entre todas as pessoas do grupo: */
    for (i = 0; i < tam - 1; i++)
        for (j = i + 1; j < tam; j++)
            cria_conexao(grafo, pessoas[i], pessoas[j]);

    free(pessoas);
}

/* Vale notar que nas entradas existem pares de nos em mais de um grupo, isso criara mais de uma conexao entre os nos.
* So que tratar isso necessitaria de uma busca na lista de adjacencias. Visto que essa propriedade nao influencia em
* nada, e que os grafos das entradas sao esparsos foi optado por ignorar esse fato. */
int main() {
    int n, k, i;
    Grafo grafo;
    int *distancias;

    scanf("%d %d", &n, &k);
    grafo = cria_grafo(n);
    distancias = safe_array_malloc(n);

    for (i = 0; i < k; i++)
        le_grupo(grafo);

    for (i = 0; i < n; i++) { /* Para cada no realiza a busca */
        busca_em_largura(grafo, distancias, i);
        imprime_resultado(distancias, n);
    }

    free(distancias);
    destroi_grafo(grafo);
    return 0;
}
