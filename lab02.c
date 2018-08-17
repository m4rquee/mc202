#include <stdio.h>

#define MAX 312
#define get_pval(p, i, j) (p[j] - 1 == i ? 1.0f : 0.0f) /* Usado para acessar o vetor como se fosse uma matriz */

void read_vet(void *vet, int tam, char isInt) {
    int i;
    /* Decide como vai ler o input (int ou float) */
    if (isInt)
        for (i = 0; i < tam; i++)
            scanf("%d", &((int *) vet)[i]);
    else
        for (i = 0; i < tam; i++)
            scanf("%f", &((float *) vet)[i]);
}

void mul_by_pvet(int p[MAX], float B[MAX][MAX], float C[MAX][MAX], int n) {
    int i, j, k;
    float sum_aux;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            sum_aux = 0;
            for (k = 0; k < n; k++)
                sum_aux += get_pval(p, i, k) * B[k][j];

            C[i][j] = sum_aux;
        }
}

void print_mat(float C[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++)
            printf("%.1f ", C[i][j]);
        printf("%.1f\n", C[i][n - 1]);
    }
}

int main() {
    int n, i;
    int p[MAX];
    float B[MAX][MAX], C[MAX][MAX];

    scanf("%d", &n);
    read_vet(p, n, 1);
    for (i = 0; i < n; i++)
        read_vet(B[i], n, 0);

    mul_by_pvet(p, B, C, n);
    print_mat(C, n);

    return 0;
}