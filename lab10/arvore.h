#ifndef MC202_ARVORE_H
#define MC202_ARVORE_H

#define TAM_MAX 12 /* Tamanho do maior int possivel (em caracteres) -2147483648 */

typedef enum TipoDado {
    inteiro, caractere
} TipoDado;

typedef union Dado {
    int numero;
    char operador_ou_variavel;
} Dado;

typedef struct No {
    Dado dado;
    TipoDado tipo;
    struct No *esq, *dir;
} No;

typedef No *expressao;

expressao cria_expressao(Dado dado, TipoDado tipo, expressao esq, expressao dir);

void imprime_como_exp(expressao exp);

expressao simplifica(expressao exp);

expressao le_expressao();

void destroi_expressao(expressao exp);

#endif
