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

char tem_prioridade(Tipo_Heap tipo, Caixa a, Caixa b) {
    if (tipo == max)
        return a.peso > b.peso;
    else
        return a.peso < b.peso;
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
    ret.vet = cria_vetor(n_max);
    return ret;
}

void sobe(p_heap heap, int i) {
    Caixa caixa = heap->vet[i];
    while (i > 0 && tem_prioridade(heap->tipo, caixa, heap->vet[pai(i)])) {
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
    return heap->vet[0];
}

void desce(p_heap heap, int i) {
    int i_esq;
    char achou_possicao = 0;
    Caixa aux = heap->vet[i];

    while (!achou_possicao && (i_esq = filho_esq(i)) < heap->n_atual) {
        int filho_prioritario = i_esq;
        int i_dir = filho_dir(i);
        if (i_dir < heap->n_atual && tem_prioridade(heap->tipo, heap->vet[i_dir], heap->vet[i_esq]))
            filho_prioritario = i_dir;

        if (tem_prioridade(heap->tipo, heap->vet[filho_prioritario], aux)) {
            heap->vet[i] = heap->vet[filho_prioritario];
            i = filho_prioritario;
        } else
            achou_possicao = 1;
    }

    heap->vet[i] = aux;
}

Caixa pega_topo(p_heap heap) {
    Caixa ret = heap->vet[0];
    troca(&heap->vet[0], &heap->vet[--heap->n_atual]);
    desce(heap, 0);
    return ret;
}

int tamanho_atual(Heap heap) {
    return heap.n_atual;
}

void destroi_heap(Heap heap) {
    free(heap.vet);
}
