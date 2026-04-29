#include <stdio.h>
#include "comprimir.h"
#include "descomprimir.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso:\n  %s c <arquivo>\n  %s d <arquivo.huff>\n", argv[0], argv[0]);
        return 1;
    }

    if (argv[1][0] == 'c') {
        if (comprimir(argv[2], NULL) == -1.0f) return 1;
    } else if (argv[1][0] == 'd') {
        if (descomprimir(argv[2], NULL) != 0) return 1;
    } else {
        printf("Modo invalido: use 'c' ou 'd'.\n");
        return 1;
    }

    return 0;
}
