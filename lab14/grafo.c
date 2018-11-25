#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void *safe_calloc(size_t nmemb, size_t size) {
    void *ret = calloc(nmemb, size);
    if (ret == NULL) {
        printf("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    return ret;
}

Grafo cria_grafo(int n_nos) {
    Grafo ret;
    ret.n_nos = n_nos;
    ret.nos = safe_calloc(n_nos, sizeof(No_Grafo));
    return ret;
}

void insere_no(Grafo grafo, int indice_no, char idade) { /* Inserir na pratica e colocar a idade na possicao correta */
    grafo.nos[indice_no].idade = idade;
}

p_no insere_lista(p_no raiz, int indice) {
    p_no novo = safe_calloc(1, sizeof(No_Lista));
    novo->indice = indice;
    novo->prox = raiz;
    return novo;
}

void cria_conexao(Grafo grafo, int u, int v) {
    grafo.nos[u].conexoes = insere_lista(grafo.nos[u].conexoes, v);
    grafo.nos[v].conexoes = insere_lista(grafo.nos[v].conexoes, u);
}

/* Dado os indices de um triangulo checa se e um grupo entediado: */
char estam_entediados(Grafo grafo, int i_a, int i_b, int i_c) {
    char a = grafo.nos[i_a].idade, b = grafo.nos[i_b].idade, c = grafo.nos[i_c].idade;
    int soma = a + b + c;
    return soma > 6 * a || soma > 6 * b || soma > 6 * c; /* Equivalente a checar se media > 2Xi */
}

/* Coloca no resultado se cada no do grafo esta na intersecsao (2), ou esta em apenas uma das listas (1): */
void interseccao(char *resultado, p_no lista_a, p_no lista_b) {
    p_no i;
    for (i = lista_a; i != NULL; i = i->prox)
        resultado[i->indice] += 1;

    for (i = lista_b; i != NULL; i = i->prox)
        resultado[i->indice] += 1;
}

char *entediados(Grafo grafo) {
    int i, j;
    p_no conexao;
    char *ret = safe_calloc(grafo.n_nos, sizeof(char)), *aux = safe_calloc(grafo.n_nos, sizeof(char));

    /* Para cada conexao de cada no: */
    for (i = 0; i < grafo.n_nos; i++)
        for (conexao = grafo.nos[i].conexoes; conexao != NULL; conexao = conexao->prox)
            if (conexao->indice > i) { /* Evita checar cada grupo (triangulo) mais de uma vez */
                /* Como os dois nos atuais (i e conexao->indice) estam ligados, basta que um terceiro no
                 * esteja na interseccao das duas listas de adjacencia para que os tres formem um triangulo: */
                interseccao(aux, grafo.nos[i].conexoes, grafo.nos[conexao->indice].conexoes);

                /* Percorre todos os triangulos formados pelos no i e a conexao atual: */
                for (j = 0; j < grafo.n_nos; j++) {
                    /* Adiciona os nos do triangulo caso este seja um grupo entediado: */
                    if (aux[j] == 2 && estam_entediados(grafo, i, conexao->indice, j))
                        ret[i] = ret[conexao->indice] = ret[j] = 1;
                    aux[j] = 0; /* Zera o auxiliar para a proxima conexao */
                }
            }

    free(aux);
    return ret;
}

void destroi_lista(p_no lista) {
    if (lista != NULL) {
        destroi_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(Grafo grafo) {
    int i;
    for (i = 0; i < grafo.n_nos; i++)
        destroi_lista(grafo.nos[i].conexoes);
    free(grafo.nos);
}
