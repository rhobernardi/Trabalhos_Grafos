#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

#define WHITE 	0
#define GRAY 	1
#define BLACK 	2

typedef int Vertice;
typedef int Peso;

typedef struct {
	int ini, fim;
	int tamanho;
	int *queue;
	int quantidade;
}Queue;

//para usar com matriz de adjacencia
typedef Peso AdjacentM;

//mapa do Grafo
typedef struct g{

	char type1; 		//tipo G ou D
	char type2; 		//tipo M ou L
	int num_vertice; 	//numero de vertices
	int num_eagle; 		//numero de arestas
	AdjacentM **matriz; //matriz de adjacencia

}Graph;


void createGraph(Graph *G, char t1, char t2, int nvertice, int neagle)
{
	int i,j;

	G->type1 = t1;
	G->type2 = t2;
	G->num_vertice = nvertice;
	G->num_eagle = neagle;

	if(G->type2 == 'M') //com matriz de adj
	{
		G->matriz = (int **) calloc ((G->num_vertice),sizeof(int *));

		for(i = 0; i < G->num_vertice; i++)
			G->matriz[i] = (int *) calloc ((G->num_vertice),sizeof(int));

		for(i = 0; i < G->num_vertice; i++)
			for(j = 0; j < G->num_vertice; j++)
				G->matriz[i][j] = -1;

		//printf("\n\n Criou grafo de matriz\n\n");
	}
}


void IG(Graph *G) 										//imprimir grafo respeitando a representação;
{
	int i, j;

	if(G->type2 == 'M')	//imprime a matriz se o grafo for feito com matriz de adj
	{
		for(i = 0; i < G->num_vertice; i++)
		{
			for(j = 0; j < G->num_vertice; j++)
			{	
				if(G->matriz[i][j] < 0)
					printf(". ");

				else printf("%d ", G->matriz[i][j]);
			}

			printf("\n");
		}
	}
} 

void VA(Graph *G, Vertice X)							//imprimir vértices adjacentes ao vértice X 
														//(em ordem crescente dos índices dos vértices, por exemplo, “1 5 7” e não “7 1 5”);
{
	int i;

	if(G->type2 == 'M')
	{
		for(i = 0; i < G->num_vertice; i++)
		{
			if(G->matriz[X][i] != -1)
				printf("%d ", i);
		}

		printf("\n");
	}
}

void AA (Graph *G, Vertice X, Vertice Y, Peso P) 		//adicionar aresta entre os vértices X e Y com peso P 
														//(ATENÇÃO: OS PESOS SÃO MAIORES OU IGUAIS A 0);
{
	if(P >= 0)
	{
		if(G->type2 == 'M')
		{
			if(G->type1 == 'G')
			{
				G->matriz[X][Y] = P;
				G->matriz[Y][X] = P;
			}

			else if(G->type1 == 'D')
			{
				G->matriz[X][Y] = P;
			}
		}
	}

	else return;
}

void RA (Graph *G, Vertice X, Vertice Y) 							//remover aresta entre os vértices X e Y;
{
	if(G->type2 == 'M')
	{
		if(G->type1 == 'G')
		{
			G->matriz[X][Y] = -1;
			G->matriz[Y][X] = -1;
		}

		else if(G->type1 == 'D')
		{
			G->matriz[X][Y] = -1;
		}
	}
}

void IT(Graph *G) 										//imprimir transposto (caso não seja um dígrafo, ignore o comando)
{
	if(G->type1 == 'G') //ignora comando caso nao seja digrafo
		return;

	else if(G->type1 == 'D')
	{
		int i, j;

		if(G->type2 == 'M')	//imprime a matriz se o grafo for feito com matriz de adj
		{
			for(i = 0; i < G->num_vertice; i++)
			{
				for(j = 0; j < G->num_vertice; j++)
				{	
					if(G->matriz[j][i] < 0)
						printf(". ");

					else printf("%d ", G->matriz[j][i]);
				}

				printf("\n");
			}
		}
	}
}

void MP(Graph *G)										//imprimir aresta com menor peso (haverá apenas uma aresta com menor peso). 
														//Caso não seja um dígrafo, imprima a aresta com os índices dos vértices em ordem 
														//crescente, por exemplo, “3 7” e não “7 3” para a aresta entre os vértices 3 e 7.
{
	int i, j;

	if(G->type2 == 'M')
	{
		if(G->type1 == 'G')
		{
			int aux, auxI, auxJ;

			for(i = 0; i < G->num_vertice; i++)
			{
				for(j = 0; j < G->num_vertice; j++)
				{
					if(G->matriz[i][j] > -1)
						aux = G->matriz[i][j];
				}
			}

			for(i = 0; i < G->num_vertice; i++)
			{
				for(j = 0; j < G->num_vertice; j++)
				{
					if(G->matriz[i][j] < aux && G->matriz[i][j] > -1)
					{
						aux = G->matriz[i][j];
						auxI = i;
						auxJ = j;
					}
				}
			}

			if(auxI < auxJ) printf("%d %d\n", auxI, auxJ);				//imprime sempre o vertice menor primeiro

			else printf("%d %d\n", auxJ, auxI);
		}

		if(G->type1 == 'D')
		{
			int aux, auxI, auxJ;

			for(i = 0; i < G->num_vertice; i++)
			{
				for(j = 0; j < G->num_vertice; j++)
				{
					if(G->matriz[i][j] > -1)
					{
						aux = G->matriz[i][j];
						break;
					}
				}
			}

			for(i = 0; i < G->num_vertice; i++)
			{
				for(j = 0; j < G->num_vertice; j++)
				{
					if(G->matriz[i][j] < aux && G->matriz[i][j] > -1)
					{
						aux = G->matriz[i][j];
						auxI = i;
						auxJ = j;
					}
				}
			}

			printf("%d %d\n", auxI, auxJ);
		}
	}
}

Queue *ini_queue(int tam)
{
	Queue *q = (Queue *) malloc(sizeof(Queue));
	q->queue = (int *) malloc(tam*sizeof(int));
	q->tamanho = tam;
	q->ini = q->fim = q->quantidade = 0;

	return q;
}

void push(Queue *q, int value)
{
	q->queue[q->fim] = value;
	q->fim = q->fim++ % q->tamanho;
	q->quantidade++;
}

void pop(Queue *q)
{
	q->ini = q->ini++ % q->tamanho;
	q->quantidade--;
}

int empty(Queue *q)
{
	if(q->quantidade == 0)
		return 1;

	else return 0;
}

int top(Queue *q)
{
	return q->queue[q->ini];
}

void BFS(Graph *G, int root, int *predecessor, int *distance, int *pre, int *pos) 
{
	int i, i_pre = 0, i_pos = 0;

	int *color = (int *) malloc(G->num_vertice * sizeof(int));

	Queue *q = ini_queue(G->num_vertice + 1);

	for(i = 0; i < G->num_vertice; i++) 
	{
		color[i] = WHITE;
		predecessor[i] = distance[i] = -1;
	}

	color[root] = GRAY;

	pre[i_pre+1] = root;

	distance[root] = 0;

	predecessor[root] = -1;

	push(q, root);

	//printf("\n\ndeu push\n\n");

	while(!empty(q)) 
	{
		int u = top(q);

		for(i = 0; G->matriz[u][i] != -1; i++) 
		{
			int v = G->matriz[u][i];

			if(color[v] == WHITE) 
			{
				color[v] = GRAY;
				pre[i_pre++] = v;
				distance[v] = distance[u] + 1;
				predecessor[v] = u;
				push(q, v);
			}
		}

		pop(q);
		color[u] = BLACK;
		pos[i_pos+1] = u;
	}

	free(color);
}


void printPath(Graph *G, int ini, int fim, int *predecessor)
{
	if(ini != fim)
	{
		printPath(G, ini, predecessor[fim], predecessor);
		printf("%d ", fim);
	}

	else if(ini == fim)
	{
		printf("%d ", ini);
	}
	/*int i;
	for(i =0; i < G->num_vertice; i++)
	{
		printf("%d ", predecessor[i]);
	}*/
}

void path(Graph *G, int origem, int dest)
{
	int *predecessor, *distance, *pre, *pos;

	predecessor = (int *) malloc(G->num_vertice * sizeof(int));
	distance = (int *) malloc(G->num_vertice * sizeof(int));
	pre = (int *) malloc(G->num_vertice * sizeof(int));
	pos = (int *) malloc(G->num_vertice * sizeof(int));

	BFS(G, origem, predecessor, distance, pre, pos);
	printPath(G, origem, dest, predecessor);

	free(predecessor);
	free(distance);
	free(pre);
	free(pos);
}