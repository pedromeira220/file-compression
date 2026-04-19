#include <stdlib.h>
#include "comprimir.h"
#include "functions/levante_frequencia_dos_bytes.h"
#include "functions/ordene_bytes_na_arvore.h"

FilaPrioridade* comprimir(FILE* arquivo) {
    int tamanho;
    ByteFrequencia* frequencias = levanteFrequenciaDosBytes(arquivo, &tamanho);
    FilaPrioridade* fila = ordeneBytesNaArvore(frequencias, tamanho);
    free(frequencias);
    return fila;
}
