#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

#define pos(no) ((no)->jogador.pos) /* Determina a posicao do no dado o seu jogador */

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

void insere(jogadores *p_jogadores, jogador jogador) {
    no_lista *atual = p_jogadores->comeco, *p_novo;
    if (atual == NULL || jogador.pos > pos(p_jogadores->fim)) {
        enfileira(p_jogadores, jogador);
        return;
    }

    p_novo = cria_no_lista(jogador);

    if (jogador.pos < pos(atual)) { /* Caso o novo no deva ser o primeiro */
        p_novo->proximo = atual;
        p_jogadores->comeco = p_novo;
        return;
    }

    /* O atual sempre tera um proximo, pois senao o primeiro if teria pegado: */
    while (jogador.pos > pos(atual->proximo)) /* Encontra a posicao a ser inserida */
        atual = atual->proximo;

    p_novo->proximo = atual->proximo;
    atual->proximo = p_novo;
}

void imprime_pontos(jogadores jogadores) {
    no_lista *atual;
    for (atual = jogadores.comeco; atual != NULL; atual = atual->proximo)
        printf("%u\n", atual->jogador.pontos);
}

void limpa_lista(no_lista *lista) {
    if (lista != NULL) {
        limpa_lista(lista->proximo);
        free(lista);
    }
}

void limpa_jogadores(jogadores jogadores) {
    limpa_lista(jogadores.comeco);
}
