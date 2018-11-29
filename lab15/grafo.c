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

/* Fila -------------------------------------------------------------------------: */

typedef struct Fila {
    No *comeco;
    No *fim;
} Fila;

typedef Fila *p_fila;

Fila cria_fila() {
    Fila ret;
    ret.comeco = ret.fim = NULL;
    return ret;
}

void enfileira(p_fila fila, int indice) {
    p_no p_novo = safe_calloc(1, sizeof(No));
    if (fila->comeco == NULL) /* Lista vazia */
        fila->comeco = p_novo;
    else
        fila->fim->prox = p_novo;

    fila->fim = p_novo;
}

int desenfileira(p_fila fila) {
    p_no primeiro = fila->comeco;
    int ret = primeiro->indice;
    fila->comeco = fila->comeco->prox;

    if (fila->comeco == NULL) /* Ao remover o ultimo no */
        fila->fim = NULL;

    free(primeiro);
    return ret;
}

/* Grafo ------------------------------------------------------------------------: */

Grafo cria_grafo(int n_nos) {
    Grafo ret;
    ret.n_nos = n_nos;
    ret.nos = safe_calloc(n_nos, sizeof(No_Grafo));
    return ret;
}

p_no insere_lista(p_no raiz, int indice) {
    p_no novo = safe_calloc(1, sizeof(No));
    novo->indice = indice;
    novo->prox = raiz;
    return novo;
}

void cria_conexao(Grafo grafo, int u, int v) {
    grafo.nos[u].conexoes = insere_lista(grafo.nos[u].conexoes, v);
    grafo.nos[v].conexoes = insere_lista(grafo.nos[v].conexoes, u);
}

void busca_em_largura(Grafo grafo, int pos) {
    int w, v;
    char *visitados = safe_calloc(grafo.n_nos, sizeof(char));
    char *distancias = safe_calloc(grafo.n_nos, sizeof(char));
    Fila aux = cria_fila();
    enfileira(&aux, pos);

    free(visitados);
    free(distancias);
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
        destroi_lista(grafo.nos[i].conexoes);
    free(grafo.nos);
}
