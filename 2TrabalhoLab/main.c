#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define MAX_INSTRUCTIONS 1000

Graph graph;
Graph *G = &graph;

int main(int argc, char* argv[])
{
	char tipo1, tipo2;
	int numeroV, numeroA, vertice1, vertice2, peso = 1, i = 0, j = 0;

	tipo1 = 'D';
	tipo2 = 'M';

	scanf("%d %d", &numeroV, &numeroA);

	createGraph(G, tipo1, tipo2, numeroV, numeroA);

	//IG(G);

	for(i = 0; i < numeroA; i++)
	{
		scanf("%d %d", &vertice1, &vertice2);
		AA(G, vertice1, vertice2, peso);
	}

	int origem, destino;

	/*for(i = 0; i < numeroA; i++)
	{
		scanf("%d %d", &origem, &destino);
	}*/

	while(scanf("%d %d", &origem, &destino) != EOF)
	{																																																																																																												
		path(G, origem, destino);
		printf("%d %d\n", origem, destino);
	}

	return 0;
}