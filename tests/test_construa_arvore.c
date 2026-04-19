#include <stdlib.h>
#include "test_runner.h"
#include "../functions/construa_arvore_de_huffman.h"
#include "../functions/ordene_bytes_na_arvore.h"
#include "../huffman.h"
#include "../fila_prioridade.h"

static void liberarNodo(Nodo* n) {
    if (n == NULL) return;
    liberarNodo(n->filhoEsquerdo);
    liberarNodo(n->filhoDireito);
    free(n);
}

void test_construa_arvore_de_huffman() {
    SUITE("construaArvoreDeHuffman");

    {
        ByteFrequencia lista[] = {{'a', 2}, {'b', 1}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 2);
        ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);

        ASSERT("arvore criada nao e nula", arvore != NULL);
        ASSERT("raiz da arvore nao e nula", arvore->raiz != NULL);
        liberarNodo(arvore->raiz);
        free(arvore);
        destruirFilaPrioridade(fila);
    }

    {
        ByteFrequencia lista[] = {{'a', 2}, {'b', 1}, {'c', 3}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 3);
        ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);

        ASSERT("frequencia da raiz e a soma de todos (6)", arvore->raiz->frequencia == 6);
        ASSERT("quantidadeDeNodos e 3", arvore->quantidadeDeNodos == 3);
        liberarNodo(arvore->raiz);
        free(arvore);
        destruirFilaPrioridade(fila);
    }

    {
        ByteFrequencia lista[] = {{'x', 5}, {'y', 3}, {'z', 1}, {'w', 4}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 4);
        ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);

        ASSERT("frequencia da raiz e a soma de todos (13)", arvore->raiz->frequencia == 13);
        ASSERT("quantidadeDeNodos e 4", arvore->quantidadeDeNodos == 4);
        liberarNodo(arvore->raiz);
        free(arvore);
        destruirFilaPrioridade(fila);
    }

    {
        ByteFrequencia lista[] = {{'a', 5}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 1);
        ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);

        ASSERT("1 byte: raiz sem filhos", arvore->raiz->filhoEsquerdo == NULL && arvore->raiz->filhoDireito == NULL);
        ASSERT("1 byte: frequencia da raiz e 5", arvore->raiz->frequencia == 5);
        liberarNodo(arvore->raiz);
        free(arvore);
        destruirFilaPrioridade(fila);
    }
}
