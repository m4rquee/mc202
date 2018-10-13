#include "pilha.h"
#include "jogador.h"

jogador cria_jogador(int pos) {
    jogador ret;
    ret.pontos = ret.num_as_disponiveis = 0;
    ret.pos = pos;
    return ret;
}

void adiciona_pontos(jogador *p_jogador, char carta) {
    switch (carta) {
        case AS:
            p_jogador->pontos += 11;
            p_jogador->num_as_disponiveis++;
            break;
        case DAMA:
        case VALETE:
        case REI:
            p_jogador->pontos += 10;
            break;
        default: /* Cartas 2, 3, 4, 5, 6, 7, 8, 9 e 10 */
            p_jogador->pontos += carta;
    }

    /* Quando o jogador possui um as e passa de 21 o as passa a valer 1: */
    if (p_jogador->pontos > 21 && p_jogador->num_as_disponiveis > 0) {
        p_jogador->pontos -= 10; /* Converte um as para 1 ponto */
        p_jogador->num_as_disponiveis--;
    }
}

char acabou(jogador jogador) {
    return jogador.pontos >= 21;
}
