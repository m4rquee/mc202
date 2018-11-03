#ifndef MC202_TREAP_H
#define MC202_TREAP_H

typedef struct No_treap {
    unsigned int chave;
    int prioridade;
    struct No_treap *esq, *dir;
} No_treap;

typedef No_treap *p_no;

p_no cria_arvore();

p_no insere(p_no raiz, unsigned int chave);

/**A funcao de busca nao foi usada, pois e mais eficiente tentar remover do que checar se existe primeiro para depois
 * decidir se remove ou se insere**/
p_no busca(p_no raiz, unsigned int chave);

char remove_chave(p_no *raiz, unsigned int chave); /* Remove uma chave e no caso de nao existir retorna 0 */

void imprime_decrescente(p_no raiz);

void destroi_arvore(p_no raiz);

#endif
