#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "heap.h"

#define filho_esq(i) (2 * (i) + 1)
#define filho_dir(i) (2 * (i) + 2)
#define pai(i) ((i - 1) / 2)

p_caixa cria_vetor(int n) {
    p_caixa ret = malloc(n * sizeof(Caixa));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

void troca(p_caixa a, p_caixa b) {
    Caixa aux = *a;
    *a = *b;
    *b = aux;
}

char tem_prioridade(Tipo_Heap tipo, int a, int b) {
    switch (tipo) {
        case max:
            return a > b;
        case min:
            return a < b;
    }
}

Caixa cria_caixa(char nome[TAM_NOME], int peso) {
    Caixa ret;
    strcpy(ret.nome, nome);
    ret.peso = peso;
    return ret;
}

Heap cria_heap(Tipo_Heap tipo, int n_max) {
    Heap ret;
    ret.tipo = tipo;
    ret.n_atual = 0;
    ret.n_max = n_max;
    ret.vet = cria_vetor(n_max);
    return ret;
}

void sobe(p_heap heap, int i) {
    Caixa caixa = heap->vet[i];
    while (i > 0 && tem_prioridade(heap->tipo, caixa.peso, heap->vet[pai(i)].peso)) {
        heap->vet[i] = heap->vet[pai(i)];
        i = pai(i);
    }
    heap->vet[i] = caixa;
}

void insere(p_heap heap, Caixa caixa) {
    heap->vet[heap->n_atual] = caixa;
    sobe(heap, heap->n_atual++);
}

Caixa olha_topo(p_heap heap) {
    return heap->vet[heap->n_atual - 1];
}

void desce(p_heap heap, int i) {
    Caixa caixa = heap->vet[i];
    int p_esq, p_dir;
    do {
    } while (i < heap->n_atual - 1);
    heap->vet[i] = caixa;
}

Caixa pega_topo(p_heap heap) {
    Caixa ret = heap->vet[0];
    troca(&heap->vet[0], &heap->vet[--heap->n_atual]);
    desce(heap, 0);
    return ret;
}