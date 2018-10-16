#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

char is_binary_search_r(p_node raiz, int *aux_min, int *aux_max) {
    int min, max;
    *aux_min = *aux_max = min = max = raiz->data;

    if (!raiz->esq && !raiz->dir)
        return 1;

    if (raiz->esq) {
        is_binary_search_r(raiz->esq, aux_min, aux_max);
        if (raiz->data < *aux_max)
            return 0;
        min = *aux_min;
    }

    if (raiz->dir) {
        is_binary_search_r(raiz->dir, aux_min, aux_max);
        if (raiz->data > *aux_min)
            return 0;
        max = *aux_max;
    }

    *aux_min = min;
    *aux_max = max;

    return 1;
}

char is_binary_search(p_node arvore) {
    char ret;
    int min, max;
    ret = is_binary_search_r(arvore, &min, &max);
    return ret;
}

void print_tree(p_node arvore) {
    if (arvore == NULL)
        return;


    if (arvore->esq) {
        printf("(");
        print_tree(arvore->esq);
        printf(") <- ");
    }

    printf("%i", arvore->data);

    if (arvore->dir) {
        printf(" -> (");
        print_tree(arvore->dir);
        printf(")");
    }
}

int main() {
    int i;
    p_node my_tree = NULL;
    srand((unsigned int) time(NULL));

    for (i = 0; i < 10; i++)
        my_tree = insert(my_tree, rand() % 501);

    print_tree(my_tree);
    printf("\n");
    printf("%s\n", is_binary_search(my_tree) ? "Is binary" : "Isn't binary");
    return 0;
}