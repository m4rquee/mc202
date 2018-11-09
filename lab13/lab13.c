#include <stdio.h>
#include "hash.h"

int main() {
    Hash hash = criar_hash();
    char nome[TAM_NOME], separador;

    int n, m, i;
    scanf("%d %d", &n, &m);

    for (i = 0; i < n; i++) {
        scanf(" %c. %[^.,]%c", &nome[0], &nome[1], &separador);

        insere(hash, nome);
    }

    destroi_hash(hash);
    return 0;
}
