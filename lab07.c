#include <stdio.h>
#include <stdlib.h>

#define VAZIO 'O'
#define ESPACO ' '
#define OCUPADO '*'
#define dentro(x, MAX) (0 <= (x) && (x) < (MAX)) /* Checa se x pertence ao intervalo [0, MAX) */
/* Checa se a possicao esta disponivel para ser usada, mas antes faz uma validacao: */
#define e_vazia(lab, M, N, i, j) (dentro(i, M) && dentro(j, N) && (lab)[i][j] == VAZIO)

void *safe_malloc(size_t size) {
    void *ret = malloc(size);
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

char **aloca_matriz(int M, int N) {
    int i;
    char **ret = safe_malloc(M * sizeof(char *));
    for (i = 0; i < M; i++)
        ret[i] = safe_malloc(N * sizeof(char));
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

char gera_caminho(char **lab, int M, int N, int i_i, int j_i, int i_f, int j_f) {
    if (i_i == i_f && j_i == j_f) /* Caso base (achou a saida) */
        return lab[i_i][j_i] = OCUPADO;

    /* Checa se nao passou ainda e nao tem parede: */
    if (e_vazia(lab, M, N, i_i, j_i)) {
        lab[i_i][j_i] = OCUPADO;

        /* Tenta cada direcao possivel a partir da possicao atual: */
        if (gera_caminho(lab, M, N, i_i + 1, j_i, i_f, j_f)) /* Abaixo */
            return 1;
        else if (gera_caminho(lab, M, N, i_i - 1, j_i, i_f, j_f)) /* Acima */
            return 1;
        else if (gera_caminho(lab, M, N, i_i, j_i + 1, i_f, j_f)) /* Direita */
            return 1;
        else if (gera_caminho(lab, M, N, i_i, j_i - 1, i_f, j_f)) /* Esquerda */
            return 1;

        lab[i_i][j_i] = VAZIO; /* Caso nao encontre solucao reseta a possicao atual */
    }

    return 0;
}

void printa_caminho(char **lab, int M, int N) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++)
            printf("%c", lab[i][j] == OCUPADO ? OCUPADO : ESPACO);
        printf("\n");
    }
}

int main() {
    char **labirinto;
    int LT, CT, LE, CE, LS, CS;

    scanf("%d %d %d %d %d %d ", &LT, &CT, &LE, &CE, &LS, &CS);
    labirinto = le_labirinto(LT, CT);
    gera_caminho(labirinto, LT, CT, LE, CE, LS, CS);
    printa_caminho(labirinto, LT, CT);

    del_matriz(labirinto, LT);
    return 0;
}