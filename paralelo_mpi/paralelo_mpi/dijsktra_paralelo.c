#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <sys/timeb.h>
#include <locale.h>
#include <time.h>

// Total de cidades para construção do grafo
#define TOTALCIDADES 500

// Todos os arquivos gerados pelo grafo
FILE *ligacoes, *mapa, *resultado;

// Grafo de distancia entre as cidades e custos
int distancias[TOTALCIDADES * TOTALCIDADES];
double custos[TOTALCIDADES];

// Todas as distancias e custos sao zeradas, pois na hora do algoritmo eh verificado
// as cidades que tem ligacoes.
void zeraDistancia( ){
    for (int i = 0; i < TOTALCIDADES * TOTALCIDADES; i++)
        distancias[i] = -1;
    for (int i = 0; i < TOTALCIDADES; i++)
        custos[i] = 0;
    printf(" Distancias zeradas \n");
}

// Funcao lerMapa()
// - Abre os arquivos de mapa e de ligações feitas
void lerMapa(){
    int origem, destino, i, distancia, totalLigacoes;

    ligacoes = fopen("./mapas/total_ligacoes.txt","r");
    fscanf(ligacoes,"%i",&totalLigacoes);

    mapa = fopen("./mapas/mapa_cidades.txt","r");
    for (i = 0; i < totalLigacoes; i++){
        fscanf(mapa,"%i-%i-%i\n", &origem, &destino, &distancia);
        distancias[(origem)*TOTALCIDADES + destino] = distancia;
    }
    printf(" Mapa lido com sucesso \n");
}

int matrix_size(MPI_Comm comm) {
    int n = 8;
    MPI_Bcast(&n, 1, MPI_INT, 0, comm);
    return n;
}

// Funcao menorCaminho
// - Recebe a origem e destino para calculo
// - Aloca vetor necessário
// - Verifica as ligacoes que direta que a "cidade" possui
// - Por fim, é feito o calculo do menor caminho
// - Impresso o resultado
void dijkstra(int origem, int destino){
    int i = 0, aux = 0;
    int* verticesNoCaminho; // Vertices que sao acessados para o menor caminho
    double distMinima; // Custoo com os caminhos

    verticesNoCaminho = (int*)calloc(TOTALCIDADES, sizeof(int));

    if (verticesNoCaminho == NULL) {
        printf("ERROR: Erro na alocacao \n");
        exit(-1);
    }


    for (i = 0; i < TOTALCIDADES; i++) {
        verticesNoCaminho[i] = 0;
        if (distancias[(origem)*TOTALCIDADES + i] != -1)
            custos[i] = distancias[(origem)*TOTALCIDADES + i];
        else
            custos[i] = HUGE_VAL;
    }

    verticesNoCaminho[origem] = 1;
    custos[origem] = 0;

    // Principal la�o
    do {
        distMinima = HUGE_VAL;

        for (i = 0; i < TOTALCIDADES; i++)
            if (!verticesNoCaminho[i])
                if (custos[i] >= 0 && custos[i] < distMinima) {
                    distMinima = custos[i];
                    aux = i;
                }

        if (distMinima != HUGE_VAL && aux != destino) {
            verticesNoCaminho[aux] = 1;
            for (i = 0; i < TOTALCIDADES; i++) 
                if (!verticesNoCaminho[i])
                    if (distancias[aux * TOTALCIDADES + i] != -1 && custos[aux] + distancias[aux * TOTALCIDADES + i] < custos[i])
                        custos[i] = custos[aux] + distancias[aux * TOTALCIDADES + i];

        }
    } while (aux != destino && distMinima != HUGE_VAL);;
}

// Funcao calculoDistancia
// - Dois for's que chamam a funcao para calculo do menor caminho
void calculoDistancia(int inicio, int fim) {
    int i, j;
    for (i = inicio; i < fim; i++)
        for (j = 0; j < TOTALCIDADES; j++)
            dijkstra(i, j);

}
// Funcao principal Main
// - Roda toda a estrutura 
int main(int argc, char** argv) {
    setlocale(LC_ALL, "portuguese");
    time_t t_ini, t_fim;
    float temp;
    int inicio, fim, ntasks, rank;
    MPI_Request request;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    ntasks = 32;

    int nDados = TOTALCIDADES / ntasks;
    inicio = rank * nDados;

    if (rank == ntasks - 1 && TOTALCIDADES % ntasks != 0)
        fim = TOTALCIDADES;
    else
        fim = nDados + rank * nDados;

    printf("ALGORITMO PARELIZADO EM MPI\n\n");

    srand((unsigned)TOTALCIDADES);
	zeraDistancia();
	lerMapa();

    printf(" Rank = %d\n", rank);
    printf(" Tasks = %d\n", ntasks);
	t_ini = time(NULL);
    MPI_Barrier(MPI_COMM_WORLD);
    calculoDistancia(inicio, fim);
    MPI_Barrier(MPI_COMM_WORLD);
    t_fim = time(NULL);
    temp = difftime(t_fim, t_ini);

    if (rank == 0)
        printf(" Tempo de execução: %.0f\n", temp);
    
    MPI_Finalize();
    return 0;
}