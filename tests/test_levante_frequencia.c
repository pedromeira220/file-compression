#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_runner.h"
#include "../functions/levante_frequencia_dos_bytes.h"

void test_levante_frequencia_dos_bytes() {
    SUITE("levanteFrequenciaDosBytes");

    {
        char conteudo[] = "aab";
        FILE* f = fmemopen(conteudo, strlen(conteudo), "rb");
        int tamanho;
        ByteFrequencia* lista = levanteFrequenciaDosBytes(f, &tamanho);
        fclose(f);

        ASSERT("'aab' retorna 2 bytes distintos", tamanho == 2);

        int freq_a = 0, freq_b = 0;
        for (int i = 0; i < tamanho; i++) {
            if (lista[i].byte == 'a') freq_a = lista[i].frequencia;
            if (lista[i].byte == 'b') freq_b = lista[i].frequencia;
        }
        ASSERT("'a' tem frequencia 2 em 'aab'", freq_a == 2);
        ASSERT("'b' tem frequencia 1 em 'aab'", freq_b == 1);
        free(lista);
    }

    {
        char conteudo[] = "zzz";
        FILE* f = fmemopen(conteudo, strlen(conteudo), "rb");
        int tamanho;
        ByteFrequencia* lista = levanteFrequenciaDosBytes(f, &tamanho);
        fclose(f);

        ASSERT("'zzz' retorna 1 byte distinto", tamanho == 1);
        ASSERT("'z' tem frequencia 3 em 'zzz'", lista[0].frequencia == 3);
        free(lista);
    }

    {
        char conteudo[] = "abcd";
        FILE* f = fmemopen(conteudo, strlen(conteudo), "rb");
        int tamanho;
        ByteFrequencia* lista = levanteFrequenciaDosBytes(f, &tamanho);
        fclose(f);

        ASSERT("'abcd' retorna 4 bytes distintos", tamanho == 4);

        int soma = 0;
        for (int i = 0; i < tamanho; i++) soma += lista[i].frequencia;
        ASSERT("soma das frequencias em 'abcd' e 4", soma == 4);
        free(lista);
    }
}
