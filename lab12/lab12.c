#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void inclui_caixa(p_heap max_heap, p_heap min_heap, Caixa nova) {
    int tam_max, tam_min;
    if (tamanho_atual(*min_heap) > 0 && tem_prioridade(max, nova, olha_topo(min_heap)))
        insere(min_heap, nova);
    else
        insere(max_heap, nova);

    tam_max = tamanho_atual(*max_heap);
    tam_min = tamanho_atual(*min_heap);
    if (tam_min > tam_max)
        insere(max_heap, pega_topo(min_heap));
    else if (tam_max - tam_min == 2)
        insere(min_heap, pega_topo(max_heap));
}

void printa_mediana(Heap max_heap, Heap min_heap) {
    Caixa topo = olha_topo(&max_heap);
    printf("%s: %d\n", topo.nome, topo.peso);
    if (tamanho_atual(max_heap) == tamanho_atual(min_heap)) {
        topo = olha_topo(&min_heap);
        printf("%s: %d\n", topo.nome, topo.peso);
    }
}

int main() {
    int N, i, peso;
    char nome[TAM_NOME];
    Heap max_heap, min_heap;

    scanf("%d", &N);
    max_heap = cria_heap(max, N / 2 + 1);
    min_heap = cria_heap(min, N / 2);

    for (i = 0; i < N; i++) {
        scanf("%s %d", nome, &peso);
        inclui_caixa(&max_heap, &min_heap, cria_caixa(nome, peso));
        printa_mediana(max_heap, min_heap);
    }

    destroi_heap(max_heap);
    destroi_heap(min_heap);
    return 0;
}
