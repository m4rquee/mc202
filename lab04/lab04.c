#include "acao.h"

int main() {
    acao ac = criar_acao("Carlos alberto", 1.2);
    ac = adicionar_variacao(ac, 1);
    ac = adicionar_variacao(ac, 2);
    ac = adicionar_variacao(ac, 3);
    return 0;
}