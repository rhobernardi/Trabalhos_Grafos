#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

//#define MAX_INSTRUCTIONS 1000

Graph graph;
Graph *G = &graph;

int main(int argc, char* argv[])
{
	char tipo1, tipo2;
	int numeroV, numeroA, vertice1, vertice2, peso = 1, i = 0, j = 0;

	tipo1 = 'D'; //tipo Digrafo
	tipo2 = 'M'; //tipo matriz de adj

	scanf("%d %d", &numeroV, &numeroA);

	createGraph(G, tipo1, tipo2, numeroV, numeroA);

	IG(G);

	for(i = 0; i < numeroA; i++)
	{
		scanf("%d %d %d", &vertice1, &vertice2, &peso);
		AA(G, vertice1, vertice2, peso);
	}

	int origem, destino;

	while(scanf("%d %d", &origem, &destino) != EOF){

		printf("origem: %d  destino: %d\n", origem, destino);
		Dijkstra(G, origem, destino);

	}

/*printf("\n");
IG(G);
printf("\n");*/

	return 0;
}