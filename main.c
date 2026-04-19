#include <stdio.h>
#include <stdlib.h>
#include "comprimir.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    FILE* arquivo = fopen(argv[1], "rb");
    if (arquivo == NULL) {
        printf("Erro: arquivo '%s' não encontrado\n", argv[1]);
        return 1;
    }

    FilaPrioridade* fila = comprimir(arquivo);

    fclose(arquivo);
    destruirFilaPrioridade(fila);
    return 0;
}
