#include "fila.h"
#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

#define PESO	1

typedef int Vertice;
typedef int Peso;

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


#define BRANCO	0
#define CINZA	1
#define PRETO	2


void DFSVOrdTop(Graph *G, int i, int *color, int *predecessor, Lista *listaP)
{
    int j;
    
    color[i] = CINZA;
    
    for(j = 0; j < G->num_vertice; j++)
    {
        if(color[j] == BRANCO && G->matriz[i][j] == PESO)
        {
            predecessor[j] = i; 
            DFSVOrdTop(G, j, color, predecessor, listaP);
        }
    }
    
    color[i] = PRETO;
    entrar_inicio_lista_generica(listaP, &i);
}

Lista *DFSOrdTop(Graph *G, int ini, int *predecessor)
{
    int i; 
    Lista *listaP = criar_lista_generica(sizeof(int));
    
    int *color = (int*) calloc(G->num_vertice, sizeof(color)); 

    for(i = 0; i < G->num_vertice; i++)
    {
        predecessor[i] = -2; 
    }
    
    predecessor[ini] = -1;
    DFSVOrdTop(G, ini, color, predecessor, listaP);
    
    free(color);
  
    return listaP;
}

/*void printPath(Graph *G, int ini, int fim, int *predecessor)
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
}*/

int checaAntecessores(Graph *G)
{
	int i,j, count=0;

	for(j=0; j< G->num_vertice; j++)
	{
		for(i=0; i< G->num_vertice; i++)
		{
			if(G->matriz[i][j] == -1)
				count++;

			else break;
		}

		if(count == G->num_vertice)
			break;

		count = 0;
	}

	return j;
}

void path(Graph *G, int origem, int dest)
{
	int *predecessor, *distance, *pre, *pos, i;

	predecessor = (int *) malloc(G->num_vertice * sizeof(int));
	distance = (int *) malloc(G->num_vertice * sizeof(int));
	pre = (int *) malloc(G->num_vertice * sizeof(int));
	pos = (int *) malloc(G->num_vertice * sizeof(int));

	Lista *l = DFSOrdTop(G, checaAntecessores(G), predecessor);

	int aux;

	for(i=0; i<G->num_vertice; i++)
	{
		sair_inicio_lista_generica(l, &aux);
		printf("%d ", aux);
	}

	//DFS(G, 0, origem, predecessor, distance, pre, pos);
	//printPath(G, origem, dest, predecessor);

	free(predecessor);
	free(distance);
	free(pre);
	free(pos);
}