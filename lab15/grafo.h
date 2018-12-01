#ifndef MC202_GRAFO_H
#define MC202_GRAFO_H

typedef struct No {
    int indice;
    struct No *prox;
} No;

typedef No *p_no;

typedef struct No_Grafo {
    /* Numero de grupos em que esse no se encontra, esse numero e usado para otimizar a busca em largura. Um no so
     * precisa ser adicionado a fila se estiver em mais de um grupo, pois assim ele criara uma ponte entre grupos: */
    int n_grupos;
    p_no conexoes;
} No_Grafo;

typedef struct Grafo {
    int n_nos;
    No_Grafo *nos;
} Grafo;

Grafo cria_grafo(int n_nos);

void cria_conexao(Grafo grafo, int u, int v);

void adiciona_grupo(Grafo grafo, int pos); /* Incrementa o contador de grupos do no */

/* Coloca no vetor distancias a distancia de cada no ao no passado, usando o menor caminho.
 * Coloca -1 caso nao exista camihno entre os nos: */
void busca_em_largura(Grafo grafo, int *distancias, int pos);

void destroi_grafo(Grafo grafo);

/* A remocao nao e nescessaria */

#endif
