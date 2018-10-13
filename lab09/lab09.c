#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "pilha.h"

#define FIM '#'
#define HIT 'H'
#define STAND 'S'

char le_entrada() {
    char buff[3];
    scanf("%s", buff);
    if ('0' <= buff[0] && buff[0] <= '9')
        return (char) atoi(buff);
    else
        return buff[0];
}

void efetua_hit(jogadores *p_jogadores, char carta, jogadores *p_stand) {
    /* Remove do comeco e insere no final para criar o ciclo: */
    jogador aux = desenfileira(p_jogadores);
    adiciona_pontos(&aux, carta);
    if (acabou(aux))
        insere(p_stand, aux);
    else
        enfileira(p_jogadores, aux);
}

/* Alem de criar a lista de jogadores, distribui as cartas iniciais. Aplica as regras de finalizacao: */
jogadores inicia_jogadores(int n, baralho *p_baralho, jogadores *p_stand) {
    int i;
    jogadores ret = cria_jogadores();

    /* O ultimo jogador sera o dealer: */
    for (i = 0; i < n; i++) /* Cria jogadores vazios com uma posicao, que sera usada para manter a ordem do print */
        enfileira(&ret, cria_jogador(i));

    for (i = 0; i < 2 * n; i++) /* Distribuicao de cartas iniciais */
        efetua_hit(&ret, desempilha(p_baralho), p_stand);

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
    baralho baralho;
    jogadores jogadores, stand = cria_jogadores();

    scanf("%i %i", &m, &n);
    baralho = le_baralho(m);
    jogadores = inicia_jogadores(n + 1, &baralho, &stand);

    while ((comando = le_entrada()) != FIM) {
        if (comando == HIT)
            efetua_hit(&jogadores, desempilha(&baralho), &stand);
        else if (comando == STAND)
            insere(&stand, desenfileira(&jogadores)); /* Coloca o jogador na posicao correta */
        else /* Caso da trapaca */
            empilha(&baralho, comando);
    }

    /* Repassa os jogadores restantes (caso houver) para os finalizados: */
    while (jogadores.comeco != NULL)
        insere(&stand, desenfileira(&jogadores));

    imprime_pontos(stand);

    /* Nao e necessario limpar a fila de jogadores, pois todos foram finalizados: */
    limpa_baralho(baralho);
    limpa_jogadores(stand);
    return 0;
}
