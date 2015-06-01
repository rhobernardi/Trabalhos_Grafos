#include "fila.h"
#include "lista.h"

#include "graph.h"

#include <stdio.h>
#include <stdlib.h>


void createGraph(Graph *G, char t1, char t2, int nvertice, int nedge)
{
	int i,j;

	G->type1 = t1;
	G->type2 = t2;
	G->num_vertice = nvertice;
	G->num_edge = nedge;

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


//////////////////////////////////////////// LAB 1 ////////////////////////////////////////////


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


//////////////////////////////////////////// LAB 2 ////////////////////////////////////////////


void DFSVerify(Graph *G, int i, int *color, int *predecessor, Lista *listaP)
{
	int j;
	
	color[i] = CINZA;
	
	for(j = 0; j < G->num_vertice; j++)
	{
		if(color[j] == BRANCO && G->matriz[i][j] == PESO)
		{
			predecessor[j] = i; 
			DFSVerify(G, j, color, predecessor, listaP);
		}
	}
	
	color[i] = PRETO;
	entrar_inicio_lista_generica(listaP, &i);
}


Lista *DFS(Graph *G, int ini, int *predecessor)
{
	int i; 
	Lista *listaP = criar_lista_generica(sizeof(int));
	
	int *color = (int*) calloc(G->num_vertice, sizeof(color)); 

	for(i = 0; i < G->num_vertice; i++)
	{
		predecessor[i] = -2; 
	}
	
	predecessor[ini] = -1;
	DFSVerify(G, ini, color, predecessor, listaP);
	
	free(color);

	return listaP;
}


void pathDFS(Graph *G, int origem, int dest)
{
	if(G->type1 == 'D')
	{
		int *predecessor, *distance, *pre, *pos, i;
	
		predecessor = (int *) malloc(G->num_vertice * sizeof(int));
		distance = (int *) malloc(G->num_vertice * sizeof(int));
		pre = (int *) malloc(G->num_vertice * sizeof(int));
		pos = (int *) malloc(G->num_vertice * sizeof(int));
	
		Lista *l = DFS(G, origem, predecessor);
	
		int aux;
	
		for(i=0; i<G->num_vertice; i++)
		{
			sair_inicio_lista_generica(l, &aux);
			printf("%d ", aux);
		}
		
		free(predecessor);
		free(distance);
		free(pre);
		free(pos);

	} else {

		printf("\nÍt's not a digraph.\n");
	}
}



//////////////////////////////////////////// LAB 3 ////////////////////////////////////////////



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


void pathOrdTop(Graph *G, int origem, int dest)
{
	if(G->type1 == 'D')
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
		
		free(predecessor);
		free(distance);
		free(pre);
		free(pos);

	} else {

		printf("\nÍt's not a digraph.\n");
	}
}


//////////////////////////////////////////// LAB 4 ////////////////////////////////////////////


int somaArestas(Graph *G)
{
	int i, j, soma = 0;

	for (i = 0; i < G->num_vertice; ++i)
	{
		for (j = i+1; j < G->num_vertice; ++j)
		{
			if(G->matriz[i][j] != -1)
				soma += G->matriz[i][j];
		}
	}

	return soma;
}


int Prim(Graph *G, Vertice V) 
{
	int w, v, valor, i_s, i_f, nodup, menor_custo = 0, auxI = 0, auxJ = 0;
	Vertice i, j;
	Vertice selecionados[G->num_vertice], adjacent[G->num_vertice], adjacent_valor[G->num_vertice];
	Graph AGM;

	//inicializa os vetores
	createGraph(&AGM, 'G', 'M', G->num_vertice, G->num_edge);
	for (i = 0; i < G->num_vertice; i++) {
		selecionados[i] = 0;
		adjacent[i] = 0;
	}

	selecionados[V] = 1;

	while (menor_custo != MAX) 
	{// Quando o menor custo for o custo máximo, significará que não tem adjacent.

	//zera adjacent
	for (i = 0; i < G->num_vertice; i++)
		adjacent[i] = 0;

	//define adjacent
	for (i = 0; i < G->num_vertice; i++)
		if (selecionados[i] == 1)
			for (j = 0; j < G->num_vertice; j++)
				if (G->matriz[i][j] != -1 && selecionados[j] == 0)
					adjacent[j] = 1;

//Escolhe menor custo
	menor_custo = MAX; //Inicializa o menor custo com o custo maximo
	for (i = 0; i < G->num_vertice; i++)
		if (selecionados[i] == 1)
			for (j = 0; j < G->num_vertice; j++)
				if (i != j && adjacent[j] == 1 && G->matriz[i][j] != -1)
					if (G->matriz[i][j] < menor_custo && G->matriz[i][j] != -1) {
						auxI = i;
						auxJ = j;
						menor_custo = G->matriz[i][j];
					}

				if(menor_custo != MAX){
					AA(&AGM, auxI, auxJ, menor_custo);
					selecionados[auxI] = 1;
					selecionados[auxJ] = 1;
				}
	}

	return somaArestas(&AGM);
}


//////////////////////////////////////////// LAB 5 ////////////////////////////////////////////



void Dijkstra(Graph *G, int origem, int destino, int *custos)
{
	int i,v, cont = 0;
   int *ant, *tmp;
   int *z;     /* vertices para os quais se conhece o caminho minimo */
   double min;
   double dist[vertices]; /* vetor com os custos dos caminhos */

   z = calloc (vertices, sizeof(int *));
   if (z == NULL) {
      printf ("** Erro: Memoria Insuficiente **");
      exit(-1);
   }

   for (i = 0; i < vertices; i++) {
      if (custos[(origem - 1) * vertices + i] !=- 1) {
         ant[i] = origem - 1;
         dist[i] = custos[(origem-1)*vertices+i];
      }
      else {
         ant[i]= -1;
         dist[i] = HUGE_VAL;
      }
      z[i]=0;
   }
   z[origem-1] = 1;
   dist[origem-1] = 0;

   /* Laco principal */
   do {

      /* Encontrando o vertice que deve entrar em z */
      min = HUGE_VAL;
      for (i=0;i<vertices;i++)
         if (!z[i])
            if (dist[i]>=0 && dist[i]<min) {
               min=dist[i];v=i;
            }

      /* Calculando as distancias dos novos vizinhos de z */
      if (min != HUGE_VAL && v != destino - 1) {
         z[v] = 1;
         for (i = 0; i < vertices; i++)
            if (!z[i]) {
               if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i]) {
                     dist[i] = dist[v] + custos[v*vertices+i];
                  ant[i] =v;
                  }
              }
      }
   } while (v != destino - 1 && min != HUGE_VAL);

   /* Mostra o Resultado da busca */
   printf("\tDe %d para %d: \t", origem, destino);
   if (min == HUGE_VAL) {
      printf("Nao Existe\n");
      printf("\tCusto: \t- \n");
   }
   else {
      i = destino;
      i = ant[i-1];
      while (i != -1) {
      //   printf("<-%d",i+1);
         tmp[cont] = i+1;
         cont++;
         i = ant[i];
      }

      for (i = cont; i > 0 ; i--) {
         printf("%d -> ", tmp[i-1]);
      }
      printf("%d", destino);

      printf("\n\tCusto:  %d\n",(int) dist[destino-1]);
   }
}