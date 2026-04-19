#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "huffman.h"

typedef struct {
    Nodo** nodos;
    int tamanho;
    int capacidade;
} FilaPrioridade;

FilaPrioridade* criarFilaPrioridade(int capacidade);
void inserirFilaPrioridade(FilaPrioridade* fila, Nodo* nodo);
Nodo* removerMinimo(FilaPrioridade* fila);
int filaVazia(FilaPrioridade* fila);
void destruirFilaPrioridade(FilaPrioridade* fila);

#endif
