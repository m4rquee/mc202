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

p_no cria_no(int indice) {
    p_no ret = malloc(sizeof(No_Lista));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    ret->indice = indice;
    return ret;
}

Grafo cria_grafo(int n_nos) {
    Grafo ret;
    ret.n_nos = n_nos;
    ret.nos = safe_calloc(n_nos, sizeof(No_Grafo));
    return ret;
}

void insere_no(Grafo grafo, int indice_no, int idade) {
    grafo.nos[indice_no].idade = idade;
}

p_no insere_lista(p_no raiz, int x) {
    p_no novo = cria_no(x);
    novo->prox = raiz;
    return novo;
}

void cria_conexao(Grafo grafo, int u, int v) {
    grafo.nos[u].conexoes = insere_lista(grafo.nos[u].conexoes, v);
    grafo.nos[v].conexoes = insere_lista(grafo.nos[v].conexoes, u);
}

void interseccao(int *resultado, p_no a, p_no b) {
    p_no i;
    for (i = a; i != NULL; i = i->prox)
        resultado[i->indice] += 1;

    for (i = b; i != NULL; i = i->prox)
        resultado[i->indice] += 1;
}

char estam_entediados(int a, int b, int c) {
    double media = ((double) a + b + c) / 3;
    return media > 2 * a || media > 2 * b || media > 2 * c;
}

int *entediados(Grafo grafo) {
    p_no conexao;
    int i, j, *entediados, *parcial;
    entediados = safe_calloc(grafo.n_nos, sizeof(int));
    parcial = safe_calloc(grafo.n_nos, sizeof(int));

    for (i = 0; i < grafo.n_nos; i++)
        for (conexao = grafo.nos[i].conexoes; conexao != NULL; conexao = conexao->prox)
            if (conexao->indice > i) {
                interseccao(parcial, grafo.nos[i].conexoes, grafo.nos[conexao->indice].conexoes);

                for (j = 0; j < grafo.n_nos; j++) {
                    if (parcial[j] == 2 &&
                        estam_entediados(grafo.nos[i].idade, grafo.nos[conexao->indice].idade, grafo.nos[j].idade))
                        entediados[i] = entediados[conexao->indice] = entediados[j] = 1;
                    parcial[j] = 0;
                }
            }

    free(parcial);
    return entediados;
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
