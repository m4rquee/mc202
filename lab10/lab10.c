#include "arvore.h"

int main() {
    expressao aux = le_expressao();
    aux = simplifica(aux);
    imprime_como_exp(aux);
    return 0;
}
