#ifndef FREQUENCIA_H
#define FREQUENCIA_H

typedef struct {
    int byte;
    int frequencia;
} FreqByte;
 
int ContarFrequencia(const char *caminho, FreqByte saida[256]);

#endif