#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hash.h"

#define e_vazio(hash, pos) (!(hash).vetor[pos][0])

Conexao *cria_vetor(size_t n) {
    Conexao *ret = calloc(n, sizeof(Conexao));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

void une_nomes(char dest[TAM_UNIAO], char nome_a[TAM_NOME], char nome_b[TAM_NOME]) {
    /* Garante que nao importara a ordem dos nomes na hora de fazer o hash: */
    if (strcmp(nome_a, nome_b) > 0) {
        strcpy(dest, nome_a);
        strcat(dest, nome_b);
    } else {
        strcpy(dest, nome_b);
        strcat(dest, nome_a);
    }
}

int hash1(char str[TAM_NOME]) {
    int i, n = 0;

    for (i = 0; i < strlen(str); i++)
        n = (256 * n + str[i]) % MAX;

    return n;
}

int hash2(char str[TAM_NOME]) {
    int i, n = 0;

    /* Os for sao o inverso do hash1, para diminuir a chance de que os pulos sejam iguais para inicios iguais: */
    for (i = (int) strlen(str) - 1; i >= 0; i--)
        n = (256 * n + str[i]) % MAX;

    return n | 1; /* Garante que sera impar, ou seja co-primo a MAX */
}

Hash criar_hash() {
    Hash ret;
    ret.vetor = cria_vetor(MAX);
    return ret;
}

void insere(Hash hash, char nome_a[TAM_NOME], char nome_b[TAM_NOME]) {
    int atual, ini, pulo;
    char uniao[TAM_UNIAO];

    une_nomes(uniao, nome_a, nome_b);
    atual = ini = hash1(uniao);
    pulo = hash2(uniao);

    do {
        if (e_vazio(hash, atual)) { /* Achou a possicao onde deve ser inserido */
            strcpy(hash.vetor[atual], uniao);
            return;
        } else if (strcmp(hash.vetor[atual], uniao) == 0) /* Ja existe */
            return;

        atual = (atual + pulo) % MAX; /* O vetor e "circular" */
    } while (ini != atual); /* A condicao evita loop */
}

char existe(Hash hash, char nome_a[TAM_NOME], char nome_b[TAM_NOME]) {
    int atual, ini, pulo;
    char uniao[TAM_UNIAO];

    une_nomes(uniao, nome_a, nome_b);
    atual = ini = hash1(uniao);
    pulo = hash2(uniao);

    do {
        if (e_vazio(hash, atual)) /* Se existisse o elemento deveria estar aqui */
            return 0;
        else if (strcmp(hash.vetor[atual], uniao) == 0) /* Achou o autor */
            return 1;

        atual = (atual + pulo) % MAX; /* O vetor e "circular" */
    } while (ini != atual); /* A condicao evita loop */

    return 0;
}

void destroi_hash(Hash hash) {
    free(hash.vetor);
}
