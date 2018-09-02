#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MUL 2
#define TAM_NOME 30
#define TAM_MAX_INI 4

typedef struct participante {
    char nome[TAM_NOME];
    int telefone;
} participante;

participante *safe_malloc(int tam) {
    participante *ret = malloc(tam * sizeof(participante));
    if (ret == NULL)
        exit(EXIT_FAILURE);
    return ret;
}

participante *realloc_array(participante *array, int tam_atual) {
    participante *novo_array = safe_malloc(MUL * tam_atual);
    memcpy(novo_array, array, tam_atual * sizeof(participante));
    free(array);
    return novo_array;
}

participante le_participante() {
    participante ret;
    scanf("%s %d", ret.nome, &ret.telefone);
    return ret;
}

participante *le_participantes(int *tam_atual, int *k) {
    int tam_max = TAM_MAX_INI;
    participante *participantes, aux;

    participantes = safe_malloc(tam_max);

    aux = le_participante();
    while (strcmp(aux.nome, "fim")) {
        if (*tam_atual == tam_max) {
            participantes = realloc_array(participantes, tam_max);
            tam_max *= MUL;
        }

        participantes[*tam_atual] = aux;
        *tam_atual += 1;
        aux = le_participante();
    }
    *k = aux.telefone - 1; /* Para reutilizar codigo uso a mesma estrutura de participante */

    return participantes;
}

int comparador(const void *x, const void *y) { /* Funcionamento analogo a strcmp */
    int tel_x = ((participante *) x)->telefone;
    int tel_y = ((participante *) y)->telefone;
    return tel_x - tel_y;
}

int main() {
    int tam = 0, k;
    participante *participantes;

    participantes = le_participantes(&tam, &k);
    qsort(participantes, (unsigned int) tam, sizeof(participante), comparador);
    printf("%s %d\n", participantes[k].nome, participantes[k].telefone);

    free(participantes);
    return 0;
}