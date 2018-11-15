#ifndef MC202_GRAFO_H
#define MC202_GRAFO_H

typedef struct No_Lista {
    int indice;
    struct No_Lista *prox;
} No_Lista;

typedef No_Lista *p_no;

typedef struct No_Grafo {
    int idade;
    p_no conexoes;
} No_Grafo;

typedef struct Grafo {
    int n_nos;
    No_Grafo *nos;
} Grafo;

Grafo cria_grafo(int n_nos);

void insere_no(Grafo grafo, int indice_no, int idade);

void cria_conexao(Grafo grafo, int u, int v); /* Insere ordenado (facilita a interseccao) */

int *entediados(Grafo grafo);

void destroi_grafo(Grafo grafo);

/* A remocao nao e nescessaria */

#endif
