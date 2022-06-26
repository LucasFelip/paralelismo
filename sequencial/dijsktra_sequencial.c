#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>

// Total de cidades para construção do grafo
#define TOTALCIDADES 1000

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
}

// Funcao menorCaminho
// - Recebe a origem e destino para calculo
// - Aloca vetor necessário
// - Verifica as ligacoes que direta que a "cidade" possui
// - Por fim, é feito o calculo do menor caminho
// - Impresso o resultado
void dijkstra(int origem, int destino){
    int *anterior, i, aux, *verticesNoCaminho, calculo;
    double distMinima, auxDist;

    verticesNoCaminho = calloc(TOTALCIDADES, sizeof(int *));
    if (verticesNoCaminho == NULL){
        printf("Erro na alocacao\n");
        exit(-1);
    }

    for (i = 0; i < TOTALCIDADES; i++){
        verticesNoCaminho[i] = 0;
        if (distancias[(origem)*TOTALCIDADES + i] != -1)
            custos[i] = distancias[(origem)*TOTALCIDADES + i];
        else
            custos[i] = HUGE_VAL;
    }

    verticesNoCaminho[origem] = 1;
    custos[origem] = 0;
    do{
        distMinima = HUGE_VAL;
        for (i = 0; i < TOTALCIDADES; i++)
            if (!verticesNoCaminho[i])
                if (custos[i] >= 0 && custos[i] < distMinima){
                    distMinima = custos[i];
                    aux = i;
                }
        if (distMinima != HUGE_VAL && aux != destino){
            verticesNoCaminho[aux] = 1;
            for (i = 0; i < TOTALCIDADES; i++)
                if (!verticesNoCaminho[i])
                    if (distancias[aux * TOTALCIDADES + i] != -1 && custos[aux] + distancias[aux * TOTALCIDADES + i] < custos[i])
                        custos[i] = custos[aux] + distancias[aux * TOTALCIDADES + i]; 
        }
    } while (aux != destino && distMinima != HUGE_VAL);
}

// Funcao calculoDistancia
// - Dois for's que chamam a funcao para calculo do menor caminho
void calculoDistancia(){
    int i, j;
    for (i = 0; i < TOTALCIDADES; i++)
        for (j = 0; j < TOTALCIDADES; j++)
            dijkstra(i, j);
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
}


// Funcao principal Main
// - Roda toda a estrutura 
int main(int argc, char *argv[]){
    setlocale(LC_ALL, "Portuguese");
    time_t t_ini, t_fim;
    float temp;

    zeraDistancia();
    lerMapa();

    t_ini = time(NULL);
    calculoDistancia();
    t_fim = time(NULL);
    temp = difftime(t_fim,t_ini);
    printf("Tempo de execução: %.2f",temp);

    return 0;
}