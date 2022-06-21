#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <omp.h>

// Total de cidades para constru��o do grafo
#define TOTALCIDADES 500

// Todos os arquivos gerados pelo grafo
FILE *ligacoes, *mapa, *resultado;

// Grafo de distancia entre as cidades e custos
int distancias[TOTALCIDADES * TOTALCIDADES];
double custos[TOTALCIDADES];

// Todas as distancias e custos sao zeradas, pois na hora do algoritmo eh verificado
// as cidades que tem ligacoes.
void zeraDistancia() {
    for (int i = 0; i < TOTALCIDADES * TOTALCIDADES; i++)
        distancias[i] = -1;
    for (int i = 0; i < TOTALCIDADES; i++)
        custos[i] = 0;
    printf(" Distancias zeradas \n");
}

// Funcao lerMapa()
// - Abre os arquivos de mapa e de liga��es feitas
void lerMapa() {
    int origem, destino, i, distancia, totalLigacoes;

    ligacoes = fopen("./mapas/total_ligacoes.txt", "r");
    fscanf(ligacoes, "%i", &totalLigacoes);

    mapa = fopen("./mapas/mapa_cidades.txt", "r");
    for (i = 0; i < totalLigacoes; i++) {
        fscanf(mapa, "%i-%i-%i\n", &origem, &destino, &distancia);
        distancias[(origem)*TOTALCIDADES + destino] = distancia;
    }
    printf(" Mapa lido com sucesso \n");
}

// Funcao menorCaminho
// - Recebe a origem e destino para calculo
// - Aloca vetor necessário
// - Verifica as ligacoes que direta que a "cidade" possui
// - Por fim, é feito o calculo do menor caminho
// - Impresso o resultado
void dijkstra(int origem, int destino) {
    int* anterior, i, aux = 0, * verticesNoCaminho, calculo;
    double distMinima, auxDist;

    verticesNoCaminho = calloc(TOTALCIDADES, sizeof(int*));
    if (verticesNoCaminho == NULL) {
        printf(" Erro na alocacao\n");
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
    
    #pragma omp parallel private(i, aux)
    {
        do {
            distMinima = HUGE_VAL;
            for (i = 0; i < TOTALCIDADES; i++)
            #pragma omp single
            {
                if (!verticesNoCaminho[i])
                    if (custos[i] >= 0 && custos[i] < distMinima) {
                        distMinima = custos[i];
                        aux = i;
                    }
            }
            if (distMinima != HUGE_VAL && aux != destino) {
                verticesNoCaminho[aux] = 1;
                for (i = 0; i < TOTALCIDADES; i++) {
                    #pragma omp barrier
                    if (!verticesNoCaminho[i])
                        if (distancias[aux * TOTALCIDADES + i] != -1 && custos[aux] + distancias[aux * TOTALCIDADES + i] < custos[i])
                            custos[i] = custos[aux] + distancias[aux * TOTALCIDADES + i];
                    #pragma omp barrier
                }
                
            }
        } while (aux != destino && distMinima != HUGE_VAL);
    }
}

// Funcao calculoDistancia
// - Dois for's que chamam a funcao para calculo do menor caminho
void calculoDistancia() {
    int i, j;
    for (i = 0; i < TOTALCIDADES; i++)
        for (j = 0; j < TOTALCIDADES; j++)
            dijkstra(i, j);
}

// Funcao principal Main
// - Roda toda a estrutura 
void main() {
    setlocale(LC_ALL, "Portuguese");

    double t_ini, t_fim;

    zeraDistancia();
    lerMapa();

    t_ini = omp_get_wtime();
    calculoDistancia();  
    t_fim = omp_get_wtime();
    printf(" Runtime: %.2f ms\n", (t_fim - t_ini) * 1000);
}