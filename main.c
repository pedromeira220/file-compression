#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comprimir.h"
#include "descomprimir.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso:\n");
        printf("  %s c <arquivo>        - comprimir\n", argv[0]);
        printf("  %s d <arquivo.huff>   - descomprimir\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "c") == 0) {
        float taxa = comprimir(argv[2], NULL);
        if (taxa == -1.0f) return 1;
    } else if (strcmp(argv[1], "d") == 0) {
        if (descomprimir(argv[2], NULL) != 0) return 1;
    } else {
        fprintf(stderr, "Modo invalido: use 'c' para comprimir ou 'd' para descomprimir.\n");
        return 1;
    }

    return 0;
}
