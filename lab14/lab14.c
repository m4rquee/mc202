#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

Grafo inicializa_grafo(int n, int m) {
    int i, idade, u, v;
    Grafo grafo = cria_grafo(n);

    for (i = 0; i < n; i++) { /* Le todas as idades */
        scanf("%d", &idade);
        insere_no(grafo, i, (char) idade);
    }

    for (i = 0; i < m; i++) { /* Le todas as conexoes */
        scanf("%d %d", &u, &v);
        cria_conexao(grafo, u, v);
    }

    return grafo;
}

int main() {
    int n, m, i;
    Grafo grafo;
    char *resultado;

    scanf("%d %d", &n, &m);
    grafo = inicializa_grafo(n, m);

    /* Calcula e printa todos os nos que estam em um grupo entediado: */
    resultado = entediados(grafo);
    for (i = 0; i < n; i++)
        if (resultado[i])
            printf("%d\n", i);

    free(resultado);
    destroi_grafo(grafo);
    return 0;
}
