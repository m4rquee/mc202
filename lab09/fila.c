#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

no_lista *cria_no_lista(jogador jogador) {
    no_lista *ret = calloc(1, sizeof(no_lista)); /* Inicia todos os valores com 0 */
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    ret->jogador = jogador;
    return ret;
}

jogadores cria_jogadores() {
    jogadores ret;
    ret.comeco = ret.fim = NULL;
    return ret;
}

void enfileira(jogadores *p_jogadores, jogador jogador) {
    no_lista *p_novo = cria_no_lista(jogador);
    if (p_jogadores->comeco == NULL) /* Lista vazia */
        p_jogadores->comeco = p_novo;
    else
        p_jogadores->fim->proximo = p_novo;

    p_jogadores->fim = p_novo;
}

jogador desenfileira(jogadores *p_jogadores) {
    no_lista *primeiro = p_jogadores->comeco;
    jogador ret = primeiro->jogador;
    p_jogadores->comeco = p_jogadores->comeco->proximo;

    if (p_jogadores->comeco == NULL) /* Ao remover o ultimo no */
        p_jogadores->fim = NULL;

    free(primeiro);
    return ret;
}

char esta_vazia(jogadores jogadores) {
    return jogadores.comeco == NULL;
}

void limpa_lista(no_lista *lista) {
    if (lista != NULL) {
        limpa_lista(lista->proximo);
        free(lista);
    }
}

void limpa_jogadores(jogadores *p_jogadores) {
    limpa_lista(p_jogadores->comeco);
    p_jogadores->comeco = p_jogadores->fim = NULL;
}
