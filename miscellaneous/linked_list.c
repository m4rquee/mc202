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

void print_lista_sem_loop(no *lista, char val) {
    printf("%i -> ", lista->dado);

    if (lista->prox->prox->dado != val)
        print_lista(lista->prox);
}

void print_espacos(int n) {
    char i;
    for (i = 0; i < n; i++)
        printf(" ");
}

void print_com_espacos(char *str, int espacos) {
    print_espacos(espacos);
    printf("%s", str);
}

no *inverte_visual(no *lista, int espacos) {
    no *aux;

    if (lista == NULL) {
        //print_com_espacos("Atual = NULL -> {}\n", espacos);
        return lista;
    }

    //print_espacos(espacos);
    //printf("Atual = %i -> {\n", lista->dado);

    aux = inverte_visual(lista->prox, espacos + 5);

    print_com_espacos("aux = ", espacos + 5);
    print_lista(aux);

    if (aux == NULL) {
        //print_com_espacos("}\n\n", espacos);
        return lista;
    }

    print_com_espacos("aux = ", espacos + 5);
    print_lista(aux);

    lista->prox->prox = lista;

    print_com_espacos("aux = ", espacos + 5);
    print_lista_sem_loop(aux, lista->dado);

    lista->prox = NULL;

    print_com_espacos("aux = ", espacos + 5);
    print_lista(aux);

    //print_com_espacos("}\n\n", espacos);
    return aux;
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

    for (i = TAM; i > 0; --i) {
        lista = adiciona(lista, i);
    }

    printf("Antes:\n");
    print_lista(lista);

    printf("\nInvercao:\n");
    lista = inverte(lista);

    printf("Depois:\n");
    print_lista(lista);

    del(lista);
    return 0;
}