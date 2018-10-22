#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

#define eh_folha(no) ((no)->esq == NULL && (no)->dir == NULL)

p_no cria_no(unsigned int chave, int prioridade) {
    p_no ret = malloc(sizeof(No_treap));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    ret->chave = chave;
    ret->prioridade = prioridade;
    ret->esq = ret->dir = NULL;
    return ret;
}

p_no cria_arvore() {
    return NULL;
}

p_no rotaciona_para_esquerda(p_no raiz) {
    p_no aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;

    /* Corrige os pais: */
    aux->pai = raiz->pai;
    raiz->pai = aux;
    if (raiz->dir != NULL)
        raiz->dir->pai = raiz;

    return aux;
}

p_no rotaciona_para_direita(p_no raiz) {
    p_no aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;

    /* Corrige os pais: */
    aux->pai = raiz->pai;
    raiz->pai = aux;
    if (raiz->esq != NULL)
        raiz->esq->pai = raiz;

    return aux;
}

p_no corrige(p_no raiz) { /* Corrige a propriedade de Heap (caso estiver errada) */
    if (raiz->esq != NULL && raiz->esq->prioridade > raiz->prioridade)
        return rotaciona_para_direita(raiz);

    if (raiz->dir != NULL && raiz->dir->prioridade > raiz->prioridade)
        return rotaciona_para_esquerda(raiz);

    return raiz;
}

p_no insere(p_no raiz, unsigned int chave) {
    if (raiz == NULL)
        return cria_no(chave, rand());

    if (chave < raiz->chave) {
        raiz->esq = insere(raiz->esq, chave);
        raiz->esq->pai = raiz;
    } else {
        raiz->dir = insere(raiz->dir, chave);
        raiz->dir->pai = raiz;
    }

    return corrige(raiz);
}

/* Se o no e uma folha, ele e removido senao ele e movido para "baixo" ate que se torne uma folha */
char remove_chave(p_no *raiz, unsigned int chave) {
    if (*raiz == NULL) /* Nao achou a chave */
        return 0;

    if ((*raiz)->chave == chave) {
        if (eh_folha(*raiz)) { /* Remove o no somente se ele for uma folha */
            free(*raiz);
            *raiz = NULL;
            return 1;
        }

        /* Como o gerador gera numeros maiores que 0, faz com que o no a ser removido tenha a menor prioridade: */
        (*raiz)->prioridade = -1;
        *raiz = corrige(*raiz); /* "Desce" o no a ser removido */
    }

    if (chave < (*raiz)->chave)
        return remove_chave(&(*raiz)->esq, chave);
    else
        return remove_chave(&(*raiz)->dir, chave);
}

void imprime_decrescente_r(p_no raiz) {
    if (raiz->dir != NULL)
        imprime_decrescente_r(raiz->dir);
    printf("%u ", raiz->chave);
    if (raiz->esq != NULL)
        imprime_decrescente_r(raiz->esq);
}

void imprime_decrescente(p_no raiz) {
    imprime_decrescente_r(raiz);
    printf("\n");
}

void destroi_arvore(p_no raiz) {
    if (raiz->esq != NULL)
        destroi_arvore(raiz->esq);
    if (raiz->dir != NULL)
        destroi_arvore(raiz->dir);

    free(raiz);
}
