#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>

// Total de cidades para construção do grafo
#define TOTALCIDADES 500

//todos os arquivos gerados pelo grafo
FILE *ligacoes, *mapa, *cidades;

// Grafo de distancia entre as cidades
int distancias[TOTALCIDADES * TOTALCIDADES];


//  Todas as distancias e custos sao zeradas, pois na hora do algoritmo eh verificado
//  as cidades que tem ligacoes.
void zeraDistancia(){
    for (int i = 0; i < TOTALCIDADES * TOTALCIDADES; i++)
        distancias[i] = -1;
}

//  Funcao principal
//  - Rand para o total de ligacoes que o grafo irá ter
//  - Rand para qual cidade origem e destino
//  - Verifica se nao eh a mesma cidade e se ja nao possui ligacao entre as mesmas
//  - Rand para a distância
//  - Vetor distancias:
//      - Pos 0 ate (TOTALCIDADES - 1) = cidade 1
//      - Pos (TOTALCIDADES) ate ((2*TOTALCIDADES) -1) = cidade 2
int main(void){
    int origem, destino, i, ok, distancia, totalLigacoes;
    srand((unsigned)TOTALCIDADES);

    zeraDistancia();

    cidades = fopen("total_cidades.txt","w");
    fprintf(cidades,"%i",TOTALCIDADES);
    fclose(cidades);

    totalLigacoes = rand() % (TOTALCIDADES * 4);
    ligacoes = fopen("total_ligacoes.txt","w");
    fprintf(ligacoes,"%i", totalLigacoes);
    fclose(ligacoes);

    mapa = fopen("mapa_cidades.txt","w");
    for (i = 0; i < totalLigacoes; i++){
        ok = 0;
        while (ok == 0){
            origem = rand() % TOTALCIDADES;
            destino = rand() % TOTALCIDADES;
            if (origem != destino){
                if (distancias[(origem)*TOTALCIDADES + destino] == -1){
                    distancia = (rand() % 20) + 1;
                    distancias[(origem)*TOTALCIDADES + destino] = distancia;
                    ok = 1;
                    fprintf(mapa,"%i-%i-%i\n", origem, destino, distancia);
                }
            }
        }
    }
    fclose(mapa);
    return 0;
}