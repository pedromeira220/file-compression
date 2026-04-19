#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include "meus_tipos.h"

typedef struct Nodo {
    unsigned char byte;      
    unsigned int frequencia;
    struct Nodo* filhoEsquerdo;
    struct Nodo* filhoDireito;
} Nodo;

typedef struct {
    Nodo* raiz;
    int quantidadeDeNodos;
} ArvoreHuffman;

typedef struct {
    unsigned char byte;
    unsigned int frequencia;
} ByteFrequencia;

Nodo* criarNodo(unsigned char byte, unsigned int frequency);

#endif
