#ifndef MC202_PILHA_H
#define MC202_PILHA_H

#define AS 'A'
#define VALETE 'V'
#define DAMA 'D'
#define REI 'R'

typedef struct no_pilha {
    char carta;
    struct no_pilha *abaixo;
} no_pilha;

typedef no_pilha *baralho;

baralho cria_baralho(); /* Cria uma pilha vazia (NULA) */

void empilha(baralho *p_baralho, char carta);

char desempilha(baralho *p_baralho);

void limpa_baralho(baralho *p_baralho);

#endif
