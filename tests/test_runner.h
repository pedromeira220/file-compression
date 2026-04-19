#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <stdio.h>

extern int testes_passados;
extern int testes_falhos;

#define ASSERT(descricao, condicao) \
    do { \
        if (condicao) { \
            printf("  [OK]     %s\n", descricao); \
            testes_passados++; \
        } else { \
            printf("  [FALHOU] %s (linha %d)\n", descricao, __LINE__); \
            testes_falhos++; \
        } \
    } while(0)

#define SUITE(nome) printf("\n=== %s ===\n", nome)

#define RESUMO() \
    do { \
        printf("\n-------------------------------\n"); \
        printf("Passaram: %d  |  Falharam: %d\n", testes_passados, testes_falhos); \
        printf("-------------------------------\n"); \
    } while(0)

#endif
