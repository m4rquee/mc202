#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

no_pilha *cria_no_pilha(char carta) {
    no_pilha *ret = malloc(sizeof(no_pilha));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    ret->carta = carta;
    return ret;
}

baralho cria_baralho() {
    return NULL;
}

void empilha(baralho *p_baralho, char carta) {
    no_pilha *novo = cria_no_pilha(carta);
    novo->abaixo = *p_baralho;
    *p_baralho = novo;
}

char desempilha(baralho *p_baralho) {
    char ret;
    baralho topo = *p_baralho;
    if (topo == NULL) /* Pilha vazia */
        return 0;

    ret = topo->carta;
    *p_baralho = topo->abaixo;
    free(topo);
    return ret;
}

void limpa_baralho(baralho *p_baralho) {
    while (desempilha(p_baralho)); /* Desempilha todos os valores */
}
