#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

char eh_num(const char dado[TAM_MAX]) {
    /* Se dado[0] == '-', entao o numero e negativo, por isso dado[1] tambem e checado: */
    return ('0' <= dado[0] && dado[0] <= '9') || ('0' <= dado[1] && dado[1] <= '9');
}

expressao le_expressao() {
    Dado aux;
    TipoDado tipo;
    char buff[TAM_MAX];
    expressao esq = NULL, dir = NULL, ret;

    scanf("%s", buff);
    if (buff[0] == '(') { /* Inicio de alguma subexpressao */
        esq = le_expressao();

        scanf("%s", buff); /* Operador */
        aux = cria_operador_ou_variavel(buff[0]);

        dir = le_expressao();

        scanf("%s", buff); /* Ignora o ')' */
        tipo = caractere;
    } else if (eh_num(buff)) { /* Numero positivo ou negativo */
        aux = cria_numero(atoi(buff));
        tipo = inteiro;
    } else { /* Variavel */
        aux = cria_operador_ou_variavel(buff[0]);
        tipo = caractere;
    }

    ret = cria_expressao(aux, tipo, esq, dir);
    return ret;
}

int main() {
    expressao exp = le_expressao();
    imprime_como_exp(simplifica(exp));
    destroi_expressao(exp);
    return 0;
}
