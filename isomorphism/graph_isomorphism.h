#include <stdio.h>          // for printf() and scanf()
#include <string.h>         // for memset()
#include <stdlib.h>         // for qsort()

#ifndef GRAPH_ISOMORPHISM_H
# define GRAPH_ISOMORPHISM_H

# define SIZE 15

// Data Structure
typedef struct {
    int n;               // number of vertices
    int adj[SIZE][SIZE]; // adjacency matrix
    int degree[SIZE];    // degree of each vertex
} Graph;

// Graph Construction
void init_graph(Graph *g, int n);
// Initializes a graph with n vertices, zeroing the adjacency matrix and degrees.

void add_edge(Graph *g, int u, int v);
// Adds an undirected edge between vertices u and v, and updates their degrees.

void print_graph(const Graph *g);
// Prints the adjacency matrix and degree sequence of the graph.




// Rejection Filters
int same_vertex_count(const Graph *g1, const Graph *g2);
// Returns 1 if both graphs have the same number of vertices, 0 otherwise.

int same_edge_count(const Graph *g1, const Graph *g2);
// Returns 1 if both graphs have the same number of edges, 0 otherwise.

int same_degree_sequence(const Graph *g1, const Graph *g2);
// Returns 1 if both graphs have the same sorted degree sequence, 0 otherwise.

int passes_filters(const Graph *g1, const Graph *g2);
// Runs all rejection filters in order. Returns 0 as soon as one fails, 1 if all pass.




// Preprocessing
void sort_vertices_by_degree(const Graph *g, int order[SIZE]);
// Fills order[] with G1 vertex indices sorted by degree (descending).
// Used to determine the mapping order during backtracking.

void build_candidate_buckets(const Graph *g, int buckets[SIZE][SIZE], int bucket_size[SIZE]);
// Groups G2 vertices by degree into buckets[d][] with counts in bucket_size[d].
// Used to quickly look up valid candidates for a given degree.





// Backtracking Core
int is_compatible(const Graph *g1, const Graph *g2,
                  int perm[SIZE], int order[SIZE],
                  int depth, int candidate);
// Checks if mapping G1 vertex order[depth] to G2 vertex `candidate` is
// consistent with all edges to already-mapped vertices.

int backtrack(const Graph *g1, const Graph *g2,
              int perm[SIZE], int used[SIZE],
              int order[SIZE],
              int buckets[SIZE][SIZE], int bucket_size[SIZE],
              int depth);
// Recursively tries to build a valid isomorphism mapping using backtracking.
// Returns 1 if a valid mapping is found, 0 otherwise.





// Main Entry Point
int are_isomorphic(const Graph *g1, const Graph *g2, int perm[SIZE]);
// Top-level function. Runs filters, sets up preprocessing structures,
// launches backtracking, and returns 1 if isomorphic (with perm[] filled),
// or 0 if not.

void print_mapping(const Graph *g1, int perm[SIZE], int order[SIZE]);






//main
//static void read_graph(Graph *g, int id);

#endif