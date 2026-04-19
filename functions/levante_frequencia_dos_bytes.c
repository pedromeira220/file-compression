#include <stdio.h>
#include <stdlib.h>
#include "../huffman.h"

ByteFrequencia* levanteFrequenciaDosBytes(FILE* arquivo, int* tamanho) {
    unsigned int frequencias[256] = {0};
    unsigned char byte;

    rewind(arquivo);
    while (fread(&byte, 1, 1, arquivo) == 1) {
        frequencias[byte]++;
    }

    int total = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) total++;
    }

    ByteFrequencia* lista = malloc(total * sizeof(ByteFrequencia));
    int index = 0;
    for (int i = 0; i < 256; i++) {
        if (frequencias[i] > 0) {
            lista[index].byte = (unsigned char) i;
            lista[index].frequencia = frequencias[i];
            index++;    
        }
    }

    *tamanho = total;
    return lista;
}
