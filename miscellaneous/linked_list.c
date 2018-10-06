#include <stdio.h>
#include <stdlib.h>

#define TAM 5

typedef struct no {
    char dado;
    struct no *prox;
} no;

no *adiciona(no *lista, char dado) {
    no *novo = malloc(sizeof(no));
    novo->dado = dado;
    novo->prox = lista;
    return novo;
}

void del(no *lista) {
    if (lista != NULL) {
        del(lista->prox);
        free(lista);
    }
}

void print_lista(no *lista) {
    if (lista != NULL) {
        printf("%i -> ", lista->dado);
        print_lista(lista->prox);
    } else {
        printf("∅\n");
    }
}

no *inverte(no *lista) {
    no *aux;

    if (lista == NULL || lista->prox == NULL)
        return lista;

    aux = inverte(lista->prox);
    lista->prox->prox = lista;
    lista->prox = NULL;

    return aux;
}

int main() {
    char i;
    no *lista = NULL;

    for (i = TAM; i > 0; --i)
        lista = adiciona(lista, i);

    printf("Antes:\n");
    print_lista(lista);

    lista = inverte(lista);

    printf("Depois:\n");
    print_lista(lista);

    del(lista);
    return 0;
}