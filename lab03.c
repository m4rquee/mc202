#include <stdio.h>

#define BUFF_SIZE 100

void cat(char buff[], char cmd_arg[], int *len_buff, int len_arg) {
    int i;
    for (i = 0; i < len_arg; i++)
        buff[*len_buff + i] = cmd_arg[i];

    *len_buff += len_arg;
}

char cmp(char a[], char b[], int len_a, int len_b) {
    int i;
    if (len_a != len_b)
        return 0;

    for (i = 0; i < len_a; i++)
        if (a[i] != b[i])
            return 0;

    return 1;
}

void sub(char buff[], int x, int tam, int *len_buff) {
    int i;
    for (i = 0; i < tam; i++)
        buff[i] = buff[x + i];

    *len_buff = tam;
}

void print_vet(char buff[], int len_buff) {
    int i;
    for (i = 0; i < len_buff; i++)
        printf("%c", buff[i]);

    printf("\n");
}

int str_len(char buff[]) {
    int len;
    for (len = 0; buff[len] != '\0'; len++);
    return len;
}

int main() {
    int len_buff = 0, x, tam;
    char cmd[3 + 1], is_equal;
    char buffer[BUFF_SIZE], cmd_arg[BUFF_SIZE + 1];

    do {
        scanf("%s", cmd);

        if (cmp(cmd, "CAT", 3, 3)) {
            scanf("%s", cmd_arg);
            cat(buffer, cmd_arg, &len_buff, str_len(cmd_arg));
            print_vet(buffer, len_buff);
        } else if (cmp(cmd, "CMP", 3, 3)) {
            scanf("%s", cmd_arg);
            is_equal = cmp(buffer, cmd_arg, len_buff, str_len(cmd_arg));
            printf("%s\n", is_equal ? "IGUAL" : "DIFERENTE");
        } else if (cmp(cmd, "SUB", 3, 3)) {
            scanf("%d %d", &x, &tam);
            sub(buffer, x, tam, &len_buff);
            print_vet(buffer, len_buff);
        }
    } while (!cmp(cmd, "END", 3, 3));

    return 0;
}