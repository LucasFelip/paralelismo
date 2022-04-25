#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#define TOTALCIDADES 5

FILE *file;
int distancias[TOTALCIDADES * TOTALCIDADES];

void criaGrafo(){
    file = fopen("mapa_de_5_elem.txt", "w");
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
                    fprintf(file,"%i - %i - %i\\n", origem, destino, distancia);
                }
            }
        }
    }
    fclose(file);
}

void zeraDistancia(){
    for (int i = 0; i < TOTALCIDADES * TOTALCIDADES; i++)
        distancias[i] = -1;
}

int main(void){
    srand((unsigned)TOTALCIDADES);
    zeraDistancia();
    criaGrafo();

    printf("Mapa gerado");
    return 0;
}