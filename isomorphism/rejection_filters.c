#include "graph_isomorphism.h"

int same_vertex_count(const Graph *g1, const Graph *g2) {
    return g1->n == g2->n;
}

int same_edge_count(const Graph *g1, const Graph *g2) {
    int e1 = 0, e2 = 0;
    for (int i = 0; i < g1->n; i++)
        for (int j = i + 1; j < g1->n; j++)
            if (g1->adj[i][j]) e1++;

    for (int i = 0; i < g2->n; i++)
        for (int j = i + 1; j < g2->n; j++)
            if (g2->adj[i][j]) e2++;

    return e1 == e2;
}

/* helper used by qsort — ascending integer comparison */
static int cmp_int(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

int same_degree_sequence(const Graph *g1, const Graph *g2) {
    int d1[SIZE], d2[SIZE];

    for (int i = 0; i < g1->n; i++) d1[i] = g1->degree[i];
    for (int i = 0; i < g2->n; i++) d2[i] = g2->degree[i];

    qsort(d1, g1->n, sizeof(int), cmp_int);
    qsort(d2, g2->n, sizeof(int), cmp_int);

    for (int i = 0; i < g1->n; i++)
        if (d1[i] != d2[i]) return 0;

    return 1;
}

int passes_filters(const Graph *g1, const Graph *g2) {
    if (!same_vertex_count(g1, g2))    return 0;
    if (!same_edge_count(g1, g2))      return 0;
    if (!same_degree_sequence(g1, g2)) return 0;
    return 1;
}
