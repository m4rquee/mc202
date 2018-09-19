#include <stdio.h>
#include <stdlib.h>

#define VAZIO 'O'
#define ESPACO ' '
#define OCUPADO '*'
#define dentro(x, MAX) ((x) < (MAX) && (x) >= 0)
#define e_vazia(lab, M, N, i, j) (dentro(i, M) && dentro(j, N) && (lab)[i][j] == VAZIO)

void *safe_calloc(int nmemb, size_t size) {
    void *ret = calloc((unsigned int) nmemb, size);
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

char **aloca_matriz(int M, int N) {
    int i;
    char **ret = safe_calloc(M, sizeof(char *));
    for (i = 0; i < M; i++)
        ret[i] = safe_calloc(N, sizeof(char));
    return ret;
}

void del_matriz(char **matriz, int M) {
    int i;
    for (i = 0; i < M; i++)
        free(matriz[i]);
    free(matriz);
}

char **le_labirinto(int M, int N) {
    int i, j;
    char **ret = aloca_matriz(M, N);
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++)
            scanf("%c", &ret[i][j]);
        getchar(); /* Ignora o \n */
    }

    return ret;
}

char gera_caminho(char ***caminho, char **lab, int M, int N, int i_i, int j_i, int i_f, int j_f) {
    if (i_i == i_f && j_i == j_f) /* Caso base */
        return (*caminho)[i_i][j_i] = 1;

    if (e_vazia(lab, M, N, i_i, j_i) && !(*caminho)[i_i][j_i]) { /* Checa se nao passou e nao tem parede */
        (*caminho)[i_i][j_i] = 1;

        if (gera_caminho(caminho, lab, M, N, i_i + 1, j_i, i_f, j_f))
            return 1;
        else if (gera_caminho(caminho, lab, M, N, i_i - 1, j_i, i_f, j_f))
            return 1;
        else if (gera_caminho(caminho, lab, M, N, i_i, j_i + 1, i_f, j_f))
            return 1;
        else if (gera_caminho(caminho, lab, M, N, i_i, j_i - 1, i_f, j_f))
            return 1;
        else
            (*caminho)[i_i][j_i] = 0; /* Caso nao encontre solucao reseta a possicao atual */
    }

    return 0;
}

void printa_caminho(char **caminho, int M, int N) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++)
            printf("%c", caminho[i][j] ? OCUPADO : ESPACO);
        printf("\n");
    }
}

int main() {
    char **labirinto, **caminho;
    int LT, CT, LE, CE, LS, CS;

    scanf("%d %d %d %d %d %d ", &LT, &CT, &LE, &CE, &LS, &CS);
    labirinto = le_labirinto(LT, CT);
    caminho = aloca_matriz(LT, CT);
    gera_caminho(&caminho, labirinto, LT, CT, LE, CE, LS, CS);
    printa_caminho(caminho, LT, CT);

    del_matriz(labirinto, LT);
    del_matriz(caminho, LT);
    return 0;
}