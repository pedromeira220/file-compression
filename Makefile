SRC = main.c comprimir.c huffman.c fila_prioridade.c functions/levante_frequencia_dos_bytes.c functions/ordene_bytes_na_arvore.c functions/construa_arvore_de_huffman.c

SRC_TEST = tests/main.c tests/test_levante_frequencia.c tests/test_ordene_bytes.c tests/test_construa_arvore.c \
           huffman.c fila_prioridade.c \
           functions/levante_frequencia_dos_bytes.c \
           functions/ordene_bytes_na_arvore.c \
           functions/construa_arvore_de_huffman.c

run:
	gcc $(SRC) -o output && ./output arquivo.txt

test:
	gcc $(SRC_TEST) -o output_test && ./output_test
