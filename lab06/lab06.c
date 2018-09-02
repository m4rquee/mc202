#include <stdio.h>
#include <stdlib.h>
#include "universidade.h"

void *safe_array_malloc(int tam, size_t size) {
    void *ret = malloc(tam * size);
    if (ret == NULL)
        exit(EXIT_FAILURE);
    return ret;
}

void le_disciplinas(p_aluno aluno, int qtd) {
    int i;
    double nota;
    char disciplina[MAX_CODIGO];
    for (i = 0; i < qtd; i++) {
        scanf(" %s %lf", disciplina, &nota);
        adicionarDisciplina(aluno, disciplina, nota);
    }
}

void destroi_tudo(p_aluno *alunos, int A, p_professor *professores, int P) {
    int i;
    for (i = 0; i < A; i++)
        destruirAluno(alunos[i]);

    for (i = 0; i < P; i++)
        destruirProfessor(professores[i]);

    free(alunos);
    free(professores);
}

void imprime_salarios(p_aluno *alunos, int A, p_professor *professores, int P) {
    int i;
    double min, max;
    for (i = 0; i < P; i++) {
        obterNotasExtremas(alunos, A, professores[i]->disciplina, &min, &max);
        reajusteSalario(professores[i], (min + max) / 2);
        imprimirProfessor(professores[i]);
    }
}

int main() {
    int A, P;
    p_aluno *alunos;
    p_professor *professores;

    /* Variaveis auxiliares */
    double salario;
    int i, qtd_disciplinas;
    char nome[MAX_NOME], sobrenome[MAX_NOME], disciplina[MAX_CODIGO];

    scanf("%d", &P);
    professores = safe_array_malloc(P, sizeof(p_professor));
    for (i = 0; i < P; i++) {
        scanf("%s %s %lf %s", nome, sobrenome, &salario, disciplina);
        professores[i] = criarProfessor(nome, sobrenome, salario, disciplina);
    }

    scanf("%d", &A);
    alunos = safe_array_malloc(A, sizeof(p_aluno));
    for (i = 0; i < A; i++) {
        scanf("%s %s %d", nome, sobrenome, &qtd_disciplinas);
        alunos[i] = criarAluno(nome, sobrenome);
        le_disciplinas(alunos[i], qtd_disciplinas);
    }

    imprime_salarios(alunos, A, professores, P);
    destroi_tudo(alunos, A, professores, P);

    return 0;
}