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
    // ogni elemento rappresenta l'indice del suo parent
    int parent[MAX_NODES];
    //Ogni elemento approssima (upperbound) l'altezza del suo sottoalbero
    int rank[MAX_NODES]; // si usa il rank per non calcolare l'altezza ogni volta
};

#endif // DISJOINTSET_H