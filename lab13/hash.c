#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hash.h"

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
    for (i = 0; i < TAM_NOME; i++)
        n = (256 * n + nome[i]) % MAX;

    return n;
}

int hash2(char nome[TAM_NOME]) {
    int i, n = 0;
    for (i = TAM_NOME - 1; i >= 0; i--)
        n = (256 * n + nome[i]) % MAX;

    return n | 1; /* Garante que sera impar, ou seja co-primo a MAX */
}

Hash criar_hash() {
    Hash ret;
    ret.vetor = cria_vetor(MAX);
    return ret;
}

void insere(Hash hash, char nome[TAM_NOME]) {
    int ini;
    int cod = ini = hash1(nome), pulo = hash2(nome);

    do {
        if (!hash.vetor[cod].nome[0]) { /* Checa se a posicao e vazia */
            strcpy(hash.vetor[cod].nome, nome);
            return;
        } else if (strcmp(nome, hash.vetor[cod].nome) == 0) /* Ja existe */
            return;

        cod = (cod + pulo) % MAX; /* O vetor e "circular" */
    } while (ini != cod); /* A condicao evita loop */
}

char contem(Hash hash, char nome[TAM_NOME], int *pos) {
    int ini;
    int cod = ini = hash1(nome), pulo = hash2(nome);
    *pos = -1; /* Indica que nao existe */

    do {
        if (!hash.vetor[cod].nome[0]) /* Checa se a posicao e vazia */
            return 0;
        else if (strcmp(nome, hash.vetor[cod].nome) == 0) { /* Achou o autor */
            *pos = cod;
            return 1;
        }

        cod = (cod + pulo) % MAX; /* O vetor e "circular" */
    } while (ini != cod); /* A condicao evita loop */

    return 0;
}

void atualiza_conexoes(Hash hash, char nome[TAM_NOME], unsigned long long novas_conexoes) {
    int pos;
    if (contem(hash, nome, &pos))
        hash.vetor[pos].conexoes |= novas_conexoes;
}

char possui_conexao(Hash hash, char nome[TAM_NOME], unsigned long long conexao) {
    int pos;
    /* Como cada bit representa uma conexao, ao fazer o "ou bit a bit" o valor nao se altera caso a conexao exista: */
    return contem(hash, nome, &pos) && (hash.vetor[pos].conexoes | conexao == hash.vetor[pos].conexoes);
}

void destroi_hash(Hash hash) {
    free(hash.vetor);
}
