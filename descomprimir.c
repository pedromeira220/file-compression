#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descomprimir.h"

static U32 ler4bytes(FILE *f) {
    unsigned char buf[4];
    fread(buf, 1, 4, f);
    return ((U32)buf[0] << 24)
         | ((U32)buf[1] << 16)
         | ((U32)buf[2] <<  8)
         |  (U32)buf[3];
}

static void gerarCaminhoSaida(const char *entrada, char *saida, int maxLen) {
    strncpy(saida, entrada, maxLen - 1);
    saida[maxLen - 1] = '\0';
    int len = (int)strlen(saida);
    if (len > 5 && strcmp(saida + len - 5, ".huff") == 0)
        saida[len - 5] = '\0';
    else
        strncat(saida, "_descomprimido", maxLen - len - 1);
}

int descomprimir(const char *caminhoEntrada, ArvoreHuffman *arvore, const char *caminhoSaida) {
    if (!arvore || !arvore->raiz) {
        fprintf(stderr, "Arvore de Huffman invalida.\n");
        return -1;
    }

    FILE *entrada = fopen(caminhoEntrada, "rb");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir: %s\n", caminhoEntrada);
        return -1;
    }

    U32 numEntradas = ler4bytes(entrada);
    if (numEntradas == 0 || numEntradas > 256) {
        fprintf(stderr, "Cabecalho invalido.\n");
        fclose(entrada);
        return -1;
    }

    for (U32 i = 0; i < numEntradas; i++) {
        unsigned char compByte;
        fseek(entrada, 1, SEEK_CUR);
        fread(&compByte, 1, 1, entrada);
        int numBytesCod = ((int)compByte + 7) / 8;
        fseek(entrada, numBytesCod, SEEK_CUR);
    }

    U32 totalBitsUteis = ler4bytes(entrada);

    long posCorpo = ftell(entrada);
    fseek(entrada, 0, SEEK_END);
    long tamanhoCorpo = ftell(entrada) - posCorpo;
    fseek(entrada, posCorpo, SEEK_SET);

    unsigned char *corpo = (unsigned char *)malloc(tamanhoCorpo);
    if (!corpo) {
        fprintf(stderr, "Erro de alocacao de memoria.\n");
        fclose(entrada);
        return -1;
    }
    fread(corpo, 1, tamanhoCorpo, entrada);
    fclose(entrada);

    char saidaPath[1024];
    if (caminhoSaida) {
        strncpy(saidaPath, caminhoSaida, sizeof(saidaPath) - 1);
        saidaPath[sizeof(saidaPath) - 1] = '\0';
    } else {
        gerarCaminhoSaida(caminhoEntrada, saidaPath, sizeof(saidaPath));
    }

    FILE *saida = fopen(saidaPath, "wb");
    if (!saida) {
        fprintf(stderr, "Erro ao criar: %s\n", saidaPath);
        free(corpo);
        return -1;
    }

    Nodo *atual = arvore->raiz;
    U32 bitsProcessados = 0;

    for (long byteIdx = 0; byteIdx < tamanhoCorpo && bitsProcessados < totalBitsUteis; byteIdx++) {
        unsigned char byteLido = corpo[byteIdx];

        for (int bit = 7; bit >= 0 && bitsProcessados < totalBitsUteis; bit--) {
            int valorBit = (byteLido >> bit) & 1;

            atual = (valorBit == 0) ? atual->filhoEsquerdo : atual->filhoDireito;

            if (!atual->filhoEsquerdo && !atual->filhoDireito) {
                fwrite(&atual->byte, 1, 1, saida);
                atual = arvore->raiz;
            }

            bitsProcessados++;
        }
    }

    fclose(saida);
    free(corpo);

    printf("Arquivo descomprimido: %s\n", saidaPath);
    return 0;
}