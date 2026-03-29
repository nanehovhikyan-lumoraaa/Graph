#include "graph_isomorphism.h"

void sort_vertices_by_degree(const Graph *g, int order[SIZE]) {
    /* fill order[] with 0..n-1, then sort descending by degree */
    for (int i = 0; i < g->n; i++) order[i] = i;

    /* simple insertion sort — n ≤ 15 so this is perfectly fine */
    for (int i = 1; i < g->n; i++) {
        int key = order[i];
        int j   = i - 1;
        while (j >= 0 && g->degree[order[j]] < g->degree[key]) {
            order[j + 1] = order[j];
            j--;
        }
        order[j + 1] = key;
    }
}

void build_candidate_buckets(const Graph *g,
                             int buckets[SIZE][SIZE],
                             int bucket_size[SIZE]) {
    memset(bucket_size, 0, SIZE * sizeof(int));

    for (int v = 0; v < g->n; v++) {
        int d = g->degree[v];
        buckets[d][bucket_size[d]++] = v;
    }
}
