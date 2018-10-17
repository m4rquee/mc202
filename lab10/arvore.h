#ifndef MC202_ARVORE_H
#define MC202_ARVORE_H

#define TAM_MAX 12 /* Tamanho do maior int possivel (em caracteres): -2147483648 */

typedef enum TipoDado {
    inteiro, caractere
} TipoDado;

typedef union Dado {
    int numero;
    char operador_ou_variavel; /* Pode ser uma letra, +, -, * ou / */
} Dado;

/* No com uma Tagged Union: */
typedef struct No {
    Dado dado;
    TipoDado tipo; /* Indica qual o tipo do dado na Union */
    struct No *esq, *dir;
} No;

typedef No *expressao; /* Arvore de expressao */

expressao cria_expressao(Dado dado, TipoDado tipo, expressao esq, expressao dir);

void imprime_como_exp(expressao exp);

expressao simplifica(expressao exp); /* Simplifica quando possivel */

expressao le_expressao(); /* Essa funcao foi criada aqui para evitar o acesso direto das estruturas */

void destroi_expressao(expressao exp);

#endif
