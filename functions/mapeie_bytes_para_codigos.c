#include <stdlib.h>
#include "../huffman.h"
#include "../codigo.h"
#include "mapeie_bytes_para_codigos.h"

static void percorrerArvore(Nodo* nodo, Codigo* tabela, Codigo* codigoAtual) {
    if (nodo == NULL) return;

    if (nodo->filhoEsquerdo == NULL && nodo->filhoDireito == NULL) {
        clone(*codigoAtual, &tabela[nodo->byte]);
        return;
    }

    adiciona_bit(codigoAtual, 0);
    percorrerArvore(nodo->filhoEsquerdo, tabela, codigoAtual);
    joga_fora_bit(codigoAtual);

    adiciona_bit(codigoAtual, 1);
    percorrerArvore(nodo->filhoDireito, tabela, codigoAtual);
    joga_fora_bit(codigoAtual);
}

Codigo* mapeieByteParaCodigos(ArvoreHuffman* arvore) {
    Codigo* tabela = malloc(256 * sizeof(Codigo));
    if (tabela == NULL) return NULL;

    for (int i = 0; i < 256; i++) {
        tabela[i].byte = NULL;
        tabela[i].capacidade = 0;
        tabela[i].tamanho = 0;
    }

    Codigo codigoAtual;
    if (!novo_codigo(&codigoAtual)) {
        free(tabela);
        return NULL;
    }

    percorrerArvore(arvore->raiz, tabela, &codigoAtual);
    free_codigo(&codigoAtual);

    return tabela;
}
