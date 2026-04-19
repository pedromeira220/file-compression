SRC = main.c comprimir.c huffman.c fila_prioridade.c functions/levante_frequencia_dos_bytes.c functions/ordene_bytes_na_arvore.c functions/construa_arvore_de_huffman.c

run:
	gcc $(SRC) -o output && ./output arquivo.txt
