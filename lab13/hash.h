#ifndef MC202_HASH_H
#define MC202_HASH_H

#define MAX 2048 /* 2^11 */
#define MAX_AUTORES 64 /* O maximo de autores possiveis em um artigo, para que nao ultrapasse 2^11 colaboracoes */

#define TAM_NOME 17 /* Inicial mais sobrenome */
#define TAM_UNIAO (2 * TAM_NOME - 1) /* Dois nomes concatenados */

typedef char Conexao[TAM_UNIAO];

typedef struct Hash {
    Conexao *vetor;
} Hash;

Hash criar_hash();

void insere(Hash hash, char nome_a[TAM_NOME], char nome_b[TAM_NOME]); /* Insere uma Conexao entre "a" e "b" */

char existe(Hash hash, char nome_a[TAM_NOME], char nome_b[TAM_NOME]); /* Checa se existe Conexao entre "a" e "b" */

void destroi_hash(Hash hash);

/* A remocao nao e nescessaria */

#endif
