#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

#define MAX_INSTRUCTIONS 100000
/*
typedef struct node{	
	int name;
}Vertice;

typedef struct edge1{	
	int **adj;
}AdjacentM;

typedef struct nodelist{
	Vertice info;
	int peso;
	struct list *next;	
}NodeList;

typedef struct edge2{
	NodeList *adj;
}AdjacentL;

typedef struct{
	AdjacentM *adj_type1; //matriz de adjacencia
	AdjacentL *adj_type2; //lista de adjacencia
	int num_vertice;
	int num_eagle;
}Graph;

void createGraphM(Graph *G)
void createGraphL(Graph *G)
void IG()
void VA(X)
void AA (Vertice X, Vertice Y, int P)
void RA (Vertice X, Vertice Y)
void IT()
void MP()
*/

Graph graph;
Graph *G = &graph;

int main(int argc, char* argv[])
{
	char tipo1, tipo2;
	int numeroV, numeroA, vertice1, vertice2, peso, i=0, j=0;

	scanf("%c %c %d %d", &tipo1, &tipo2, &numeroV, &numeroA);

	createGraph(G, tipo1, tipo2, numeroV, numeroA);

	IG(G);

	for(i = 0; i < numeroA; i++)
	{
		scanf("%d %d %d", &vertice1, &vertice2, &peso);
		AA(G, vertice1, vertice2, peso);
	}


	char *op;
	int arg1, arg2, arg3;

	for(i=0; i<MAX_INSTRUCTIONS; i++)
	{
		op = NULL;
		op = (char *) calloc (1,sizeof(char));

		scanf("%s", op);
	
		if (op[0] == 'I' && op[1] == 'G')
		{
			IG(G);
		}
	
		else if (op[0] == 'V' && op[1] == 'A')
		{
			scanf("%d\n", &arg1);

			VA(G, arg1);
		}
	
		else if (op[0] == 'A' && op[1] == 'A')
		{
			scanf("%d %d %d\n", &arg1, &arg2, &arg3);
			AA(G, arg1, arg2, arg3);
		}
	
		else if (op[0] == 'R' && op[1] == 'A')
		{
			scanf("%d %d\n", &arg1, &arg2);
			RA(G, arg1, arg2);
		}
	
		else if (op[0] == 'I' && op[1] == 'T')
		{
			IT(G);
		}

		else if (op[0] == 'M' && op[1] == 'P')
		{
			MP(G);
		}
	}

	return 0;
}