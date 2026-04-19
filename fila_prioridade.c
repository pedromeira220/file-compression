#include <stdlib.h>
#include "fila_prioridade.h"

FilaPrioridade* criarFilaPrioridade(int capacidade) {
    FilaPrioridade* fila = (FilaPrioridade*) malloc(sizeof(FilaPrioridade));
    if (fila == NULL) return NULL;

    fila->nodos = (Nodo**) malloc(sizeof(Nodo*) * capacidade);
    if (fila->nodos == NULL) {
        free(fila);
        return NULL;
    }

    fila->tamanho = 0;
    fila->capacidade = capacidade;
    return fila;
}

void inserirFilaPrioridade(FilaPrioridade* fila, Nodo* nodo) {
    // 1 / 4
    if (fila->tamanho >= fila->capacidade) return;

    // 0
    int i = fila->tamanho - 1;
    while (i >= 0 && fila->nodos[i]->frequencia > nodo->frequencia) {
        fila->nodos[i + 1] = fila->nodos[i];
        i--;
    }
    fila->nodos[i + 1] = nodo;
    fila->tamanho++;
}

Nodo* removerMinimo(FilaPrioridade* fila) {
    if (filaVazia(fila)) return NULL;

    Nodo* minimo = fila->nodos[0];

    for (int i = 0; i < fila->tamanho - 1; i++)
        fila->nodos[i] = fila->nodos[i + 1];

    fila->tamanho--;
    return minimo;
}

int filaVazia(FilaPrioridade* fila) {
    return fila->tamanho == 0;
}

void destruirFilaPrioridade(FilaPrioridade* fila) {
    free(fila->nodos);
    free(fila);
}