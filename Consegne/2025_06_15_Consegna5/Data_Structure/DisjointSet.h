#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include "./Dimensione.h"

class DisjointSet {
public:
    DisjointSet();
    void makeSet(int n);
    int find(int x);
    void unite(int x, int y);
private:
    int parent[MAX_NODES];
    int rank[MAX_NODES];
};

#endif // DISJOINTSET_H