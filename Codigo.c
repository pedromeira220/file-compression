#include <string.h>
#include "codigos.h"
#include "arvore.h"

static void percorrer(Nodo *nodo, char *prefixo, int profundidade,
                      Codigo tabela[256]) {

    if (!nodo) return;
    if (!nodo->esquerda && !nodo->direita) {

        if (profundidade == 0) {
            tabela[nodo->byte].codigo[0] = '0';
            tabela[nodo->byte].codigo[1] = '\0';
        } else {
            prefixo[profundidade] = '\0';
            strcpy(tabela[nodo->byte].codigo, prefixo);
        }
        return;
    }

    prefixo[profundidade] = '0';
    percorrer(nodo->esquerda, prefixo, profundidade + 1, tabela);
    
    prefixo[profundidade] = '1';
    percorrer(nodo->direita, prefixo, profundidade + 1, tabela);
}

void gerarCodigos(Nodo *raiz, Codigo tabela[256]) {
    memset(tabela, 0, sizeof(Codigo) * 256);

    char prefixo[MAX_CODIGO];
    percorrer(raiz, prefixo, 0, tabela);
}