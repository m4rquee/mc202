#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "treap.h"

int main() {
    unsigned int i;
    p_no aux = cria_arvore();

    srand((unsigned) time(NULL)); /* Coloca o horario atual como seed do gerador de numeros */

    for (i = 0; i < 5; i++)
        aux = insere(aux, i);

    for (i = 0; i < 5; i++)
        remove_chave(&aux, i);

    return 0;
}
