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

p_no insere(p_no raiz, unsigned int chave) {
    if (raiz == NULL)
        return cria_no(chave, rand() % 100);

    if (chave < raiz->chave) {
        raiz->esq = insere(raiz->esq, chave);
        raiz->esq->pai = raiz;
        if (raiz->esq->prioridade > raiz->prioridade)
            raiz = rotaciona_para_direita(raiz);
    } else {
        raiz->dir = insere(raiz->dir, chave);
        raiz->dir->pai = raiz;
        if (raiz->dir->prioridade > raiz->prioridade)
            raiz = rotaciona_para_esquerda(raiz);
    }

    return raiz;
}

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
        // TODO
        if ((*raiz)->esq != NULL)
            *raiz = rotaciona_para_direita(*raiz);
        else
            *raiz = rotaciona_para_esquerda(*raiz);
    }

    if (chave < (*raiz)->chave)
        return remove_chave(&(*raiz)->esq, chave);
    else
        return remove_chave(&(*raiz)->dir, chave);
}

void destroi_arvore(p_no raiz) {
    if (raiz->esq != NULL)
        destroi_arvore(raiz->esq);
    if (raiz->dir != NULL)
        destroi_arvore(raiz->dir);

    free(raiz);
}
