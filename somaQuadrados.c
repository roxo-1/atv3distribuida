/*
Ana Julia Yaguti Matilha
Carolina Lee
Pedro Casas Pequeno Junior
*/

#include <stdio.h>
/*
Implemente um programa MPI que siga os seguintes passos:
1. O processo root (rank 0) deve criar um vetor contendo os inteiros de 1 a N, onde N = 40.
2. Esse vetor deverá ser dividido igualmente entre todos os processos com MPI_Scatter.
    Exemplo: se N = 40 e há 4 processos, cada um receberá 10 elementos.
3. Cada processo deve calcular a soma dos quadrados dos elementos recebidos.
    Exemplo: se recebeu [3, 4, 5], calcular 3² + 4² + 5² = 50.
4. Com MPI_Reduce, envie todas as somas locais para o processo root, que deve calcular a soma total dos quadrados.
5. O processo root também deve calcular a soma sequencial dos quadrados (1² + 2² + ... + 40²) e comparar com o resultado paralelo.
6.Exibir na tela:
    O vetor local de cada processo (para verificação)
    O resultado da soma paralela
    O resultado da soma sequencial
    Se os valores coincidem ou não
*/


int main(){
    return 0;
}