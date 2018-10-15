#ifndef MC202_FILA_H
#define MC202_FILA_H

#include "jogador.h"

typedef struct no_lista {
    jogador jogador;
    struct no_lista *proximo;
} no_lista;

typedef struct fila {
    no_lista *comeco;
    no_lista *fim;
} jogadores;

jogadores cria_jogadores(); /* Cria uma fila vazia */

void enfileira(jogadores *p_jogadores, jogador jogador);

jogador desenfileira(jogadores *p_jogadores);

char esta_vazia(jogadores jogadores);

/* Essa funcao nunca foi usada, mas foi implementada pois uma fila completa deve possui-la */
void limpa_jogadores(jogadores *p_jogadores);

#endif
