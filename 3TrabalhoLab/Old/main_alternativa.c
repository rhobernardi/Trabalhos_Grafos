#include <stdlib.h>
#include <stdio.h>

#include "grafo.h"

static void ler_arestas(Grafo *grafo, int m);
static void ler_commandos(Grafo *grafo, void (*fn)(const Grafo*, int, vertice_fn, aresta_fn, void *));

/**
 * O programa principal receberá sempre um argumento.
 * Se este argumento for 'B', realiza a busca em largura,
 * caso contrário, a busca em profundidade.
 */
int main(int argc, char *argv[])
{
    Grafo *grafo;
    int n, m;

    if (argc < 2)
        return 1;

    scanf("%d %d\n", &n, &m);

    grafo = criar_grafo(n, 1, MATRIZ_DE_ADJACENCIA);

    ler_arestas(grafo, m);
    ler_commandos(grafo, argv[1][0] == 'B' ? busca_em_largura : busca_em_profundidade);

    destruir_grafo(grafo);

    return 0;
}

void ler_arestas(Grafo *grafo, int m)
{
    int u, v;

    int i;
    for (i = 0; i < m; ++i)
    {
        scanf("%d %d\n", &u, &v);
        adicionar_aresta(grafo, u, v, 1);
    }
}

/**
 * Estrutura que armazena as condições e retorno da busca.
 */
struct busca
{
    int origem;
    int destino;
    int *caminho;
    int tamanho;
};

/**
 * Callback passada para o algoritmo de busca que preenche apropriadamente o resultado da
 * busca.
 */
static int encontra_vertice(int vertice, const int *cor, const int *d,
        const int *p, struct busca *busca)
{
    int i;

    (void) cor; /* O vetor de cores não é utilizado aqui. */

    /* Se está processando o vértice destino, preencha o caminho. */
    if (vertice == busca->destino && d[vertice] >= 0)
    {
        busca->tamanho = d[vertice] + 1;
        for (i = d[vertice]; i >= 0; --i) /* Inverta o caminho. */
        {
            busca->caminho[i] = vertice;
            vertice = p[vertice];
        }

        return 0; /* Retorna para que a busca pare. */
    }

    return 1;
}

void ler_commandos(Grafo *grafo, void (*busca_fn)(const Grafo*, int, vertice_fn, aresta_fn, void *))
{
    struct busca busca;
    busca.caminho = (int *) malloc(n_vertices(grafo) * sizeof(int));
    int i;

    while (scanf("%d %d", &busca.origem, &busca.destino) != EOF)
    {
        busca.tamanho = 0;

        busca_fn(grafo, busca.origem, (vertice_fn) encontra_vertice, NULL, &busca);
        for (i = 0; i < busca.tamanho; ++i)
            printf("%d ", busca.caminho[i]);
        printf("\n");
    }

    free(busca.caminho);
}
