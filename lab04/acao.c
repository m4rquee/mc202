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