#ifndef MC202_GRAFO_H
#define MC202_GRAFO_H

typedef struct No {
    int indice;
    struct No *prox;
} No;

typedef No *p_no;

typedef struct Grafo {
    int n_nos;
    p_no *adjacencias;
} Grafo;

Grafo cria_grafo(int n_nos);

void cria_conexao(Grafo grafo, int u, int v);

void busca_em_largura(Grafo grafo, int pos);

void destroi_grafo(Grafo grafo);

/* A remocao nao e nescessaria */

#endif
