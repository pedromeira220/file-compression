#include <stdio.h>
#include "frequencia.h"

int ContarFrequencia(const char *caminho, FreqByte saida[256]) {

    FILE *arquivo = fopen(caminho, "rb");

    if (!arquivo) {

        return -1;
    }

    int contagem[256] = {0};

    int c;
    while ((c = fgetc(arquivo)) != EOF) {
        contagem[c]++;
    }

    fclose(arquivo);

    int total = 0;
    for (int i = 0; i < 256; i++) {
        if (contagem[i] > 0) {
            saida[total].byte = i;
            saida[total].frequencia = contagem[i];
            total++;
        }
    }
    return total;
}