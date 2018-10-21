#ifndef MC202_TREAP_H
#define MC202_TREAP_H

typedef struct No_treap {
    struct No_treap *pai;
    unsigned int chave;
    int prioridade;
    struct No_treap *esq, *dir;
} No_treap;

typedef No_treap *p_no;

p_no cria_arvore();

void insere(p_no *raiz, unsigned int chave);

char inclui(p_no raiz, unsigned int chave);

char remove(p_no *raiz, unsigned int chave); /* Remove uma chave e no caso de nao existir retorna 0 */

void destroi_arvore(p_no raiz);

#endif
