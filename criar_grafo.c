#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#define TOTALCIDADES 5

int distancias[TOTALCIDADES * TOTALCIDADES];

void criaGrafo(){
    int origem, destino, totalLigacoes, i, ok, distancia;
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
                    printf("- %i - %i - %i - \n", origem, destino, distancia);
                }
            }
        }
    }
}

void zeraDistancia(){
    for (int i = 0; i < TOTALCIDADES * TOTALCIDADES; i++)
        distancias[i] = -1;
}