#include "./DisjointSet.h"

DisjointSet::DisjointSet() = default;

void DisjointSet::makeSet(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int DisjointSet::find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void DisjointSet::unite(int x, int y) {
    int rx = find(x); // Rappresemtante di x
    int ry = find(y); // Rappresentante di y
    if (rx == ry) return; // Sono la stessa classe di nodi
    // Viene fatta questa scelta per non aumentare velocemente l'altezza dell'albero
    if (rank[rx] < rank[ry]) { // Metto Rx sotto Ry
        parent[rx] = ry;
    } else if (rank[ry] < rank[rx]) { // Metto Rx sopra ry
        parent[ry] = rx;
    } else {
        parent[ry] = rx; // Stesso Rank scelgo indifferentemente
        rank[rx]++;
    }
}