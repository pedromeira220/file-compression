#ifndef DESCOMPRIMIR_H
#define DESCOMPRIMIR_H

#include "huffman.h"
#include "meus_tipos.h"

int descomprimir(const char *caminhoEntrada, ArvoreHuffman *arvore, const char *caminhoSaida);

#endif