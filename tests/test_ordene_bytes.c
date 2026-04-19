#include <stdlib.h>
#include "test_runner.h"
#include "../functions/ordene_bytes_na_arvore.h"
#include "../huffman.h"
#include "../fila_prioridade.h"

void test_ordene_bytes_na_arvore() {
    SUITE("ordeneBytesNaArvore");

    {
        ByteFrequencia lista[] = {{'a', 2}, {'b', 1}, {'c', 5}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 3);

        ASSERT("fila criada com tamanho 3", fila->tamanho == 3);
        destruirFilaPrioridade(fila);
    }

    {
        ByteFrequencia lista[] = {{'a', 2}, {'b', 1}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 2);

        Nodo* minimo = removerMinimo(fila);
        ASSERT("primeiro removido tem a menor frequencia (1)", minimo->frequencia == 1);
        ASSERT("byte de menor frequencia e 'b'", minimo->byte == 'b');
        free(minimo);
        destruirFilaPrioridade(fila);
    }

    {
        ByteFrequencia lista[] = {{'x', 10}, {'y', 3}, {'z', 7}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 3);

        Nodo* n1 = removerMinimo(fila);
        Nodo* n2 = removerMinimo(fila);
        Nodo* n3 = removerMinimo(fila);
        ASSERT("1o removido tem frequencia 3", n1->frequencia == 3);
        ASSERT("2o removido tem frequencia 7", n2->frequencia == 7);
        ASSERT("3o removido tem frequencia 10", n3->frequencia == 10);
        free(n1); free(n2); free(n3);
        destruirFilaPrioridade(fila);
    }
}
