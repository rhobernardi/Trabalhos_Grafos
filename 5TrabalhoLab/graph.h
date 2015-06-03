#ifndef GRAPH_H
#define GRAPH_H

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
	int num_edge; 		//numero de arestas
	AdjacentM **matriz; //matriz de adjacencia
}Graph;


typedef struct p{
	int peso;
	int destino;
}No;


typedef struct {
	int tamanho;
	No **queue;
	int quantidade;
}Queue;


void createGraph(Graph *G, char t1, char t2, int nvertice, int nedge);


//////////////////////////////////////////// LAB 1 ////////////////////////////////////////////


void IG(Graph *G);										//imprimir grafo respeitando a representação;


void VA(Graph *G, Vertice X);							//imprimir vértices adjacentes ao vértice X 
														//(em ordem crescente dos índices dos vértices, por exemplo, “1 5 7” e não “7 1 5”);

void AA (Graph *G, Vertice X, Vertice Y, Peso P); 		//adicionar aresta entre os vértices X e Y com peso P 
														//(ATENÇÃO: OS PESOS SÃO MAIORES OU IGUAIS A 0);

void RA (Graph *G, Vertice X, Vertice Y); 				//remover aresta entre os vértices X e Y;


void IT(Graph *G); 										//imprimir transposto (caso não seja um dígrafo, ignore o comando)


void MP(Graph *G);										//imprimir aresta com menor peso (haverá apenas uma aresta com menor peso). 
														//Caso não seja um dígrafo, imprima a aresta com os índices dos vértices em ordem 
														//crescente, por exemplo, “3 7” e não “7 3” para a aresta entre os vértices 3 e 7.

//////////////////////////////////////////// LAB 2 ////////////////////////////////////////////

#define BRANCO	0
#define CINZA	1
#define PRETO	2


void DFSVerify(Graph *G, int i, int *color, int *predecessor, Lista *listaP);


Lista *DFS(Graph *G, int ini, int *predecessor);


void pathDFS(Graph *G, int origem, int dest);


//////////////////////////////////////////// LAB 3 ////////////////////////////////////////////


void DFSVOrdTop(Graph *G, int i, int *color, int *predecessor, Lista *listaP);


Lista *DFSOrdTop(Graph *G, int ini, int *predecessor);


int checaAntecessores(Graph *G);


void pathOrdTop(Graph *G, int origem, int dest);


//////////////////////////////////////////// LAB 4 ////////////////////////////////////////////


int somaArestas(Graph *G);

#define MAX 999

int Prim(Graph *G, Vertice V) ;


//////////////////////////////////////////// LAB 5 ////////////////////////////////////////////


#define NIL -1
#define INF 10000000

void Dijkstra(Graph *, Vertice, Vertice);

Queue *ini_queue(int tam);

void push(Queue *q, No* value);

void pop(Queue *q);

int empty(Queue *q);

No* top(Queue *q);

#endif