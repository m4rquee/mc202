#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "heap.h"

#define filho_esq(i) (2 * (i) + 1)
#define filho_dir(i) (2 * (i) + 2)
#define pai(i) ((i - 1) / 2)

char eh_maior(Tipo_Heap tipo, int a, int b) {
    if (tipo == max)
        return a > b;
    else if (tipo == min)
        return a < b;
}

void troca(p_caixa a, p_caixa b) {
    Caixa aux = *a;
    *a = *b;
    *b = aux;
}

p_caixa cria_vetor(int n) {
    p_caixa ret = malloc(n * sizeof(Caixa));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
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
    p_caixa pai = &heap->vet[pai(i)], atual = &heap->vet[i];
    if (i > 0) {
        if (eh_maior(heap->tipo, atual->peso, pai->peso)) {
            troca(pai, atual);
            sobe(heap, pai(i));
        }
    }

}

void insere(p_heap heap, Caixa caixa) {
    heap->vet[heap->n_atual] = caixa;
    sobe(heap, heap->n_atual++);
}

Caixa olha_topo(p_heap heap) {
    return heap->vet[heap->n_atual];
}

void desce(p_heap heap, int i) {
    int i_esq = filho_esq(i), i_dir = filho_dir(i);
    int p_esq = i_esq < heap->n_atual ? heap->vet[i_esq].peso : -1;
    int p_dir = i_dir < heap->n_atual ? heap->vet[i_dir].peso : -1;
    int p_atual = heap->vet[i].peso;

    if (i_esq < heap->n_atual) {
        if (eh_maior(heap->tipo, i_esq, p_atual) || eh_maior(heap->tipo, i_dir, p_atual)) {

        }
    }
}

Caixa pega_topo(p_heap heap) {
    Caixa ret = heap->vet[0];
    troca(&heap->vet[0], &heap->vet[--heap->n_atual]);
    desce(heap, 0);
    return ret;
}