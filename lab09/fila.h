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

void enfileira(jogadores *p_jogadores, jogador jogador); /* Adiciona um no ao final da fila */

jogador desenfileira(jogadores *p_jogadores);

void insere(jogadores *p_jogadores, jogador jogador); /* Insere um jogador mantendo a ordem crescente */

void imprime_pontos(jogadores jogadores);

void limpa_jogadores(jogadores jogadores);

#endif
