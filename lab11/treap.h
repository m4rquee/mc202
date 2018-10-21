#ifndef MC202_TREAP_H
#define MC202_TREAP_H

typedef struct No_treap {
    struct No_treap *pai;
    unsigned int chave;
    int prioridade;
    struct No_treap *esq, *dir;
} No_treap;

typedef No_treap *p_no;

/**A funcao de busca nao foi usada, pois e mais eficiente tentar remover do que checar se existe primeiro para depois
 * decidir se remove ou se insere**/

p_no cria_arvore();

p_no insere(p_no raiz, unsigned int chave);

char remove_chave(p_no *raiz, unsigned int chave); /* Remove uma chave e no caso de nao existir retorna 0 */

void destroi_arvore(p_no raiz);


// char checa_heap(p_no raiz);

// char checa_bst(p_no raiz, unsigned int min, unsigned int max);

// char checa_pais(p_no raiz);

#endif
