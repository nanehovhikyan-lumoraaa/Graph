#include "graph_isomorphism.h"

int are_isomorphic(const Graph *g1, const Graph *g2, int perm[SIZE]) {
    /* 1. quick rejection */
    if (!passes_filters(g1, g2)) return 0;

    /* 2. preprocessing */
    int order[SIZE];
    int buckets[SIZE][SIZE];
    int bucket_size[SIZE];

    sort_vertices_by_degree(g1, order);
    build_candidate_buckets(g2, buckets, bucket_size);

    /* 3. backtracking search */
    int used[SIZE];
    memset(used, 0, sizeof(used));
    memset(perm, -1, SIZE * sizeof(int));   /* -1 = unmapped */

    return backtrack(g1, g2, perm, used, order,
                     buckets, bucket_size, 0);
}

void print_mapping(const Graph *g1, int perm[SIZE], int order[SIZE]) {
    printf("Isomorphism mapping found:\n");
    printf("G1 vertex  -->  G2 vertex\n");
    printf("--------------------------\n");
    for (int i = 0; i < g1->n; i++)
        printf("    %2d      -->     %2d\n", order[i] + 1, perm[i] + 1);
}