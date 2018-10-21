cmake_minimum_required(VERSION 3.10.2)
project(mc202 C)

set(CMAKE_C_STANDARD 90)

include_directories(miscellaneous)
add_executable(list miscellaneous/linked_list.c)
add_executable(tree miscellaneous/binary_search_check.c)

add_executable(lab01 lab01.c)
add_executable(lab02 lab02.c)
add_executable(lab03 lab03.c)
add_executable(lab05 lab05.c)
add_executable(lab07 lab07.c)

include_directories(lab04)
add_executable(
        lab04 lab04/lab04.c
        lab04/acao.h lab04/acao.c
        lab04/portfolio.h lab04/portfolio.c
)

include_directories(lab06)
add_executable(
        lab06 lab06/lab06.c
        lab06/universidade.h lab06/universidade.c
)

include_directories(lab08)
add_executable(
        lab08 lab08/lab08.c
        lab08/numero_astronomico.h lab08/numero_astronomico.c
)

include_directories(lab09)
add_executable(
        lab09 lab09/lab09.c
        lab09/fila.h lab09/fila.c
        lab09/jogador.h lab09/jogador.c
        lab09/pilha.h lab09/pilha.c
)

include_directories(lab10)
add_executable(
        lab10 lab10/lab10.c
        lab10/arvore.h lab10/arvore.c
)

include_directories(lab11)
add_executable(
        lab11 lab11/lab11.c
        lab11/treap.h lab11/treap.c
)