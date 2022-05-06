#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <omp.h>

// Total de cidades para construção do grafo
#define TOTALCIDADES 100

//todos os arquivos gerados pelo grafo
FILE *ligacoes, *mapa, *resultado;

// Grafo de distancia entre as cidades e custos
int distancias[TOTALCIDADES * TOTALCIDADES];
double custos[TOTALCIDADES];

//  Todas as distancias e custos sao zeradas, pois na hora do algoritmo eh verificado
//  as cidades que tem ligacoes.
void zeraDistancia( ){
    for (int i = 0; i < TOTALCIDADES * TOTALCIDADES; i++)
        distancias[i] = -1;
    for (int i = 0; i < TOTALCIDADES; i++)
        custos[i] = 0;
}

//  Funcao calculoDistancia
//  - Dois for's que chamam a funcao para calculo do menor caminho
void calculoDistancia(){
    int i, j;
    resultado = fopen("resultado.txt","w");
    for (i = 0; i < TOTALCIDADES; i++)
        for (j = 0; j < TOTALCIDADES; j++)
            //dijkstra(i, j);
    fclose(resultado);
}

// Funcao lerMapa()
// - Abre os arquivos de mapa e de ligações feitas
void lerMapa(){
    int origem, destino, i, distancia, totalLigacoes;

    ligacoes = fopen("./mapas/total_ligacoes.txt","r");
    fscanf(ligacoes,"%i",&totalLigacoes);

    mapa = fopen("./mapas/mapa_100_cidades.txt","r");
    for (i = 0; i < totalLigacoes; i++){
        fscanf(mapa,"%i-%i-%i\n", &origem, &destino, &distancia);
        distancias[(origem)*TOTALCIDADES + destino] = distancia;
    }
}

int main(int argc, char *argv[]){

    #pragma omp parallel num_threads(10)
    {
        printf("Hello World\n");
        zeraDistancia();
        lerMapa();
        //calculoDistancia();
        return 1;
    }
}