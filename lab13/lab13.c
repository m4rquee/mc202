#include <stdio.h>
#include <memory.h>
#include <stdint.h>
#include "hash.h"

#define cria_con(pos) ((int64_t) 1 << (pos))

void atualiza_todas_conexoes(Hash hash, char nome_autores[MAX][TAM_NOME], int n_autores) {
    int i, pos;
    int64_t conexoes = 0;

    /* Coloca uma conexao em cada bit representado por um autor da lista: */
    for (i = 0; i < n_autores; i++) {
        pos = busca(hash, nome_autores[i]);
        conexoes |= cria_con(pos); /* Coloca o bit na possicao correta */
    }

    /* Atualiza as conexoes de cada autor para a lista de bits gerada (um autor vai ter uma conexao para si mesmo,
     * mas isso e irrelevante): */
    for (i = 0; i < n_autores; i++)
        atualiza_conexoes(hash, nome_autores[i], conexoes);
}

void le_nome(char nome[TAM_NOME], char *separador) {
    scanf(" %c. %[^.,]%c", &nome[0], &nome[1], separador);
}

int main() {
    int64_t conexao;
    Hash hash = criar_hash();
    int n, m, i, n_autores = 0, pos;
    char nome[TAM_NOME], separador, nome_autores[MAX][TAM_NOME];

    scanf("%d %d", &n, &m);

    /* Le todos os artigos e atualiza as conexoes (colaboracoes) entre os autores: */
    for (i = 0; i < n;) {
        le_nome(nome, &separador);

        insere(hash, nome);
        strcpy(nome_autores[n_autores++], nome);

        if (separador == '.') { /* Acabou a leitura do artigo atual */
            i++;
            atualiza_todas_conexoes(hash, nome_autores, n_autores);
            n_autores = 0;
        }
    }

    /* Realiza as consultas: */
    for (i = 0; i < m; i++) {
        le_nome(nome, &separador);
        pos = busca(hash, nome);

        if (pos != -1) {
            conexao = cria_con(pos);
            le_nome(nome, &separador);
            printf("%c\n", possui_conexao(hash, nome, conexao) ? 'S' : 'N');
        } else { /* Nao existe na lista, entao nem e preciso continuar */
            le_nome(nome, &separador); /* Ignora o nome */
            printf("%c\n", 'N');
        }
    }

    destroi_hash(hash);
    return 0;
}
