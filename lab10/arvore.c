#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

No *cria_no(Dado dado, TipoDado tipo) {
    No *ret = malloc(sizeof(No));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    ret->dado = dado;
    ret->tipo = tipo;
    return ret;
}

expressao cria_expressao(Dado dado, TipoDado tipo, expressao esq, expressao dir) {
    expressao ret = cria_no(dado, tipo);
    ret->esq = esq;
    ret->dir = dir;
    return ret;
}

void imprime_como_exp(expressao raiz) {
    printf("( ");
    if (raiz->esq)
        imprime_como_exp(raiz->esq);

    if (raiz->tipo == caractere)
        printf("%c ", raiz->dado.operador_ou_variavel);
    else if (raiz->tipo == inteiro)
        printf("%d ", raiz->dado.numero);

    if (raiz->dir)
        imprime_como_exp(raiz->dir);
    printf(") ");
}

expressao simplifica(expressao raiz) {
    if (!raiz->esq && !raiz->dir)
        return raiz;

    if (raiz->esq->tipo == inteiro && raiz->dir->tipo == inteiro)
        switch (raiz->dado.operador_ou_variavel) {
            default:
                raiz->tipo = inteiro;
                raiz->esq = simplifica(raiz->esq);
                raiz->dir = simplifica(raiz->dir);
            case '+':
                raiz->dado.numero = raiz->esq->dado.numero + raiz->dir->dado.numero;
                break;
            case '-':
                raiz->dado.numero = raiz->esq->dado.numero - raiz->dir->dado.numero;
                break;
            case '*':
                raiz->dado.numero = raiz->esq->dado.numero * raiz->dir->dado.numero;
                break;
            case '/':
                raiz->dado.numero = raiz->esq->dado.numero / raiz->dir->dado.numero;
                break;
        }

    return raiz;
}

char eh_num(const char dado[TAM_MAX]) {
    return ('0' <= dado[0] && dado[0] <= '9') || ('0' <= dado[1] && dado[1] <= '9');
}

expressao le_expressao() {
    Dado aux;
    char buff[TAM_MAX];
    expressao esq, dir, ret;

    scanf("%s", buff);
    if (buff[0] == '(') {
        esq = le_expressao();
        scanf("%s", buff); /* Operador */
        aux.operador_ou_variavel = buff[0];
        dir = le_expressao();

        ret = cria_expressao(aux, caractere, esq, dir);
        scanf("%s", buff); /* Ignora o ')' */
    } else if (eh_num(buff)) {
        aux.numero = atoi(buff);
        ret = cria_expressao(aux, inteiro, NULL, NULL);
    } else { /* Variavel */
        aux.operador_ou_variavel = buff[0];
        ret = cria_expressao(aux, caractere, NULL, NULL);
    }

    return ret;
}
