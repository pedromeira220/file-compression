#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comprimir.h"
#include "compactacao.h"
#include "codigo.h"
#include "fila_prioridade.h"
#include "functions/levante_frequencia_dos_bytes.h"
#include "functions/ordene_bytes_na_arvore.h"
#include "functions/construa_arvore_de_huffman.h"
#include "functions/mapeie_bytes_para_codigos.h"

static TabelaCodigos codigosParaTabelaCodigos(Codigo *tabela) {
    TabelaCodigos tabelaCodigos;
    tabelaCodigos.tamanho = 0;

    for (int i = 0; i < 256; i++) {
        if (tabela[i].tamanho == 0) continue;

        EntradaTabela *e = &tabelaCodigos.entradas[tabelaCodigos.tamanho];
        e->byteVal = (unsigned char)i;
        e->comprimento = (int)tabela[i].tamanho;

        char *str = toString(tabela[i]);
        strncpy(e->codigo, str, MAX_BITS_CODIGO - 1);
        e->codigo[MAX_BITS_CODIGO - 1] = '\0';
        free(str);

        tabelaCodigos.tamanho++;
    }

    return tabelaCodigos;
}

float comprimir(const char *caminhoEntrada, const char *caminhoSaida) {
    FILE *arquivo = fopen(caminhoEntrada, "rb");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo: %s\n", caminhoEntrada);
        return -1.0f;
    }

    /* Processo 1.1 - Levantamento da frequência dos bytes */
    int tamanho;
    ByteFrequencia *frequencias = levanteFrequenciaDosBytes(arquivo, &tamanho);
    fclose(arquivo);

    /* Processo 1.2 - Ordenação e priorização dos bytes */
    FilaPrioridade *fila = ordeneBytesNaArvore(frequencias, tamanho);
    free(frequencias);

    /* Processo 1.3 - Construção da Árvore de Huffman */
    ArvoreHuffman *arvore = construaArvoreDeHuffman(fila);
    destruirFilaPrioridade(fila);

    /* Processo 1.4 - Mapeamento dos bytes para códigos */
    Codigo *tabela = mapeieByteParaCodigos(arvore);

    /* Processo 1.5 - Compactação do arquivo */
    TabelaCodigos tabelaCodigos = codigosParaTabelaCodigos(tabela);

    for (int i = 0; i < 256; i++) {
        if (tabela[i].byte != NULL) free_codigo(&tabela[i]);
    }
    free(tabela);
    free(arvore);

    return compactar(caminhoEntrada, &tabelaCodigos, caminhoSaida);
}
