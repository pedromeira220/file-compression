#include <stdio.h>
#include "test_runner.h"

int testes_passados = 0;
int testes_falhos = 0;

void test_levante_frequencia_dos_bytes();
void test_ordene_bytes_na_arvore();
void test_construa_arvore_de_huffman();

int main() {
    printf("Rodando testes...\n");

    test_levante_frequencia_dos_bytes();
    test_ordene_bytes_na_arvore();
    test_construa_arvore_de_huffman();

    RESUMO();
    return testes_falhos > 0 ? 1 : 0;
}
