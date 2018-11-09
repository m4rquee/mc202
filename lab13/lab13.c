#include <stdio.h>
#include <memory.h>
#include "hash.h"

void atualiza_todas_conexoes(Hash hash, char nome_autores[MAX][TAM_NOME], int n_autores) {

}

int main() {
    Hash hash = criar_hash();
    unsigned long long conexao;
    char nome[TAM_NOME], separador;
    int n, m, i, n_autores = 0, pos;
    char nome_autores[MAX][TAM_NOME];

    scanf("%d %d", &n, &m);

    for (i = 0; i < n; i++) {
        scanf(" %c. %[^.,]%c", &nome[0], &nome[1], &separador);

        insere(hash, nome);
        if (separador == ',')
            strcpy(nome, nome_autores[n_autores++]);
        else /* '.' */
            atualiza_todas_conexoes(hash, nome_autores, n_autores);
    }

    for (i = 0; i < m; i++) {
        scanf(" %c. %[^.,]%c", &nome[0], &nome[1], &separador);
        pos = busca(hash, nome);
        conexao = ((unsigned long long int) 1 << pos);
        scanf(" %c. %[^.,]%c", &nome[0], &nome[1], &separador);

        printf("%c", possui_conexao(hash, nome, conexao) ? 'S' : 'N');
    }

    destroi_hash(hash);
    return 0;
}
