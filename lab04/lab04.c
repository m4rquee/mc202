#include <stdio.h>
#include "acao.h"
#include "portfolio.h"

int main() {
    acao ac;
    portfolio p;

    int N, M;
    double double_aux;
    char nome[MAX_SIZE_NAME], sobrenome[MAX_SIZE_NAME], i, j;

    scanf("%s %s %d", nome, sobrenome, &N);
    p = criar_portfolio(nome, sobrenome);

    for (i = 0; i < N; i++) {
        scanf("%s %lf %d", nome, &double_aux, &M);
        ac = criar_acao(nome, double_aux);

        for (j = 0; j < M; j++) {
            scanf("%lf", &double_aux);
            ac = adicionar_variacao(ac, double_aux);
        }
        p = adicionar_acao(p, ac);
    }

    criar_relatorio(p);

    return 0;
}