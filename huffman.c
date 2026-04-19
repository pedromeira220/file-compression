#include "huffman.h"

Nodo* criarNodo(unsigned char byte, unsigned int frequency) {
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    if (nodo == NULL) return NULL;

    nodo->byte = byte;
    nodo->frequencia = frequency;
    nodo->filhoEsquerdo = NULL;
    nodo->filhoDireito = NULL;

    return nodo;
}