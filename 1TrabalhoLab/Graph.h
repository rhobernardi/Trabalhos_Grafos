#include <stdio.h>
#include <stdlib.h>

typedef int Vertice;
typedef int Peso;

//para usar com matriz de adjacencia
typedef int AdjacentM;

//para usar com lista de adjacencia
typedef struct nodelist{

	Vertice num;
	Peso peso;
	struct nodelist *next;
	
}NodeList;

typedef NodeList AdjacentL;

//mapa do Grafo
typedef struct{

	char type1; //tipo G ou D
	char type2; //tipo M ou L
	int num_vertice; //numero de vertices
	int num_eagle; //numero de arestas
	AdjacentM **matriz; //matriz de adjacencia
	AdjacentL **lista; //lista de adjacencia

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
		G->lista = NULL;	//quando type2 == 'M' não se usa lista de adj
		G->matriz = (int **) calloc ((G->num_vertice),sizeof(int *));

		for(i = 0; i < G->num_vertice; i++)
			G->matriz[i] = (int *) calloc ((G->num_vertice),sizeof(int));

		printf("\n\n Criou grafo de matriz\n\n");
	}

	else if(G->type2 == 'L') //com lista de adj
	{
		G->matriz = NULL; //quando type2 == 'L' não se usa matriz de adj
		G->lista = (NodeList **) calloc ((G->num_vertice),sizeof(NodeList *));

		for(i = 0; i < G->num_vertice; i++)
		{
			G->lista[i] = (NodeList *) calloc ((G->num_vertice),sizeof(NodeList));
			G->lista[i]->num = -1;
			G->lista[i]->peso = -1;
			G->lista[i]->next = NULL;
		}

		printf("\n\n Criou grafo de lista\n\n");
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
				if(G->matriz[i][j] == 0)
					printf(". ");

				else printf("%d ", G->matriz[i][j]);
			}

			printf("\n");
		}
	}

	else if(G->type2 == 'L') //imprime a lista se o grafo for feito com lista de adj
	{
		NodeList *node_aux; 
		for(i = 0; i < G->num_vertice; i++)
		{
			printf("%d. ", i);

			node_aux = G->lista[i]->next;

			while(node_aux != NULL)
			{	
				printf("%d(%d) ", node_aux->num, node_aux->peso);
				node_aux = node_aux->next;
			}

			if (node_aux == NULL)
			{
				printf("(null)");
			}

			printf("\n");
		}

		free(node_aux);
	}

	printf("\n");
} 

void VA(Graph *G, Vertice X)							//imprimir vértices adjacentes ao vértice X 
														//(em ordem crescente dos índices dos vértices, por exemplo, “1 5 7” e não “7 1 5”);
{
	if(G->type1 == 'G')
	{
		return;
	}

	else if(G->type1 == 'D')
	{
		return;
	}
}

void AA (Graph *G, Vertice X, Vertice Y, int P) 		//adicionar aresta entre os vértices X e Y com peso P 
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

		else if(G->type2 == 'L')
		{
			NodeList *node_aux1 = (NodeList *) malloc(sizeof(NodeList));

			if(G->type1 == 'G')
			{
				NodeList *pointer = G->lista[X];

				while(pointer->next != NULL)
				{
					pointer = pointer->next;
				}

				node_aux1->num = Y;
				node_aux1->peso = P;
				
				pointer->next = node_aux1;

				IG(G);

				pointer = G->lista[Y];

				while(pointer->next != NULL)
				{
					pointer = pointer->next;
				}

				free(node_aux1);

				NodeList *node_aux2 = (NodeList *) malloc(sizeof(NodeList));

				node_aux2->num = X;
				node_aux2->peso = P;

				pointer->next = node_aux2;

				IG(G);

				free(node_aux2);
				free(pointer);
			}

			else if(G->type1 == 'D')
			{
				NodeList *pointer = G->lista[X];

				while(pointer->next != NULL)
				{
					pointer = pointer->next;
				}

				node_aux1->num = Y;
				node_aux1->peso = P;
				
				pointer->next = node_aux1;

				free(pointer);
			}

			free(node_aux1);
		}
	}

	else return;
}

void RA (Graph *G, Vertice X, Vertice Y) 							//remover aresta entre os vértices X e Y;
{
	if(G->type1 == 'G')
	{
		return;
	}

	else if(G->type1 == 'D')
	{
		return;
	}
}

void IT(Graph *G) 										//imprimir transposto (caso não seja um dígrafo, ignore o comando)
{
	if(G->type1 == 'G') //ignora comando caso nao seja digrafo
	{
		return;
	}

	else if(G->type1 == 'D')
	{
		return;
	}
}

void MP(Graph *G)										//imprimir aresta com menor peso (haverá apenas uma aresta com menor peso). 
														//Caso não seja um dígrafo, imprima a aresta com os índices dos vértices em ordem 
														//crescente, por exemplo, “3 7” e não “7 3” para a aresta entre os vértices 3 e 7.
{

}