#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hash.h"

#define e_vazio(hash, pos) (!(hash).vetor[pos].nome[0])

p_autor cria_vetor(size_t n) {
    p_autor ret = calloc(n, sizeof(Autor));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

int hash1(char nome[TAM_NOME]) {
    int i, n = 0;
    for (i = 0; i < strlen(nome); i++)
        n = (256 * n + nome[i]) % MAX;

    return n;
}

int hash2(char nome[TAM_NOME]) {
    int i, n = 0;
    /* O for e inverso ao do hash1, para diminuir a chance de que os pulos sejam iguais para inicios iguais: */
    for (i = strlen(nome) - 1; i >= 0; i--)
        n = (256 * n + nome[i]) % MAX;

    return n | 1; /* Garante que sera impar, ou seja co-primo a MAX */
}

Hash criar_hash() {
    Hash ret;
    ret.vetor = cria_vetor(MAX);
    return ret;
}

void insere(Hash hash, char nome[TAM_NOME]) {
    int atual, ini = hash1(nome), pulo = hash2(nome);
    atual = ini;

    do {
        if (e_vazio(hash, atual)) { /* Achou a possicao onde deve ser inserida */
            strcpy(hash.vetor[atual].nome, nome);
            return;
        } else if (strcmp(hash.vetor[atual].nome, nome) == 0) /* Ja existe */
            return;

        atual = (atual + pulo) % MAX; /* O vetor e "circular" */
    } while (ini != atual); /* A condicao evita loop */
}

int busca(Hash hash, char nome[TAM_NOME]) { /* Posicao do elemento no vetor, retorna -1 caso nao exista */
    int atual, ini = hash1(nome), pulo = hash2(nome);
    atual = ini;

    do {
        if (e_vazio(hash, atual)) /* Se existisse o elemento deveria estar aqui */
            return -1;
        else if (strcmp(hash.vetor[atual].nome, nome) == 0) /* Achou o autor */
            return atual;

        atual = (atual + pulo) % MAX; /* O vetor e "circular" */
    } while (ini != atual); /* A condicao evita loop */

    return -1;
}

void atualiza_conexoes(Hash hash, char nome[TAM_NOME], int64_t novas_conexoes) {
    int pos = busca(hash, nome);
    if (pos != -1)
        hash.vetor[pos].conexoes |= novas_conexoes;
}

char possui_conexao(Hash hash, char nome[TAM_NOME], int64_t conexao) {
    int pos = busca(hash, nome);
    /* Como cada bit representa uma conexao, ao fazer o "ou bit a bit" o valor nao se altera caso a conexao exista: */
    return pos != -1 && (hash.vetor[pos].conexoes | conexao) == hash.vetor[pos].conexoes;
}

void destroi_hash(Hash hash) {
    free(hash.vetor);
}
