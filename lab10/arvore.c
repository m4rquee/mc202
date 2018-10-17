#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

#define eh_folha(exp) (!(exp)->esq && !(exp)->dir) /* Uma folha pode ser uma varialvel ou um numero */

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
    /* Uma expressao e uma variavel/numero ou um operador com duas subexpressoes: */
    if (eh_folha(exp)) {
        if (exp->tipo == inteiro)
            printf("%i ", exp->dado.numero);
        else if (exp->tipo == caractere)
            printf("%c ", exp->dado.operador_ou_variavel);
    } else {
        printf("( ");
        imprime_como_exp_r(exp->esq);

        printf("%c ", exp->dado.operador_ou_variavel);

        imprime_como_exp_r(exp->dir);
        printf(") ");
    }
}

void imprime_como_exp(expressao exp) {
    imprime_como_exp_r(exp);
    printf("\n");
}

expressao simplifica(expressao exp) {
    if (eh_folha(exp))
        return exp;

    /* A partir daqui sabemos que o no e um operador: */
    exp->esq = simplifica(exp->esq);
    exp->dir = simplifica(exp->dir);

    /* So e possivel simplificar caso os dois filhos sejam numeros: */
    if (exp->esq->tipo == inteiro && exp->dir->tipo == inteiro) {
        switch (exp->dado.operador_ou_variavel) { /* Realiza a operacao e coloca no atual */
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
            default:
                printf("Operador nao suportado!");
                exit(EXIT_FAILURE);
        }

        exp->tipo = inteiro; /* O no atual deixa de ser um operador */

        /* Os filhos nao seram mais usados: */
        free(exp->esq);
        free(exp->dir);
        exp->esq = exp->dir = NULL;
    }

    return exp;
}

Dado cria_numero(int numero) {
    Dado ret;
    ret.numero = numero;
    return ret;
}

Dado cria_operador_ou_variavel(char operador_ou_variavel) {
    Dado ret;
    ret.operador_ou_variavel = operador_ou_variavel;
    return ret;
}

void destroi_expressao(expressao exp) {
    if (exp->esq)
        destroi_expressao(exp->esq);
    if (exp->dir)
        destroi_expressao(exp->dir);

    free(exp);
}
