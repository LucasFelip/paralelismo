#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <omp.h>

// Total de cidades para constru��o do grafo
#define TOTALCIDADES 100

// Total de threads que devem ser usadas
#define threads 25

// Todos os arquivos gerados pelo grafo
FILE* ligacoes, * mapa, * resultado;

// Grafo de distancia entre as cidades e custos
int distancias[TOTALCIDADES * TOTALCIDADES];
double custos[TOTALCIDADES];

//  Todas as distancias e custos sao zeradas, pois na hora do algoritmo eh verificado
//  as cidades que tem ligacoes.
void zeraDistancia() {
    for (int i = 0; i < TOTALCIDADES * TOTALCIDADES; i++)
        distancias[i] = -1;
    for (int i = 0; i < TOTALCIDADES; i++)
        custos[i] = 0;
}

// Funcao lerMapa()
// - Abre os arquivos de mapa e de liga��es feitas
void lerMapa() {
    int origem, destino, i, distancia, totalLigacoes;

    ligacoes = fopen("programa-o_sequencial_paralela/mapas/total_ligacoes.txt","r");
    fscanf(ligacoes, "%i", &totalLigacoes);

    mapa = fopen("programa-o_sequencial_paralela/mapas/total_ligacoes.txt","r");
    for (i = 0; i < totalLigacoes; i++) {
        fscanf(mapa, "%i-%i-%i\n", &origem, &destino, &distancia);
        distancias[(origem)*TOTALCIDADES + destino] = distancia;
    }
}

void main() {
    //int n, id, i;
    //n = 50;

    zeraDistancia();
    lerMapa();
    //calculoDistancia();

    /*
    #pragma omp parallel num_threads(threads) 
    {
        #pragma omp for
        for (i = 0; i < n; i++) {
            id = omp_get_thread_num();
            printf("Thread_id = %d, i= %d , m=%d\n", id, i, threads);
        }
    }
    */
}