#ifndef MC202_HASH_H
#define MC202_HASH_H

#include <stdint.h> /* Como a versao do C usada no susy e muito antiga "long long" nao existe e tive que usar int64_t */

#define MAX 64
#define TAM_NOME 17 /* Inicial mais sobrenome */

typedef struct Autor {
    char nome[TAM_NOME];
    /* Cada bit indica uma colaboracao entre esse autor e o autor no heap da mesma possicao que o bit,
     * ou seja, e uma especie de vetor caracteristico: */
    int64_t conexoes;
} Autor;

typedef Autor *p_autor;

typedef struct Hash {
    p_autor vetor;
} Hash;

Hash criar_hash();

void insere(Hash hash, char nome[TAM_NOME]);

int busca(Hash hash, char nome[TAM_NOME]);

void atualiza_conexoes(Hash hash, char nome[TAM_NOME], int64_t novas_conexoes);

char possui_conexao(Hash hash, char nome[TAM_NOME], int64_t conexao);

void destroi_hash(Hash hash);

/* A remocao nao e nescessaria */

#endif
