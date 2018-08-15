#include <stdio.h>
#include <string.h>

#define MAX 40

void read_vet(int vet[MAX], int tam) {
    int i;
    for (i = 0; i < tam; i++)
        scanf("%d", &vet[i]);
}

/* Algoritmo de Diferenca Simetrica com O(mn) no pior caso */
int main() {
    int A[MAX], B[MAX];
    int m, n, i, j, tem;

    scanf("%d %d", &m, &n);
    read_vet(A, m);
    read_vet(B, n);

    /* Primeira parte: Os elementos de A que nao estao em B sao printados (menos o ultimo elemento) */
    for (i = 0; i < m - 1; i++) {
        tem = 0;
        for (j = 0; j < n; j++)
            if (A[i] == B[j]) { /* Caso B contenha o elemento atual a possicao j de B e removida: */
                tem = 1;
                memmove(&B[j], &B[j + 1], (n - j - 1) * sizeof(int)); /* Remove a posicao j de B */
                n--;
                break;
            }

        if (!tem)
            printf("%d ", A[i]);
    }

    /* Segunda parte: Os elementos de B que nao sao iguais ao ultimo elemento de A sao printados */
    tem = 0;
    for (i = 0; i < n; i++)
        if (B[i] != A[m - 1])
            printf("%d ", B[i]);
        else
            tem = 1;

    /* Caso B nao contenha o ultimo elemento de A: */
    if (!tem)
        printf("%d ", A[m - 1]);

    return 0;
}