#include "arvore.h"

int main() {
    expressao exp = le_expressao();
    imprime_como_exp(simplifica(exp));
    destroi_expressao(exp);
    return 0;
}
