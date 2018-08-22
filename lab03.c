#include <stdio.h>

#define BUFF_SIZE 100

void cat(char buffer[], char arg[], int *len_buff, int len_arg) {
    int i;
    for (i = 0; i < len_arg; i++)
        buffer[*len_buff + i] = arg[i];

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
    for (i = x; i < tam + x; i++)
        printf("%c", buff[i]);

    printf("\n");
}

void print_vet(char buff[], int tam) {
    int i;
    for (i = 0; i < tam; i++)
        printf("%c", buff[i]);

    printf("\n");
}

int str_len(char buff[]) {
    int len;
    for (len = 0; buff[len] != '\0'; len++);
    return len;
}

int main() {
    char cmd[3 + 1];
    int len_buff = 0;
    char buffer[BUFF_SIZE], arg[BUFF_SIZE + 1];

    do {
        scanf("%s", cmd);

        if (cmp(cmd, "CAT", 3, 3)) {
            scanf("%s", arg);
            cat(buffer, arg, &len_buff, str_len(arg));
            print_vet(buffer, len_buff);
        } else if (cmp(cmd, "CMP", 3, 3)) {
            scanf("%s", arg);
            printf("%s\n", cmp(buffer, arg, len_buff, str_len(arg)) ? "IGUAL" : "DIFERENTE");
        } else if (cmp(cmd, "SUB", 3, 3)) {
            int x, tam;
            scanf("%d %d", &x, &tam);
            sub(buffer, x, tam, &len_buff);
            print_vet(buffer, len_buff);
        }
    } while (!cmp(cmd, "END", 3, 3));

    return 0;
}