#include <stdio.h>
#include "hash.h"

void le_nome(char nome[TAM_NOME], char *separador) {
    scanf(" %c. %[^.,]%c", &nome[0], &nome[1], separador);
}

void atualiza_todas_conexoes(Hash hash, char nome_autores[MAX][TAM_NOME], int n_autores) {
    int i, j;

    for (i = 0; i < n_autores - 1; i++)
        for (j = i + 1; j < n_autores; j++)
            insere(hash, nome_autores[i], nome_autores[j]);
}

char realiza_consuta(Hash hash) {
    char nome1[TAM_NOME], nome2[TAM_NOME], sep;
    le_nome(nome1, &sep);
    le_nome(nome2, &sep);

    return existe(hash, nome1, nome2);
}

int main() {
    Hash hash = criar_hash();
    int n, m, i, n_autores = 0;
    /* O numero maximo de autores e o dobro do de colaboracoes (cada autor e ligadado a um unico outro): */
    char separador, nome_autores[2 * MAX][TAM_NOME];

    scanf("%d %d", &n, &m);

    /* Le todos os artigos e atualiza as conexoes (colaboracoes) entre os autores: */
    for (i = 0; i < n;) {
        le_nome(nome_autores[n_autores++], &separador);

        if (separador == '.') { /* Acabou a leitura do artigo atual */
            i++;
            atualiza_todas_conexoes(hash, nome_autores, n_autores);
            n_autores = 0;
        }
    }

    /* Realiza todas as consultas: */
    for (i = 0; i < m; i++)
        printf("%c\n", realiza_consuta(hash) ? 'S' : 'N');

    destroi_hash(hash);
    return 0;
}
