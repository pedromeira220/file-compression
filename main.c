# include <stdio.h>

// TODO: O main.c só deve chamar as funções

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        printf("Por favor, especifique um arquivo no formato acima.\n");
        return 1;
    }

    FILE* f = fopen(argv[1], "rb");
    if (f == NULL) {
        printf("Erro: arquivo '%s' não encontrado\n", argv[1]);
        return 1;
    }

    unsigned char byte;
    while (fread(&byte, 1, 1, f) == 1) {
        printf("%c", byte);
    }

    printf("\n");

    fclose(f);
    return 0;
}