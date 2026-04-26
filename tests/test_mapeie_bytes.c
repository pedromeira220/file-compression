#include <stdlib.h>
#include <string.h>
#include "test_runner.h"
#include "../functions/mapeie_bytes_para_codigos.h"
#include "../functions/construa_arvore_de_huffman.h"
#include "../functions/ordene_bytes_na_arvore.h"
#include "../huffman.h"
#include "../codigo.h"

static void liberarNodo(Nodo* n) {
    if (n == NULL) return;
    liberarNodo(n->filhoEsquerdo);
    liberarNodo(n->filhoDireito);
    free(n);
}

static void liberarTabela(Codigo* tabela) {
    if (tabela == NULL) return;
    for (int i = 0; i < 256; i++) {
        if (tabela[i].byte != NULL)
            free_codigo(&tabela[i]);
    }
    free(tabela);
}

void test_mapeie_bytes_para_codigos() {
    SUITE("mapeieByteParaCodigos");

    {
        ByteFrequencia lista[] = {{'b', 1}, {'a', 2}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 2);
        ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);
        Codigo* tabela = mapeieByteParaCodigos(arvore);

        ASSERT("tabela criada nao e nula", tabela != NULL);
        ASSERT("codigo de 'b' tem 1 bit", tabela['b'].tamanho == 1);
        ASSERT("codigo de 'a' tem 1 bit", tabela['a'].tamanho == 1);

        char* cb = toString(tabela['b']);
        char* ca = toString(tabela['a']);
        ASSERT("codigo de 'b' e '0'", strcmp(cb, "0") == 0);
        ASSERT("codigo de 'a' e '1'", strcmp(ca, "1") == 0);
        free(cb); free(ca);

        liberarTabela(tabela);
        liberarNodo(arvore->raiz);
        free(arvore);
        destruirFilaPrioridade(fila);
    }

    {
        ByteFrequencia lista[] = {{'a', 2}, {'b', 1}, {'c', 3}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 3);
        ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);
        Codigo* tabela = mapeieByteParaCodigos(arvore);

        ASSERT("'c' (maior freq) tem 1 bit", tabela['c'].tamanho == 1);
        ASSERT("'b' (menor freq) tem 2 bits", tabela['b'].tamanho == 2);
        ASSERT("'a' tem 2 bits", tabela['a'].tamanho == 2);

        char* cc = toString(tabela['c']);
        char* cb = toString(tabela['b']);
        char* ca = toString(tabela['a']);
        ASSERT("codigo de 'c' e '0'", strcmp(cc, "0") == 0);
        ASSERT("codigo de 'b' e '10'", strcmp(cb, "10") == 0);
        ASSERT("codigo de 'a' e '11'", strcmp(ca, "11") == 0);
        free(cc); free(cb); free(ca);

        liberarTabela(tabela);
        liberarNodo(arvore->raiz);
        free(arvore);
        destruirFilaPrioridade(fila);
    }

    {
        ByteFrequencia lista[] = {{'a', 5}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 1);
        ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);
        Codigo* tabela = mapeieByteParaCodigos(arvore);

        ASSERT("byte unico: codigo de 'a' tem 0 bits", tabela['a'].tamanho == 0);
        ASSERT("byte ausente na arvore tem tamanho 0", tabela['b'].tamanho == 0);

        liberarTabela(tabela);
        liberarNodo(arvore->raiz);
        free(arvore);
        destruirFilaPrioridade(fila);
    }

    {
        ByteFrequencia lista[] = {{'x', 5}, {'y', 3}, {'z', 1}, {'w', 4}};
        FilaPrioridade* fila = ordeneBytesNaArvore(lista, 4);
        ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);
        Codigo* tabela = mapeieByteParaCodigos(arvore);

        ASSERT("'x' (maior freq) tem 1 bit", tabela['x'].tamanho == 1);
        ASSERT("'w' tem 2 bits", tabela['w'].tamanho == 2);
        ASSERT("'z' (menor freq) tem 3 bits", tabela['z'].tamanho == 3);
        ASSERT("'y' tem 3 bits", tabela['y'].tamanho == 3);

        char* cx = toString(tabela['x']);
        char* cw = toString(tabela['w']);
        char* cz = toString(tabela['z']);
        char* cy = toString(tabela['y']);
        ASSERT("codigo de 'x' e '0'", strcmp(cx, "0") == 0);
        ASSERT("codigo de 'w' e '10'", strcmp(cw, "10") == 0);
        ASSERT("codigo de 'z' e '110'", strcmp(cz, "110") == 0);
        ASSERT("codigo de 'y' e '111'", strcmp(cy, "111") == 0);
        free(cx); free(cw); free(cz); free(cy);

        liberarTabela(tabela);
        liberarNodo(arvore->raiz);
        free(arvore);
        destruirFilaPrioridade(fila);
    }
}
