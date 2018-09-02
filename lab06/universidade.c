#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "universidade.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void *safe_struct_malloc(size_t size) {
    void *ret = malloc(size);
    if (ret == NULL)
        exit(EXIT_FAILURE);
    return ret;
}

p_professor criarProfessor(char nome[], char sobrenome[], double salario, char disciplina[]) {
    p_professor ret = safe_struct_malloc(sizeof(Professor));
    strcpy(ret->nome, nome);
    strcpy(ret->sobrenome, sobrenome);
    ret->salario = salario;
    strcpy(ret->disciplina, disciplina);

    return ret;
}

void destruirProfessor(p_professor professor) {
    free(professor);
}

p_aluno criarAluno(char nome[], char sobrenome[]) {
    p_aluno ret = safe_struct_malloc(sizeof(Aluno));
    strcpy(ret->nome, nome);
    strcpy(ret->sobrenome, sobrenome);
    ret->qtd_disciplinas = 0;

    return ret;
}

void adicionarDisciplina(p_aluno aluno, char disciplina[], double nota) {
    int pos = aluno->qtd_disciplinas++;
    strcpy(aluno->disciplinas[pos], disciplina);
    aluno->notas[pos] = nota;
}

void destruirAluno(p_aluno aluno) {
    free(aluno);
}

void obterNotasExtremas(p_aluno alunos[], int qtd_alunos, char disciplina[], double *nota_min, double *nota_max) {
    int i, j;
    *nota_min = 10;
    *nota_max = 0;
    for (i = 0; i < qtd_alunos; i++) {
        for (j = 0; j < alunos[i]->qtd_disciplinas; j++) {
            if (!strcmp(alunos[i]->disciplinas[j], disciplina)) {
                *nota_min = min(*nota_min, alunos[i]->notas[j]);
                *nota_max = max(*nota_max, alunos[i]->notas[j]);
            }
        }
    }
}

void reajusteSalario(p_professor professor, double media_notas) {
    double mul = media_notas == 10 ? 1.15
                : media_notas >= 9 ? 1.1
                : media_notas >= 8.5 ? 1.05
                : 1;
    professor->salario *= mul;
}

void imprimirProfessor(p_professor professor) {
    printf("%s %s %.2f\n", professor->nome, professor->sobrenome, professor->salario);
}