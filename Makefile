SRC = main.c comprimir.c huffman.c fila_prioridade.c Codigo.c functions/levante_frequencia_dos_bytes.c functions/ordene_bytes_na_arvore.c functions/construa_arvore_de_huffman.c functions/mapeie_bytes_para_codigos.c

SRC_TEST = tests/main.c tests/test_levante_frequencia.c tests/test_ordene_bytes.c tests/test_construa_arvore.c tests/test_mapeie_bytes.c \
           huffman.c fila_prioridade.c Codigo.c \
           functions/levante_frequencia_dos_bytes.c \
           functions/ordene_bytes_na_arvore.c \
           functions/construa_arvore_de_huffman.c \
           functions/mapeie_bytes_para_codigos.c

run:
	gcc $(SRC) -o output && ./output arquivo.txt

test:
	gcc $(SRC_TEST) -o output_test && ./output_test
