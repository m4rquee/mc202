#ifndef MC202_HEAP_H
#define MC202_HEAP_H

#define TAM_NOME 21

typedef enum Tipo_Heap {
    max, min
} Tipo_Heap;

typedef struct Caixa {
    char nome[TAM_NOME];
    unsigned int peso;
} Caixa;

typedef Caixa *p_caixa;

/* Nao e necessario armazenar o tamanho maximo do heap, pois em nenhum momento ele sera acessado: */
typedef struct Heap {
    Tipo_Heap tipo;
    p_caixa vet;
    int n_atual;
} Heap;

typedef Heap *p_heap;

char tem_prioridade(Tipo_Heap tipo, Caixa a, Caixa b); /* Dependendo do tipo checa se a > b ou a < b */

Caixa cria_caixa(char nome[TAM_NOME], unsigned int peso);

Heap cria_heap(Tipo_Heap tipo, int n_max);

void insere(p_heap p_heap, Caixa caixa);

Caixa olha_topo(Heap heap); /* Retorna o topo sem retira-lo */

Caixa pega_topo(p_heap p_heap);

int tamanho_atual(Heap heap);

void destroi_heap(Heap heap);

#endif
