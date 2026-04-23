#ifndef COMPACTACAO_H
#define COMPACTACAO_H

#define MAX_SIMBOLOS 256
#define MAX_BITS_CODIGO 256

typedef struct {
    unsigned char byteVal;
    char codigo[MAX_BITS_CODIGO];
    int comprimento;
} EntradaTabela;

typedef struct {
    EntradaTabela entradas[MAX_SIMBOLOS];
    int tamanho;
} TabelaCodigos;

float compactar(const char *caminhoEntrada, const TabelaCodigos *tabela, const char *caminhoSaida);

#endif