#include <stdio.h>
#include <string.h>
#include "acao.h"

acao criar_acao(char *nome, double investimento) {
    acao ret;
    ret.investimento = investimento;
    strcpy(ret.nome, nome);
    ret.n_variacoes = 0;

    return ret;
}

acao adicionar_variacao(acao a, double variacao) {
    a.variacoes[a.n_variacoes] = variacao;
    a.n_variacoes += 1;
    return a;
}

void reportar_acao(acao a) {
    int i;
    char *resultado;
    double val_final = a.investimento;

    for (i = 0; i < a.n_variacoes; i++)
        val_final *= a.variacoes[i] / 100 + 1;

    resultado = val_final > a.investimento ? "GANHO" : "PERDA";
    printf("%s %.2f %s\n", a.nome, val_final, resultado);
}