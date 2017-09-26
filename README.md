# Ordenacao_Merge

Implemente um programa paralelo para ordenação de elementos de um vetor -- distribuído em vários processos (ranks).

Passos:

Inicialmente, um dos processos (rank=0) criará um vetor V de P posições preenchido com números aleatórios (ex: inteiros entre 0 e 100) -- rank 0 imprime vetor gerado.
Em seguida, esse processo distribuirá o vetor em N processos (P = k.N, onde k=1,2,3,...) -- incluindo a si próprio.
A partir daí, os programas devem coordenar processamento local e global para permitir a ordenação global do vetor.
Quando ordenação do vetor estiver finalizada, rank 0 deve imprimir vetor ordenado.
Todos os processos devem finalizar.


Envie um arquivo compactado contendo os seguintes arquivos:

mpi_ordenacao.c
programa paralelo

saida_mpi_ordenacao.txt
resultado da execução do programa e quanto tempo o programa demorou.
