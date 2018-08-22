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
    int i;
    acao ret;
    ret.investimento = a.investimento;
    strcpy(ret.nome, a.nome);

    for (i = 0; i < a.n_variacoes; i++)
        ret.variacoes[i] = a.variacoes[i];

    ret.variacoes[a.n_variacoes] = variacao;
    ret.n_variacoes = a.n_variacoes + 1;

    return ret;
}

void reportar_acao(acao a) {
    int i;
    double val_final = a.investimento;
    for (i = 0; i < a.n_variacoes; i++)
        val_final *= a.variacoes[i] / 100 + 1;

    char *resultado = val_final > a.investimento ? "GANHO" : "PERDA";
    printf("%s %.2f %s\n", a.nome, val_final, resultado);
}