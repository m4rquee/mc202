#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "arvore.h"

expressao cria_no(char dado[TAM_MAX]) {
    expressao ret = malloc(sizeof(No));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    strcpy(ret->dado, dado);
    return ret;
}

expressao cria_arvore(char dado[TAM_MAX], expressao esq, expressao dir) {
    expressao ret = cria_no(dado);
    ret->esq = esq;
    ret->dir = dir;
    return ret;
}

void imprime_como_exp(expressao raiz) {
    printf("( ");
    if (raiz->esq)
        imprime_como_exp(raiz->esq);

    printf("%s ", raiz->dado);

    if (raiz->esq)
        imprime_como_exp(raiz->esq);
    printf(") ");
}

expressao simplifica(expressao raiz) {
    if (raiz->esq)
        raiz->esq = simplifica(raiz->esq);

    if (raiz->dir)
        raiz->dir = simplifica(raiz->dir);

    if (e_num(raiz->esq->dado) && e_num(raiz->dir->dado)) { /* Tambem significa que o atual e um operador */
        int result, esq = atoi(raiz->esq->dado), dir = atoi(raiz->dir->dado);

        switch (raiz->dado[0]) {
            case '+':
                result = esq + dir;
                break;
            case '-':
                result = esq - dir;
                break;
            case '*':
                result = esq * dir;
                break;
            case '/':
                result = esq / dir;
                break;
        }

        sprintf(raiz->dado, "%d", result);
    }

    return raiz;
}

expressao le_expressao() {
    char buff[TAM_MAX];
    expressao esq, dir;

    scanf("%s", buff);
    if (buff[0] == '(') {
        esq = le_expressao();
    } else {
        return cria_arvore(buff, NULL, NULL);
    }

    scanf("%s", buff);
    if (buff[0] == '(') {
        dir = le_expressao();
    } else {
        return cria_arvore(buff, NULL, NULL);
    }

    return cria_arvore(buff, esq, dir);
}

char e_num(char dado[TAM_MAX]) {
    return ('0' <= dado[0] && dado[0] <= '9') || ('0' <= dado[1] && dado[1] <= '9');
}
