#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void *safe_calloc(size_t nmemb, size_t size) {
    void *ret = calloc(nmemb, size);
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

Grafo cria_grafo(int n_nos) {
    Grafo ret;
    ret.n_nos = n_nos;
    ret.adjacencias = safe_calloc(n_nos, sizeof(p_no));
    return ret;
}

p_no insere_lista(p_no raiz, int indice) {
    p_no novo = safe_calloc(1, sizeof(No_Lista));
    novo->indice = indice;
    novo->prox = raiz;
    return novo;
}

void cria_conexao(Grafo grafo, int u, int v) {
    grafo.adjacencias[u] = insere_lista(grafo.adjacencias[u], v);
    grafo.adjacencias[v] = insere_lista(grafo.adjacencias[v], u);
}

void destroi_lista(p_no lista) {
    if (lista != NULL) {
        destroi_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(Grafo grafo) {
    int i;
    for (i = 0; i < grafo.n_nos; i++)
        destroi_lista(grafo.adjacencias[i]);
    free(grafo.adjacencias);
}
