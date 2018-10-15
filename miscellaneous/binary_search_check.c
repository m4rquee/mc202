#include <stdlib.h>
#include <stdio.h>

typedef struct tree_node {
    int data;
    struct tree_node *dir;
    struct tree_node *esq;
} tree_node;

typedef tree_node *p_node;

p_node insert(p_node tree, int data) {
    p_node new;
    if (tree == NULL) {
        new = calloc(1, sizeof(tree_node));
        new->data = data;
        return new;
    }

    if (data == tree->data)
        return tree;
    else if (data > tree->data) {
        tree->dir = insert(tree->dir, data);
    } else {
        tree->esq = insert(tree->esq, data);
    }
}

/* Use min and max comming from childreen */
char is_binary_search_r(p_node arvore, int *aux_d, int *aux_e) {
    char ret;
    if (!arvore->dir && !arvore->esq) {
        *aux_d = *aux_e = arvore->data;
        return 1;
    }

    if ((arvore->dir && !is_binary_search_r(arvore->dir, aux_d, aux_d)) ||
        (arvore->esq && !is_binary_search_r(arvore->esq, aux_e, aux_e)))
        return 0;

    ret = *aux_e < arvore->data && arvore->data < *aux_d;
    *aux_d = *aux_e = arvore->data;
    return ret;
}

char is_binary_search(p_node arvore) {
    char ret;
    int aux_d, aux_e;
    ret = is_binary_search_r(arvore, &aux_d, &aux_e);
    return ret;
}

int main() {
    int i;
    p_node my_tree = NULL;

    for (i = 0; i < 10; i++)
        my_tree = insert(my_tree, rand() % 501);

    printf("%s", is_binary_search(my_tree) ? "Is binary" : "Isn't binary");
    return 0;
}