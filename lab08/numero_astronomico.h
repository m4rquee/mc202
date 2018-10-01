#ifndef NUMERO_ASTRONOMICO_H
#define NUMERO_ASTRONOMICO_H

#define ZERO '0' /* Usado para converter entre o digito e seu caractere */

typedef struct no {
    struct no *anterior;
    char digito;
    struct no *proximo;
} no;

/* Cabeca da lista (representa um unico numero): */
typedef struct lista {
    no *comeco;
    no *fim;
} numero_ast;

numero_ast cria_numero(); /* Cria um numero com comeco e fim nulos */

/* A adicao no fim e usada durante a leitura de um novo numero, e no comeco quando a soma nao cabe no numero: */
void adiciona(numero_ast *num, char digito, char no_fim);

void limpa(numero_ast *num); /* Libera a memoria alocada para o numero, colocando nulo no comeco e no fim */

void print_num(numero_ast num);

void soma(numero_ast *A, numero_ast B); /* Realiza a soma dos digitos de B em A, alterando o numero A */

#endif