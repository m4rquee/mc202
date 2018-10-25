#ifndef MC202_HEAP_H
#define MC202_HEAP_H

#define TAM_NOME 20 + 1

typedef enum Tipo_Heap {
    max, min
} Tipo_Heap;

typedef struct Caixa {
    char nome[TAM_NOME];
    int peso;
} Caixa;

typedef Caixa *p_caixa;

typedef struct Heap {
    Tipo_Heap tipo;
    p_caixa vet;
    int n_atual, n_max;
} Heap;

typedef Heap *p_heap;

Caixa cria_caixa(char nome[TAM_NOME], int peso);

Heap cria_heap(Tipo_Heap tipo, int n_max);

void insere(p_heap heap, Caixa caixa);

Caixa olha_topo(p_heap heap);

Caixa pega_topo(p_heap heap)

#endif
