#ifndef MC202_HASH_H
#define MC202_HASH_H

#define MAX 64
#define TAM_NOME 19 /* Inicial mais sobrenome */

typedef struct Autor {
    char nome[TAM_NOME];
    /* Cada bit indica uma colaboracao entre esse autor e o autor no heap na mesma possicao que o bit,
     * ou seja e uma especie de vetor caracteristico: */
    unsigned long long conexoes;
} Autor;

typedef Autor *p_autor;

typedef struct Hash {
    p_autor vetor;
} Hash;

Hash criar_hash();

void insere(Hash hash, char nome[TAM_NOME]);

char contem(Hash hash, char nome[TAM_NOME], int *pos);

void atualiza_conexoes(Hash hash, char nome[TAM_NOME], unsigned long long novas_conexoes);

char possui_conexao(Hash hash, char nome[TAM_NOME], unsigned long long conexao);

void destroi_hash(Hash hash);

/* A remocao nao e nescessaria */

#endif
