# Algoritmo de Dijkstra
## Explicação do algoritmo
A implementação tem como foco soluciona o problema do caminho mais curto num grafo dirigido ou não dirigido com arestas de peso não negativo. O algoritmo que serve para resolver o mesmo problema em um grafo com pesos negativos é o algoritmo de Bellman-Ford, que possui maior tempo de execução que o Dijkstra.

![alt text](http://siddarthareddy.weebly.com/uploads/2/8/7/9/28799429/4999443.png?468)

O algoritmo considera um conjunto S de menores caminhos, iniciado com um vértice inicial I. A cada passo do algoritmo busca-se nas adjacências dos vértices pertencentes a S aquele vértice com menor distância relativa a I e adiciona-o a S e, então, repetindo os passos até que todos os vértices alcançáveis por I estejam em S. Arestas que ligam vértices já pertencentes a S são desconsideradas.

O algoritmo foi montando com base no exemplo mais comum da implmentação do mesmo, que é: alguém precisa se deslocar de uma cidade para outra. Para isso, ela dispõe de várias estradas, que passam por diversas cidades. Qual delas oferece uma trajetória de menor caminho?

## Algoritmo em OpenMP
O OpenMP é uma interface de programação de aplicativo para a programação multi-processo de memória compartilhada em múltiplas plataformas. Permite acrescentar simultaneidade aos programas escritos em C, C++ e Fortran sobre a base do modelo de execução fork-join.

## Algoritmo em OpenMPI
O Open MPI Project é uma implementação de código aberto da especificação Message Passing Interface (MPI) desenvolvida e mantida por um consórcio de parceiros acadêmicos, de pesquisa e do setor. O Open MPI é, portanto, capaz de combinar o conhecimento, as tecnologias e os recursos de toda a comunidade de computação de alto desempenho para construir a melhor biblioteca MPI disponível. O Open MPI oferece vantagens para fornecedores de sistemas e software, desenvolvedores de aplicativos e pesquisadores de ciência da computação.


