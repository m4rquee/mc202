#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "numero_astronomico.h"

#define FIM '#'

numero_ast le_numero_ast() {
    char entrada, ja_comecou = 0;
    numero_ast ret = cria_numero();

    /* Le os digitos ate encontrar algo que nao seja numero (no caso \n): */
    while (isdigit(entrada = getchar())) {
        ja_comecou = ja_comecou || entrada != ZERO; /* So comeca a ler ao encontrar o primeiro digito nao zero */
        if (ja_comecou) /* Ignora os zeros a esquerda */
            adiciona(&ret, (char) (entrada - ZERO), 1);
    }

    return ret;
}

int main() {
    numero_ast buffer_calc = cria_numero(), aux;
    adiciona(&buffer_calc, 0, 0); /* Inicia o buffer da calculadora com 0 */

    while (getchar() != FIM) {
        getchar(); /* Ignora o espaco antes do numero */
        aux = le_numero_ast();
        soma(&buffer_calc, aux);
        limpa(&aux);
        print_num(buffer_calc);
    }

    limpa(&buffer_calc);
    return 0;
}