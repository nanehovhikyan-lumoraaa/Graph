#include "graph_isomorphism.h"

static void read_graph(Graph *g, int id) {
    int n, u, v, edges;

    printf("=== Graph %d ===\n", id);

    printf("Enter number of vertices (max %d): ", SIZE);
    scanf("%d", &n);
    init_graph(g, n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge as two vertex indices (u v):\n");
    for (int i = 0; i < edges; i++) {
        printf("  Edge %d: ", i + 1);
        scanf("%d %d", &u, &v);
        u--;
        v--;
        add_edge(g, u, v);
    }

    printf("\n");
}


int main(void)
{
    Graph g1, g2;
    int   perm[SIZE];
    int   order[SIZE];

    printf("╔══════════════════════════════════╗\n");
    printf("║     Graph Isomorphism Checker    ║\n");
    printf("╚══════════════════════════════════╝\n\n");

    /* ── input ── */
    read_graph(&g1, 1);
    read_graph(&g2, 2);

    /* ── display both graphs ── */
    printf("=== Graph 1 ===\n");
    print_graph(&g1);
    printf("\n=== Graph 2 ===\n");
    print_graph(&g2);
    printf("\n");

    /* ── check isomorphism ── */
    sort_vertices_by_degree(&g1, order);   /* fill order[] for printing */

    if (are_isomorphic(&g1, &g2, perm)) {
        printf("✔  The graphs ARE isomorphic.\n\n");
        print_mapping(&g1, perm, order);
    } else {
        printf("✘  The graphs are NOT isomorphic.\n");
    }

    return 0;
}