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

/* Same as format_bytes but also prints each /1024 step */
void format_bytes_verbose(double bytes, char *out) {
    const char *units[] = {"B", "KB", "MB", "GB", "TB", "PB"};
    int u = 0;
    double val = bytes;
    printf("    Converting to human-readable:\n");
    printf("      %.0f B\n", val);
    while (val >= 1024.0 && u < 5) {
        val /= 1024.0;
        u++;
        printf("      / 1024 = %.4g %s\n", val, units[u]);
    }
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

/* ═══════════════════════════════════════════════
   MODE 1: Given n and avg_deg → find memory
   ═══════════════════════════════════════════════ */
void mode_memory(void) {
    long long n;
    double avg_deg;

    printf("Enter number of vertices (n): ");
    scanf("%lld", &n);
    printf("Enter average degree of vertices: ");
    scanf("%lf", &avg_deg);

    double m = ((double)n * avg_deg) / 2.0;

    printf("\n");
    separator();
    printf("INPUT SUMMARY\n");
    separator();
    printf("  Vertices (n)    = %lld\n", n);
    printf("  Average degree  = %.0f\n", avg_deg);
    printf("  Total edges (m) = n x avg_deg / 2\n");
    printf("                  = %lld x %.0f / 2\n", n, avg_deg);
    printf("                  = %.0f\n\n", m);

    char buf1[64];

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
    format_bytes_verbose(adj_bytes, buf1);
    printf("\n  MEMORY = %s\n\n", buf1);

    /* (b) Incidence Matrix */
    separator();
    printf("(b) INCIDENCE (EDGE) MATRIX  B(G)\n");
    separator();
    printf("  Structure : n x m binary matrix\n");
    printf("              (rows=vertices, columns=edges)\n");
    printf("  Cell size : 1 bit\n");
    printf("  Formula   : n x m bits\n\n");

    double inc_bits  = (double)n * m;
    double inc_bytes = inc_bits / 8.0;

    printf("  Calculation:\n");
    printf("    bits  = n x m = %lld x %.0f = %.0f bits\n", n, m, inc_bits);
    printf("    bytes = %.0f / 8 = %.0f bytes\n", inc_bits, inc_bytes);
    format_bytes_verbose(inc_bytes, buf1);
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
    format_bytes_verbose(list_bytes, buf1);
    printf("\n  MEMORY = %s\n\n", buf1);

    /* Summary */
    separator();
    printf("SUMMARY\n");
    separator();
    printf("  %-28s %s\n", "Representation", "Memory");
    printf("  %-28s %s\n", "--------------", "------");
    format_bytes(adj_bytes,  buf1); printf("  %-28s %s\n", "(a) Adjacency Matrix",  buf1);
    format_bytes(inc_bytes,  buf1); printf("  %-28s %s\n", "(b) Incidence Matrix",  buf1);
    format_bytes(list_bytes, buf1); printf("  %-28s %s\n", "(c) Adjacency Lists",   buf1);
    printf("\n");
    separator();
    printf("NOTE: Adjacency lists are most efficient for\n");
    printf("sparse graphs (avg_degree << n).\n");
    separator();
}

/* ═══════════════════════════════════════════════
   MODE 2: Given memory and avg_deg → find max n
   ═══════════════════════════════════════════════ */
void mode_max_vertices(void) {
    double mem_bytes;
    double avg_deg;
    int    bpv;

    printf("Enter available memory (in bytes): ");
    scanf("%lf", &mem_bytes);
    printf("Enter average degree of vertices: ");
    scanf("%lf", &avg_deg);
    printf("Enter bytes used per vertex number in lists (e.g. 4): ");
    scanf("%d", &bpv);

    double mem_bits = mem_bytes * 8.0;

    printf("\n");
    separator();
    printf("INPUT SUMMARY\n");
    separator();
    printf("  Available memory    = %.0f bytes\n", mem_bytes);
    printf("  Average degree      = %.0f\n", avg_deg);
    printf("  Bytes per vertex no = %d\n\n", bpv);

    /* (a) Adjacency Matrix
       n^2 bits <= mem_bits
       n <= sqrt(mem_bits)                        */
    separator();
    printf("(a) ADJACENCY MATRIX  A(G)\n");
    separator();
    printf("  Formula   : n^2 bits <= memory_in_bits\n\n");
    printf("  Derivation:\n");
    printf("    n^2 <= mem_bytes x 8\n");
    printf("    n^2 <= %.0f x 8\n", mem_bytes);
    printf("    n^2 <= %.0f\n", mem_bits);
    printf("    n   <= sqrt(%.0f)\n", mem_bits);
    double n_adj = floor(sqrt(mem_bits));
    printf("    n   <= %.0f\n\n", n_adj);
    printf("  MAX VERTICES = %.0f\n\n", n_adj);

    /* (b) Incidence Matrix
       n x m bits <= mem_bits,  m = n*avg_deg/2
       n * (n*avg_deg/2) <= mem_bits
       n^2 * avg_deg/2   <= mem_bits
       n^2               <= mem_bits * 2 / avg_deg
       n                 <= sqrt(mem_bits * 2 / avg_deg)  */
    separator();
    printf("(b) INCIDENCE (EDGE) MATRIX  B(G)\n");
    separator();
    printf("  Formula   : n x m bits <= memory_in_bits\n");
    printf("  Since m = n x avg_deg / 2:\n\n");
    printf("  Derivation:\n");
    printf("    n x (n x avg_deg / 2) <= mem_bytes x 8\n");
    printf("    n^2 x %.0f / 2        <= %.0f\n", avg_deg, mem_bits);
    printf("    n^2 x %.0f            <= %.0f\n", avg_deg / 2.0, mem_bits);
    printf("    n^2                   <= %.0f / %.0f\n", mem_bits, avg_deg / 2.0);
    double rhs_b = mem_bits / (avg_deg / 2.0);
    printf("    n^2                   <= %.0f\n", rhs_b);
    printf("    n                     <= sqrt(%.0f)\n", rhs_b);
    double n_inc = floor(sqrt(rhs_b));
    printf("    n                     <= %.0f\n\n", n_inc);
    printf("  MAX VERTICES = %.0f\n\n", n_inc);

    /* (c) Adjacency Lists
       2m x bpv <= mem_bytes,  m = n*avg_deg/2
       2 x (n*avg_deg/2) x bpv <= mem_bytes
       n x avg_deg x bpv       <= mem_bytes
       n                       <= mem_bytes / (avg_deg x bpv)  */
    separator();
    printf("(c) ADJACENCY LISTS\n");
    separator();
    printf("  Formula   : 2m x bytes_per_entry <= memory_in_bytes\n");
    printf("  Since m = n x avg_deg / 2:\n\n");
    printf("  Derivation:\n");
    printf("    2 x (n x avg_deg / 2) x %d <= %.0f\n", bpv, mem_bytes);
    printf("    n x avg_deg x %d           <= %.0f\n", bpv, mem_bytes);
    printf("    n x %.0f x %d              <= %.0f\n", avg_deg, bpv, mem_bytes);
    double coeff_c = avg_deg * bpv;
    printf("    n x %.0f                   <= %.0f\n", coeff_c, mem_bytes);
    printf("    n                          <= %.0f / %.0f\n", mem_bytes, coeff_c);
    double n_list = floor(mem_bytes / coeff_c);
    printf("    n                          <= %.0f\n\n", n_list);
    printf("  MAX VERTICES = %.0f\n\n", n_list);

    /* Summary */
    separator();
    printf("SUMMARY\n");
    separator();
    printf("  %-28s %s\n", "Representation", "Max vertices");
    printf("  %-28s %s\n", "--------------", "------------");
    printf("  %-28s %.0f\n", "(a) Adjacency Matrix",  n_adj);
    printf("  %-28s %.0f\n", "(b) Incidence Matrix",  n_inc);
    printf("  %-28s %.0f\n", "(c) Adjacency Lists",   n_list);
    printf("\n");
    separator();
    printf("NOTE: Adjacency lists allow the most vertices\n");
    printf("for the same memory budget.\n");
    separator();
}

/* ═══════════════════════════════════════════════
   MAIN: pick mode
   ═══════════════════════════════════════════════ */
int main(void) {
    int mode;

    printf("╔═══════════════════════════════════════════╗\n");
    printf("║   Graph Memory Calculator                 ║\n");
    printf("╚═══════════════════════════════════════════╝\n\n");
    printf("Select mode:\n");
    printf("  1 - Given n and avg_degree  → calculate memory needed\n");
    printf("  2 - Given memory and avg_degree → find max vertices\n\n");
    printf("Choice: ");
    scanf("%d", &mode);
    printf("\n");

    if (mode == 1)      mode_memory();
    else if (mode == 2) mode_max_vertices();
    else                printf("Invalid choice.\n");

    return 0;
}