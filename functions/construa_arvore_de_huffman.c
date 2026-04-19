#include <stdlib.h>
#include "../huffman.h"
#include "../fila_prioridade.h"

ArvoreHuffman* construaArvoreDeHuffman(FilaPrioridade* fila) {
    int quantidadeDeNodos = fila->tamanho;

    while (fila->tamanho >= 2) {
        Nodo* esquerdo = removerMinimo(fila);
        Nodo* direito = removerMinimo(fila);

        Nodo* novo = criarNodo(0, esquerdo->frequencia + direito->frequencia);
        novo->filhoEsquerdo = esquerdo;
        novo->filhoDireito = direito;

        inserirFilaPrioridade(fila, novo);
    }

    ArvoreHuffman* arvore = malloc(sizeof(ArvoreHuffman));
    arvore->raiz = removerMinimo(fila);
    arvore->quantidadeDeNodos = quantidadeDeNodos;

    return arvore;
}
