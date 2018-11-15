#include <stdio.h>
#include "grafo.h"

int main() {
    Grafo grafo;
    int n, m, i, idade, u, v, *resultado;

    scanf("%d %d", &n, &m);
    grafo = cria_grafo(n);

    for (i = 0; i < n; i++) {
        scanf("%d", &idade);
        insere_no(grafo, i, idade);
    }

    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        cria_conexao(grafo, u, v);
    }

    resultado = entediados(grafo);
    for (i = 0; i < n; i++)
        if (resultado[i])
            printf("%d\n", i);

    destroi_grafo(grafo);
    return 0;
}
