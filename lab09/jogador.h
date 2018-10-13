#ifndef MC202_JOGADOR_H
#define MC202_JOGADOR_H

typedef struct jogador {
    int pos; /* Indica qual e a possicao do jogador (usado na hora de inserir ordenado) */
    unsigned char pontos;
    /* Quando o jogador passa de 21 caso ele possua um as valendo 11, ele passa a valer 1: */
    unsigned char num_as_disponiveis;
} jogador;

jogador cria_jogador(int pos);

void adiciona_pontos(jogador *p_jogador, char carta); /* Adiciona os pontos correspondentes a uma carta */

char acabou(jogador jogador); /* Checa se o jogador ja perdeu/ganhou */

#endif
