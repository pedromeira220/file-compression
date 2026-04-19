#include "../fila_prioridade.h"
#include "../huffman.h"

FilaPrioridade* ordeneBytesNaArvore(ByteFrequencia* lista, int tamanho) {
    FilaPrioridade* fila = criarFilaPrioridade(tamanho);

    for (int i = 0; i < tamanho; i++) {
        Nodo* nodo = criarNodo(lista[i].byte, lista[i].frequencia);
        inserirFilaPrioridade(fila, nodo);
    }

    return fila;
}
