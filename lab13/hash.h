#ifndef MC202_HASH_H
#define MC202_HASH_H

#define MAX 2048 /* 2^11 */
#define TAM_NOME 17 /* Inicial mais sobrenome */
#define TAM_UNIAO (2 * TAM_NOME - 1)

typedef struct Conexao {
    char uniao[TAM_UNIAO];
} Conexao;

typedef Conexao *p_conexao;

typedef struct Hash {
    p_conexao vetor;
} Hash;

Hash criar_hash();

void insere(Hash hash, char nome_a[TAM_NOME], char nome_b[TAM_NOME]);

char existe(Hash hash, char nome_a[TAM_NOME], char nome_b[TAM_NOME]);

void destroi_hash(Hash hash);

/* A remocao nao e nescessaria */

#endif
