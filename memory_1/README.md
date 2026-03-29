gcc -o graph_memory graph_memory.c -lm
./graph_memory


- n = 6×10⁵ vertices
- Average degree = 10², so total edges: m = (n × avg_degree) / 2 = (6×10⁵ × 10²) / 2 = 3×10⁷ edges

---

## a) Adjacency Matrix A(G)

The adjacency matrix is an n×n binary matrix where each cell = 1 bit.

Size = n² bits

= (6×10⁵)² = 3.6×10¹¹ bits

= 3.6×10¹¹ / 8 bytes = 4.5×10¹⁰ bytes = 45 GB

---

## b) Edge (Incidence) Matrix B(G)

The incidence matrix is an n×m binary matrix (rows = vertices, columns = edges), each cell = 1 bit.

Size = n × m bits

= 6×10⁵ × 3×10⁷ = 1.8×10¹³ bits

= 1.8×10¹³ / 8 bytes = 2.25×10¹² bytes = 2.25 TB

---

## c) Adjacency Lists

Each vertex stores a list of its neighbors. We need to store the vertex number as an integer.

Since n = 6×10⁵ < 2²⁰ = 1,048,576, we need at least 20 bits, so we round up to 3 bytes per vertex number.

The total number of entries across all lists = sum of all degrees = 2m = 6×10⁷

Size = 2m × 3 bytes

= 6×10⁷ × 3 = 1.8×10⁸ bytes = 180 MB

---

## Summary

| Representation | Memory |
|---|---|
| Adjacency Matrix | 45 GB |
| Incidence Matrix | 2.25 TB |
| Adjacency Lists | 180 MB |
