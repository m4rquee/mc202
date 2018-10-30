#include <stdio.h>
#include "heap.h"

void inclui_caixa(p_heap max_heap, p_heap min_heap, Caixa nova) {
    int tam_max, tam_min;
    /* Caso a caixa seja maior que o minimo da direita ela e inserida na direita, senao e colocada na esquerda: */
    if (tamanho_atual(*min_heap) > 0 && tem_prioridade(max, nova, olha_topo(*min_heap)))
        insere(min_heap, nova);
    else
        insere(max_heap, nova);

    tam_max = tamanho_atual(*max_heap);
    tam_min = tamanho_atual(*min_heap);
    /* Garante que a esquerda e sempre maior ou igual a direita: */
    if (tam_min > tam_max)
        insere(max_heap, pega_topo(min_heap));
    else if (tam_max - tam_min == 2) /* Garante que os selecionados estejam no topo dos heaps (o meio) */
        insere(min_heap, pega_topo(max_heap));
}

void printa_selecionados(Heap max_heap, Heap min_heap) {
    Caixa topo = olha_topo(max_heap);
    printf("%s: %d\n", topo.nome, topo.peso);

    /* Caso de numero par: */
    if (tamanho_atual(max_heap) == tamanho_atual(min_heap)) {
        topo = olha_topo(min_heap);
        printf("%s: %d\n", topo.nome, topo.peso);
    }
}

/* Imaginando os dados ordenados (em ordem crescente), basta dividi-los ao meio (no caso de numero impar
 * a esquerda e maior) que os selecionados seram o maximo da esquerda e o minimo da direta (no caso de numero
 * par de valores): */
int main() {
    int N, i;
    unsigned int peso;
    char nome[TAM_NOME];
    Heap max_heap, min_heap;

    scanf("%d", &N);
    /* O heap da esquerda (max_heap) e sempre maior ou igual ao da direita (min_heap), por isso +1: */
    max_heap = cria_heap(max, N / 2 + 1);
    min_heap = cria_heap(min, N / 2 + N % 2);

    for (i = 0; i < N; i++) {
        scanf("%s %u", nome, &peso);
        inclui_caixa(&max_heap, &min_heap, cria_caixa(nome, peso));
        printa_selecionados(max_heap, min_heap);
    }

    destroi_heap(max_heap);
    destroi_heap(min_heap);
    return 0;
}
