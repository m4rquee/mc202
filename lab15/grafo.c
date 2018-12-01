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
    p_novo->indice = indice;
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

char esta_vazia(Fila fila) {
    return fila.comeco == NULL;
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

void adiciona_grupo(Grafo grafo, int pos) {
    grafo.nos[pos].n_grupos++;
}

void busca_em_largura(Grafo grafo, int *distancias, int pos) {
    int v;
    Fila fila;
    p_no conexao;
    char *visitados = safe_calloc(grafo.n_nos, sizeof(char));

    for (v = 0; v < grafo.n_nos; v++) /* No inicio e considerado que nao existe caminho entre os nos */
        distancias[v] = -1;

    fila = cria_fila();
    enfileira(&fila, pos);

    visitados[pos] = 1;
    distancias[pos] = 0; /* A distancia de um no a ele mesmo e zero */
    while (!esta_vazia(fila)) {
        v = desenfileira(&fila);
        for (conexao = grafo.nos[v].conexoes; conexao != NULL; conexao = conexao->prox) {
            if (!visitados[conexao->indice]) {
                visitados[conexao->indice] = 1;
                /* Como fizemos o melhor caminho ate v, a distancia do atual ao inicial e a distancia ate v mais um: */
                distancias[conexao->indice] = distancias[v] + 1;

                /* So precisamos enfileirar um no se este cria uma "ponte" entre grupos: */
                if (grafo.nos[conexao->indice].n_grupos > 1)
                    enfileira(&fila, conexao->indice);
            }
        }
    }

    free(visitados);
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
