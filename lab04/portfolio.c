#include <stdio.h>
#include <string.h>
#include "portfolio.h"

portfolio criar_portfolio(char *nome, char *sobrenome) {
    portfolio ret;
    strcpy(ret.nome, nome);
    strcpy(ret.sobrenome, sobrenome);
    ret.n_acoes = 0;

    return ret;
}

portfolio adicionar_acao(portfolio p, acao a) {
    p.acoes[p.n_acoes] = a;
    p.n_acoes += 1;
    return p;
}

void criar_relatorio(portfolio p) {
    int i;
    printf("Relatorio de %s %s\n", p.nome, p.sobrenome);

    for (i = 0; i < p.n_acoes; i++)
        reportar_acao(p.acoes[i]);
}