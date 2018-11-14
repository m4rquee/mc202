#ifndef MC202_GRAFO_H
#define MC202_GRAFO_H

typedef struct No_Lista {
    int indice;
    struct No_Lista *prox;
} No_Lista;

typedef No_Lista *p_no;

typedef struct No_Grafo {
    char idade;
    p_no conexoes;
    unsigned int filtro;
} No_Grafo;

typedef struct Grafo {
    No_Grafo *nos;
} Grafo;

void cria_grafo(int n_nos);

void insere_conexao(int indice_no, int indice_conexao);

char existe_conexao(int indice_no, int indice_conexao);

#endif
