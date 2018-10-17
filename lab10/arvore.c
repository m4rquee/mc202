#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define eh_folha(exp) (!(exp)->esq && !(exp)->dir) /* Uma folha e uma varialvel ou um numero */

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

void imprime_como_exp_r(expressao exp) {
    if (eh_folha(exp)) {
        if (exp->tipo == inteiro)
            printf("%i", exp->dado.numero);
        else if (exp->tipo == caractere)
            printf("%c", exp->dado.operador_ou_variavel);
    } else {
        printf("( ");
        imprime_como_exp_r(exp->esq);
        printf(" %c ", exp->dado.operador_ou_variavel);
        imprime_como_exp_r(exp->dir);
        printf(" )");
    }
}

void imprime_como_exp(expressao exp) {
    imprime_como_exp_r(exp);
    printf(" \n");
}

expressao simplifica(expressao exp) {
    if (eh_folha(exp)) /* Numero ou variavel */
        return exp;

    exp->esq = simplifica(exp->esq);
    exp->dir = simplifica(exp->dir);

    if (exp->esq->tipo == inteiro && exp->dir->tipo == inteiro) {
        exp->tipo = inteiro;

        switch (exp->dado.operador_ou_variavel) {
            case '+':
                exp->dado.numero = exp->esq->dado.numero + exp->dir->dado.numero;
                break;
            case '-':
                exp->dado.numero = exp->esq->dado.numero - exp->dir->dado.numero;
                break;
            case '*':
                exp->dado.numero = exp->esq->dado.numero * exp->dir->dado.numero;
                break;
            case '/':
                exp->dado.numero = exp->esq->dado.numero / exp->dir->dado.numero;
                break;
        }

        free(exp->esq);
        free(exp->dir);
        exp->esq = exp->dir = NULL;
    }

    return exp;
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

void destroi_expressao(expressao exp) {
    if (exp->esq)
        destroi_expressao(exp->esq);
    if (exp->dir)
        destroi_expressao(exp->dir);

    free(exp);
}
