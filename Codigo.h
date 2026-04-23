#ifndef CODIGOS_H
#define CODIGOS_H
#include "arvore.h"
#define MAX_CODIGO 256

typedef struct {
    char codigo[MAX_CODIGO];
} Codigo;

void gerar_codigos(Nodo *raiz, Codigo tabela[256]);

#endif