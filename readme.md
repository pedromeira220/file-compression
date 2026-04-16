# Trabalho - Compressão de arquivos

## Processo do Algorítimo

1. Processo de Compactação
   1. Levantamento da frequência dos caracteres
   2. Ordenação e priorização dos caracteres com base na ocorrência do texto
   3. Construção da Árvore de Huffman baseado na lista priorizada
   4. Iteração pela Árvore de Huffman para determinar os novos códigos
   5. Compactação do arquivo usando os novos códigos
2. Processo de Descompactação

## Nota de exemplo
Para a explicação dos processos a seguir considere o seguite exemplo de arquivo/texto a ser compactado.
> Eerie eyes seen near lake.

## Conceito - Arquivos

Um arquivo é uma sequência de posições, onde cada posição tem **8 bits**, e esses 8 bits representam um número de **0 a 255**.

```
[ 01000101 ] [ 01100101 ] [ 01110010 ] ...
     69            101          114
     'E'           'e'          'r'
```

O computador guarda bits (números binários de 8 dígitos), mas pode interpretar de várias formas (hexadecimal, binário, decimal e texto, convertido com a tabela ASCI) como mostrado acima.

### Por quê 0 a 255?

Com 8 bits você consegue representar 2⁸ = **256 combinações possíveis**:

```
00000000 = 0
00000001 = 1
00000010 = 2
...
11111110 = 254
11111111 = 255
```

## Conceito - Fila de prioridade
- Fila tradicional - FIFO - First In First Out 
- Fila de prioridade
  - Todo elemento inserido tem uma prioridade
  - Não necessariamente vai entrar no fim da fila, ele pode entrar no meio
  - Uma vez que o elemento esta na fila, a retirada é normal
- O que muda da fila de prioridade para normal é a **entrada**
## 1. Levantamento da frequência dos caracteres
1. Identifique os caracteres presentes no arquivo
2. Identifique a frequência de cada um dos caracteres
**Notas**
- No final, faça um print da fila
## 2. Ordenação e priorização dos caracteres com base na ocorrência do texto
1. Crie nodos de árvore binária para cada caracter contendo char/freq
2. Coloque os nos em uma fila de prioridade. Quanto menor a frequência, maior será a prioridade na fila 
**Notas**
- Os nodos entram na fila sempre exatamente um antes de um nodo com frequencia menor ou igual a ele
## 3. Construção da Árvore de Huffman baseado na lista priorizada
1. Enquanto a fila contiver dois ou mais nodos
   1. Crie um novo nodo 
   2. Desenfileire um nodo e o torne subárvore esquerda
   3. Desenfileire um nodo e o torne subárvore direita
   4. Torne a frequência do novo nodo igual à soma das frequências dos filhos esquerdo e direito
   5. Enfileire o novo nodo
2. Ao final do ciclo, desenfileire o nodo e terá a Árvore de Huffman
**Notas**
- O novo nodo não terá o caracter preenchido, mas somente a frequência (que é a soma da frequência das subárvores filhas)
- No minuto 28:58 há a explicação passo a passo do algorítimo
- É possível perceber que com o decorrer do processo, os caracteres com frequência mais baixa estão ficando longe da raiz
- A frequência contida no nodo raiz deve ser igual à quantidade total de caracteres no texto
## 4. Iteração pela Árvore de Huffman para determinar os novos códigos
1. Percorra a árvore para obter os novos códigos
2. Acrescente 0 ao código, toda vez que for para a esquerda, ou 1, toda vez que for para a direita. Acrescentar nesse caso não é uma soma, mas sim contatenação.
3. Um código está pronto quando uma folha for atingida
## 5. Compactação do arquivo usando os novos códigos
1. Reprocesse o arquivo e gere o arquivo compactado, usando os novos códigos
   1. Para cada character no arquivo original, concatene no arquivo de saída o código correspondente
**Notas**
- Não colocar espaços entre os arquivos
## Requisitos
- O sistema deve aceitar qualquer tipo de arquivos (não só texto)
- SHOULD HAVE - Calcular a taxa de compactação do arquivo em bits