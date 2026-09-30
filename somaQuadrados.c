/*
Ana Julia Yaguti Matilha
Carolina Lee
Pedro Casas Pequeno Junior
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
/*
mpicc -o somaQuadrados somaQuadrados.c
mpirun --oversubscribe -np 4 ./somaQuadrados
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


int main(int argc, char *argv[]) {
    int i;
    int N = 40;
    int rank, processadores_num;
    int *data = NULL;              // Ponteiro para o vetor completo (só usado pelo root)
    int *local_data;               // Vetor local com parte dos dados em cada processo
    int local_poten = 0;             // Potencia parcial de cada processo
    int *partial_poten = NULL;      // Vetor para coletar potencias parciais no processo root
    int total_poten = 0;             // Potencia final (calculada pelo processo root)

    MPI_Init(&argc, &argv);

    // Obtém o rank (identificador) do processo atual
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Obtém o número total de processos em execução
    MPI_Comm_size(MPI_COMM_WORLD, &processadores_num);

    // Cada processo irá receber uma parte igual do vetor
    int chunk_tam = N / processadores_num;

    // Apenas o processo 0 (root) aloca e preenche o vetor com valores de 1 a 40
    if (rank == 0) {
        data = (int *)malloc(N * sizeof(int));
        for (i = 0; i < N; i++) {
            data[i] = i + 1;
        }
    }

    // Todos os processos alocam memória para seu pedaço do vetor
    local_data = (int *)malloc(chunk_tam * sizeof(int));

    // Scatter: distribui pedaços do vetor do root para todos os processos
    MPI_Scatter(data, chunk_tam, MPI_INT, local_data, chunk_tam, MPI_INT, 0, MPI_COMM_WORLD);
    
    
    // Cada processo calcula a potencia parcial de seu pedaço
    for (i = 0; i < chunk_tam; i++) {
        local_poten += local_data[i]*local_data[i];
    }

    // O processo root aloca memória para receber todas as potencias parciais
    if (rank == 0) {
        partial_poten = (int *)malloc(processadores_num * sizeof(int));
    }

    // Mostra o valor local de cada processo
    printf("Processo %d: valor local = %d\n", rank, local_poten);

    // Usa MPI_Reduce para somar todos os valores locais e enviar o resultado para o processo 0
    MPI_Reduce(&local_poten,     // endereço do valor a ser enviado
               &total_poten,     // onde armazenar o resultado (no processo root)
               1,                // número de elementos
               MPI_INT,          // tipo dos dados
               MPI_SUM,          // operação a ser realizada (soma)
               0,                // rank do processo root (que receberá o resultado)
               MPI_COMM_WORLD);  // comunicador

    // Apenas o processo root (0) imprime a soma final
    if (rank == 0) {
        // formula:
        // n*(n+1)*(n*2+1)/6 somatorio resultado tem que ser igual
        // somatorio resultado tem que ser igual
        int formula = N*(N+1)*(N*2+1)/6;
        printf("Processo %d: soma da potencia global = %d\n", rank, total_poten);
        printf("Resultado seguindo a formula = %d\n", formula);
        if (formula == total_poten) {
            printf("Valores conferem!");
        } else {
            printf("Valores não conferem!");
        }
    }
    // Libera a memória do vetor local
    free(local_data);

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}