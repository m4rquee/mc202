#ifndef MC202_ARVORE_H
#define MC202_ARVORE_H

#define TAM_MAX 12 /* Tamanho do maior int possivel (em caracteres) -2147483648 */

typedef struct No {
    char dado[TAM_MAX]; /* Pode ser um operador ou uma constante/variavel */
    struct No *esq, *dir;
} No;

typedef No *expressao;

expressao cria_arvore(char dado[TAM_MAX], expressao esq, expressao dir);

void imprime(expressao raiz);

expressao simplifica(expressao raiz);

char e_num(char dado[TAM_MAX]);

#endif
