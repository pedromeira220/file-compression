#include <stdlib.h>
#include "comprimir.h"
#include "functions/levante_frequencia_dos_bytes.h"
#include "functions/ordene_bytes_na_arvore.h"
#include "functions/construa_arvore_de_huffman.h"

ArvoreHuffman* comprimir(FILE* arquivo) {
    int tamanho;
    ByteFrequencia* frequencias = levanteFrequenciaDosBytes(arquivo, &tamanho);
    FilaPrioridade* fila = ordeneBytesNaArvore(frequencias, tamanho);
    free(frequencias);
    ArvoreHuffman* arvore = construaArvoreDeHuffman(fila);
    destruirFilaPrioridade(fila);
    return arvore;
}
