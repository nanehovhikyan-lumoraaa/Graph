#include "graph_isomorphism.h"

void init_graph(Graph *g, int n) {
    g->n = n;
    memset(g->adj, 0, sizeof(g->adj));
    memset(g->degree, 0, sizeof(g->degree));
}

void add_edge(Graph *g, int u, int v) {
    if (g->adj[u][v] == 0) {          /* avoid duplicate edges */
        g->adj[u][v] = 1;
        g->adj[v][u] = 1;
        g->degree[u]++;
        g->degree[v]++;
    }
}

void print_graph(const Graph *g) {
    printf("Vertices: %d\n", g->n);

    printf("Adjacency matrix:\n  ");
    for (int i = 0; i < g->n; i++) printf("%2d", i);
    printf("\n");

    for (int i = 0; i < g->n; i++) {
        printf("%2d", i);
        for (int j = 0; j < g->n; j++)
            printf("%2d", g->adj[i][j]);
        printf("\n");
    }

    printf("Degree sequence: ");
    for (int i = 0; i < g->n; i++)
        printf("%d ", g->degree[i]);
    printf("\n");
}