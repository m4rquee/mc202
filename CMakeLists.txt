cmake_minimum_required(VERSION 3.10.2)
project(mc202 C)

set(CMAKE_C_STANDARD 90)

add_executable(lab01 lab01.c)
add_executable(lab02 lab02.c)
add_executable(lab03 lab03.c)

include_directories(lab04)
add_executable(
        lab04 lab04/lab04.c
        lab04/acao.h lab04/acao.c
        lab04/portfolio.h lab04/portfolio.c
)