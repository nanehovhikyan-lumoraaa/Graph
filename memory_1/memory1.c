#include <stdio.h>
#include <math.h>
#include <string.h>

/* ─────────────────────────────────────────────
   Utility: format bytes into a human-readable
   string  (B / KB / MB / GB / TB / PB)
   ───────────────────────────────────────────── */
void format_bytes(double bytes, char *out) {
    const char *units[] = {"B", "KB", "MB", "GB", "TB", "PB"};
    int u = 0;
    double val = bytes;
    while (val >= 1024.0 && u < 5) { val /= 1024.0; u++; }
    sprintf(out, "%.4g %s", val, units[u]);
}

/* ─────────────────────────────────────────────
   How many bytes are needed to store one
   vertex index (for adjacency lists)?
   ───────────────────────────────────────────── */
int bytes_per_vertex(long long n) {
    if (n <= 256LL)          return 1;
    if (n <= 65536LL)        return 2;
    if (n <= 16777216LL)     return 3;
    if (n <= 4294967296LL)   return 4;
    return 8;
}

void separator(void) {
    printf("─────────────────────────────────────────────\n");
}

int main(void) {
    long long n;
    double    avg_deg;

    printf("╔═══════════════════════════════════════════╗\n");
    printf("║   Graph Memory Calculator                 ║\n");
    printf("╚═══════════════════════════════════════════╝\n\n");

    printf("Enter number of vertices (n): ");
    scanf("%lld", &n);

    printf("Enter average degree of vertices: ");
    scanf("%lf", &avg_deg);

    double m = ((double)n * avg_deg) / 2.0;

    printf("\n");
    separator();
    printf("INPUT SUMMARY\n");
    separator();
    printf("  Vertices (n)          = %lld\n", n);
    printf("  Average degree        = %.4g\n", avg_deg);
    printf("  Total edges (m)       = n x avg_deg / 2\n");
    printf("                        = %lld x %.4g / 2\n", n, avg_deg);
    printf("                        = %.0f\n\n", m);

    char buf1[64], buf2[64];

    /* (a) Adjacency Matrix */
    separator();
    printf("(a) ADJACENCY MATRIX  A(G)\n");
    separator();
    printf("  Structure : n x n binary matrix\n");
    printf("  Cell size : 1 bit\n");
    printf("  Formula   : n^2 bits\n\n");

    double adj_bits  = (double)n * (double)n;
    double adj_bytes = adj_bits / 8.0;

    printf("  Calculation:\n");
    printf("    bits  = n^2 = %lld^2 = %.0f bits\n", n, adj_bits);
    printf("    bytes = %.0f / 8 = %.0f bytes\n", adj_bits, adj_bytes);
    format_bytes(adj_bytes, buf1);
    printf("\n  MEMORY = %s\n\n", buf1);

    /* (b) Incidence Matrix */
    separator();
    printf("(b) INCIDENCE (EDGE) MATRIX  B(G)\n");
    separator();
    printf("  Structure : n x m binary matrix\n");
    printf("              (rows=vertices, columns=edges)\n");
    printf("  Cell size : 1 bit  (each cell is 0 or 1)\n");
    printf("  Formula   : n x m bits\n\n");

    double inc_bits  = (double)n * m;
    double inc_bytes = inc_bits / 8.0;

    printf("  Calculation:\n");
    printf("    bits  = n x m = %lld x %.0f = %.0f bits\n", n, m, inc_bits);
    printf("    bytes = %.0f / 8 = %.0f bytes\n", inc_bits, inc_bytes);
    format_bytes(inc_bytes, buf1);
    printf("\n  MEMORY = %s\n\n", buf1);

    /* (c) Adjacency Lists */
    separator();
    printf("(c) ADJACENCY LISTS\n");
    separator();

    int bpv = bytes_per_vertex(n);
    int bits_needed = (int)ceil(log2((double)n + 1));

    printf("  Structure : one linked list per vertex;\n");
    printf("              each entry stores a vertex index.\n\n");
    printf("  Vertex index range : 0 .. %lld\n", n - 1);
    printf("  Bits needed        : ceil(log2(%lld)) = %d bits\n", n, bits_needed);
    printf("  Bytes per entry    : %d byte(s)\n", bpv);
    printf("    (smallest integer size fitting %d bits)\n\n", bits_needed);

    double total_entries = 2.0 * m;
    double list_bytes    = total_entries * bpv;

    printf("  Total entries = 2m (sum of all degrees)\n");
    printf("                = 2 x %.0f = %.0f\n\n", m, total_entries);
    printf("  Calculation:\n");
    printf("    bytes = total_entries x bytes_per_entry\n");
    printf("          = %.0f x %d = %.0f bytes\n", total_entries, bpv, list_bytes);
    format_bytes(list_bytes, buf1);
    printf("\n  MEMORY = %s\n\n", buf1);

    /* Summary */
    separator();
    printf("SUMMARY\n");
    separator();
    printf("  %-28s %s\n", "Representation", "Memory");
    printf("  %-28s %s\n", "--------------", "------");

    format_bytes(adj_bytes,  buf1);
    printf("  %-28s %s\n", "(a) Adjacency Matrix",  buf1);
    format_bytes(inc_bytes,  buf1);
    printf("  %-28s %s\n", "(b) Incidence Matrix",  buf1);
    format_bytes(list_bytes, buf1);
    printf("  %-28s %s\n", "(c) Adjacency Lists",   buf1);

    printf("\n");
    separator();
    printf("NOTE: Adjacency lists are most efficient for\n");
    printf("sparse graphs (avg_degree << n).\n");
    printf("Incidence matrix is almost always the largest.\n");
    separator();

    return 0;
}