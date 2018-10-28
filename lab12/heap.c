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
    else /* tipo == min */
        return a.peso < b.peso;
}

Caixa cria_caixa(char nome[TAM_NOME], unsigned int peso) {
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

void sobe(p_heap p_heap, int i) {
    Caixa caixa = p_heap->vet[i];
    /* Enquanto puder subir o pai atual e descido: */
    while (i > 0 && tem_prioridade(p_heap->tipo, caixa, p_heap->vet[pai(i)])) {
        p_heap->vet[i] = p_heap->vet[pai(i)]; /* Desce o pai */
        i = pai(i);
    }
    p_heap->vet[i] = caixa; /* Nesse momento a posicao correta da caixa estara livre */
}

void insere(p_heap p_heap, Caixa caixa) {
    p_heap->vet[p_heap->n_atual] = caixa;
    sobe(p_heap, p_heap->n_atual++);
}

Caixa olha_topo(Heap heap) {
    return heap.vet[0];
}

void desce(p_heap p_heap, int i) {
    int i_esq;
    char achou_possicao = 0;
    Caixa aux = p_heap->vet[i];

    /* Enquanto puder descer o filho atual (de maior prioridade) e subido: */
    while (!achou_possicao && (i_esq = filho_esq(i)) < p_heap->n_atual) {
        int filho_prioritario = i_esq; /* Indice do filho de maior prioridade */

        int i_dir = filho_dir(i);
        /* Checa se o filho da direita, se existir, tem mais prioridade que o da esquerda: */
        if (i_dir < p_heap->n_atual && tem_prioridade(p_heap->tipo, p_heap->vet[i_dir], p_heap->vet[i_esq]))
            filho_prioritario = i_dir;

        /* Checa se o filho de maior prioridade deve ser subido (caso tenha mais prioridade que a caixa): */
        if (tem_prioridade(p_heap->tipo, p_heap->vet[filho_prioritario], aux)) {
            p_heap->vet[i] = p_heap->vet[filho_prioritario];
            i = filho_prioritario;
        } else /* Nesse ponto o indice correto da caixa foi encontrado */
            achou_possicao = 1;
    }

    p_heap->vet[i] = aux; /* Nesse momento a posicao correta da caixa estara livre */
}

Caixa pega_topo(p_heap p_heap) {
    Caixa ret = p_heap->vet[0];
    troca(&p_heap->vet[0], &p_heap->vet[--p_heap->n_atual]);
    desce(p_heap, 0);
    return ret;
}

int tamanho_atual(Heap heap) {
    return heap.n_atual;
}

void destroi_heap(Heap heap) {
    free(heap.vet);
}
