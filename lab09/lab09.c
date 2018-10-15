#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "pilha.h"

#define FIM '#'
#define HIT 'H'
#define STAND 'S'

jogador *safe_array_malloc(int tam) {
    jogador *ret = malloc(tam * sizeof(jogador));
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

void imprime_pontos(jogador *stand, int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%u\n", stand[i].pontos);
}

char le_entrada() {
    char buff[3];
    scanf("%s", buff);
    if ('0' <= buff[0] && buff[0] <= '9')
        return (char) atoi(buff);
    else
        return buff[0];
}

void efetua_hit(jogadores *p_jogadores, char carta, jogador *stand) {
    /* Remove do comeco e insere no final para criar o efeito de ciclo: */
    jogador aux = desenfileira(p_jogadores);
    adiciona_pontos(&aux, carta);
    if (acabou(aux))
        stand[aux.pos] = aux; /* Coloca o jogador mantendo a ordem de saida */
    else
        enfileira(p_jogadores, aux);
}

/* Alem de criar a lista de jogadores, distribui as cartas iniciais. Aplica as regras de finalizacao: */
jogadores inicia_jogadores(int n, baralho *p_baralho, jogador *stand) {
    int i;
    jogadores ret = cria_jogadores();

    /* O ultimo jogador sera o dealer: */
    for (i = 0; i < n; i++) /* Cria jogadores vazios com uma posicao, que sera usada para manter a ordem do print */
        enfileira(&ret, cria_jogador(i));

    for (i = 0; i < 2 * n; i++) /* Distribuicao de cartas iniciais */
        efetua_hit(&ret, desempilha(p_baralho), stand);

    return ret;
}

baralho le_baralho(int m) {
    int i;
    baralho ret = cria_baralho();
    for (i = 0; i < m; i++)
        empilha(&ret, le_entrada());
    return ret;
}

int main() {
    int m, n;
    char comando;
    jogador *stand;
    baralho baralho;
    jogadores jogadores;

    scanf("%i %i", &m, &n);
    baralho = le_baralho(m);
    stand = safe_array_malloc(n + 1); /* Vetor onde fica os jogadores que acabaram */
    jogadores = inicia_jogadores(n + 1, &baralho, stand);

    while ((comando = le_entrada()) != FIM) {
        if (comando == HIT)
            efetua_hit(&jogadores, desempilha(&baralho), stand);
        else if (comando == STAND) {
            jogador aux = desenfileira(&jogadores);
            stand[aux.pos] = aux;
        } else /* Caso da trapaca */
            empilha(&baralho, comando);
    }

    /* Repassa os jogadores restantes (caso houver) para stand: */
    while (!esta_vazia(jogadores)) {
        jogador aux = desenfileira(&jogadores);
        stand[aux.pos] = aux;
    }

    imprime_pontos(stand, n + 1);

    /* Nao e necessario limpar a fila de jogadores, pois nesse ponto ela estara vazia: */
    limpa_baralho(&baralho);
    free(stand);
    return 0;
}
