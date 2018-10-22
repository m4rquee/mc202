#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

int main() {
    unsigned int N, i, M, j, num;
    p_no resultado = cria_arvore();

    srand((unsigned) time(NULL)); /* Coloca o horario atual como seed do gerador de numeros */

    scanf("%u", &N);
    for (i = 0; i < N; i++) {
        scanf("%u", &M);
        for (j = 0; j < M; j++) {
            scanf("%u", &num);
            /* Tenta remover, se nao der certo o elemento nao existe e pode ser inserido: */
            if (!remove_chave(&resultado, num))
                resultado = insere(resultado, num);
        }
    }

    imprime_decrescente(resultado);

    destroi_arvore(resultado);
    return 0;
}
