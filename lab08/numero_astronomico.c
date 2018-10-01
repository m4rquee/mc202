#include <stdio.h>
#include <stdlib.h>
#include "numero_astronomico.h"

no *cria_no(char digito) {
    no *ret = malloc(sizeof(no));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    ret->digito = digito;
    ret->anterior = ret->proximo = NULL;
    return ret;
}

numero_ast cria_numero() {
    numero_ast ret;
    ret.comeco = ret.fim = NULL;
    return ret;
}

void adiciona(numero_ast *num, char digito, char no_fim) {
    no *novo = cria_no(digito);
    if (num->comeco == NULL)  /* Nesse caso o fim tambem sera nulo, ou seja lista vazia */
        num->comeco = num->fim = novo;
    else {
        if (no_fim) {
            novo->anterior = num->fim;
            num->fim->proximo = novo;
            num->fim = novo;
        } else {
            novo->proximo = num->comeco;
            num->comeco->anterior = novo;
            num->comeco = novo;
        }
    }
}

void limpa_r(no *atual) {
    if (atual->proximo != NULL)
        limpa_r(atual->proximo);

    free(atual);
}

void limpa(numero_ast *num) { /* Casca que depois de liberar memoria zera o comeco e o fim */
    if (num->comeco != NULL) {
        limpa_r(num->comeco);
        num->comeco = num->fim = NULL;
    }
}

void print_r(no *comeco) {
    printf("%c", comeco->digito + ZERO);
    if (comeco->proximo != NULL)
        print_r(comeco->proximo);
}

void print_num(numero_ast num) {
    if (num.comeco != NULL) {
        print_r(num.comeco);
        printf("\n");
    }
}

/* Percorre somando os digitos de B em A, do final pro comeco, assim como em uma soma feita a mao.
 * Quando A nao possui mais espaco, novos nos sao criados: */
void soma(numero_ast *A, numero_ast B) {
    char carry = 0, soma, dig_b; /* O carry representa a parte que passou de 9 na soma de digitos */
    no *a = A->fim, *b = B.fim;

    /* O loop para caso B acabe primeiro, otimizando a funcao. Quando B acaba
     * ainda e preciso repassar o carry (caso existir): */
    while (b != NULL || carry != 0) {
        /* Avanca se B nao acabou, senao o digito 0 e usado como padrao: */
        if (b != NULL) {
            dig_b = b->digito;
            b = b->anterior;
        } else
            dig_b = 0;

        if (a == NULL) { /* Se o numero A acabar um novo no e criado no comeco */
            adiciona(A, 0, 0);
            a = A->comeco;
        }

        soma = a->digito + dig_b + carry;
        carry = (char) (soma / 10);
        a->digito = (char) (soma % 10);

        a = a->anterior; /* O numero A e aumentado aos poucos diferente de B que precisa de validacao */
    }
}