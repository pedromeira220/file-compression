#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compactacao.h"

static const EntradaTabela *buscarCodigo(const TabelaCodigos *tabela, unsigned char byteVal) {
    for (int i = 0; i < tabela->tamanho; i++) {
        if (tabela->entradas[i].byteVal == byteVal)
            return &tabela->entradas[i];
    }
    return NULL;
}

static void escrever4bytes(FILE *f, unsigned int valor) {
    unsigned char buf[4];
    buf[0] = (valor >> 24) & 0xFF;
    buf[1] = (valor >> 16) & 0xFF;
    buf[2] = (valor >>  8) & 0xFF;
    buf[3] = (valor      ) & 0xFF;
    fwrite(buf, 1, 4, f);
}

float compactar(const char *caminhoEntrada, const TabelaCodigos *tabela, const char *caminhoSaida) {
    FILE *entrada = fopen(caminhoEntrada, "rb");
    if (!entrada) {
        fprintf(stderr, "Erro ao abrir arquivo de entrada: %s\n", caminhoEntrada);
        return -1.0f;
    }

    fseek(entrada, 0, SEEK_END);
    long tamanhoOriginal = ftell(entrada);
    rewind(entrada);

    if (tamanhoOriginal == 0) {
        fprintf(stderr, "O arquivo de entrada esta vazio.\n");
        fclose(entrada);
        return -1.0f;
    }

    unsigned char *dados = (unsigned char *)malloc(tamanhoOriginal);
    if (!dados) {
        fprintf(stderr, "Erro de alocacao de memoria.\n");
        fclose(entrada);
        return -1.0f;
    }
    fread(dados, 1, tamanhoOriginal, entrada);
    fclose(entrada);

    long capacidadeBits = tamanhoOriginal * MAX_BITS_CODIGO;
    char *bitsStr = (char *)malloc(capacidadeBits + 1);
    if (!bitsStr) {
        fprintf(stderr, "Erro de alocacao de memoria.\n");
        free(dados);
        return -1.0f;
    }
    bitsStr[0] = '\0';

    long pos = 0;
    for (long i = 0; i < tamanhoOriginal; i++) {
        const EntradaTabela *entradaTab = buscarCodigo(tabela, dados[i]);
        if (!entradaTab) {
            fprintf(stderr, "Byte %d nao encontrado na tabela de codigos.\n", dados[i]);
            free(dados);
            free(bitsStr);
            return -1.0f;
        }
        memcpy(bitsStr + pos, entradaTab->codigo, entradaTab->comprimento);
        pos += entradaTab->comprimento;
    }
    bitsStr[pos] = '\0';
    long totalBitsUteis = pos;

    free(dados);

    int padding = (8 - (int)(totalBitsUteis % 8)) % 8;
    for (int i = 0; i < padding; i++)
        bitsStr[totalBitsUteis + i] = '0';
    long totalBitsPadded = totalBitsUteis + padding;
    bitsStr[totalBitsPadded] = '\0';

    long numCorpoBytes = totalBitsPadded / 8;
    unsigned char *corpo = (unsigned char *)malloc(numCorpoBytes);
    if (!corpo) {
        fprintf(stderr, "Erro de alocacao de memoria.\n");
        free(bitsStr);
        return -1.0f;
    }

    for (long i = 0; i < numCorpoBytes; i++) {
        unsigned char byteMontado = 0;
        for (int b = 0; b < 8; b++) {
            if (bitsStr[i * 8 + b] == '1')
                byteMontado |= (1 << (7 - b));
        }
        corpo[i] = byteMontado;
    }

    free(bitsStr);

    char saidaPath[1024];
    if (caminhoSaida) {
        strncpy(saidaPath, caminhoSaida, sizeof(saidaPath) - 1);
        saidaPath[sizeof(saidaPath) - 1] = '\0';
    } else {
        snprintf(saidaPath, sizeof(saidaPath), "%s.huff", caminhoEntrada);
    }

    FILE *saida = fopen(saidaPath, "wb");
    if (!saida) {
        fprintf(stderr, "Erro ao criar arquivo de saida: %s\n", saidaPath);
        free(corpo);
        return -1.0f;
    }

    escrever4bytes(saida, (unsigned int)tabela->tamanho);

    for (int i = 0; i < tabela->tamanho; i++) {
        const EntradaTabela *e = &tabela->entradas[i];
        int comprimento = e->comprimento;
        int padCod = (8 - comprimento % 8) % 8;
        int bitsPadded = comprimento + padCod;
        int numBytesCod = bitsPadded / 8;

        unsigned char *codBytes = (unsigned char *)calloc(numBytesCod, 1);
        for (int b = 0; b < comprimento; b++) {
            if (e->codigo[b] == '1')
                codBytes[b / 8] |= (1 << (7 - (b % 8)));
        }

        fwrite(&e->byteVal, 1, 1, saida);
        unsigned char compByte = (unsigned char)comprimento;
        fwrite(&compByte, 1, 1, saida);
        fwrite(codBytes, 1, numBytesCod, saida);
        free(codBytes);
    }

    escrever4bytes(saida, (unsigned int)totalBitsUteis);
    fwrite(corpo, 1, numCorpoBytes, saida);
    fclose(saida);
    free(corpo);

    long tamanhoCompactado = 0;
    FILE *tmp = fopen(saidaPath, "rb");
    if (tmp) {
        fseek(tmp, 0, SEEK_END);
        tamanhoCompactado = ftell(tmp);
        fclose(tmp);
    }

    float taxa = (1.0f - (float)tamanhoCompactado / (float)tamanhoOriginal) * 100.0f;

    printf("Arquivo original:    %s  (%ld bytes)\n", caminhoEntrada, tamanhoOriginal);
    printf("Arquivo compactado: %s  (%ld bytes)\n", saidaPath, tamanhoCompactado);
    printf("Taxa de compactacao: %.2f%%\n", taxa);

    return taxa;
}