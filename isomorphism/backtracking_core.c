#include "graph_isomorphism.h"

int is_compatible(const Graph *g1, const Graph *g2,
                  int perm[SIZE], int order[SIZE],
                  int depth, int candidate) {
    /*
     * We want to map G1-vertex order[depth] → G2-vertex candidate.
     * For every already-mapped G1-vertex order[i] (i < depth):
     *   edge exists in G1  ⟺  edge exists in G2 between the mapped vertices.
     */
    for (int i = 0; i < depth; i++) {
        int g1_edge = g1->adj[order[depth]][order[i]];
        int g2_edge = g2->adj[candidate][perm[i]];
        if (g1_edge != g2_edge) return 0;
    }
    return 1;
}


int backtrack(const Graph *g1, const Graph *g2,
              int perm[SIZE], int used[SIZE],
              int order[SIZE],
              int buckets[SIZE][SIZE], int bucket_size[SIZE],
              int depth) {

    /* base case: every G1 vertex has been successfully mapped */
    if (depth == g1->n) return 1;

    int v1 = order[depth];          /* current G1 vertex to map   */
    int d  = g1->degree[v1];        /* its degree                  */

    /* only consider G2 vertices with the same degree */
    for (int k = 0; k < bucket_size[d]; k++) {
        int candidate = buckets[d][k];

        if (used[candidate]) continue;

        if (is_compatible(g1, g2, perm, order, depth, candidate)) {
            perm[depth]       = candidate;   /* record the mapping  */
            used[candidate]   = 1;

            if (backtrack(g1, g2, perm, used, order,
                          buckets, bucket_size, depth + 1))
                return 1;                    /* solution found!     */

            used[candidate]   = 0;           /* undo (backtrack)    */
        }
    }

    return 0;   /* no valid candidate at this depth */
}