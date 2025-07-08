#ifndef GRAPH_H
#define GRAPH_H

#include "DisjointSet.h"
#include "Dimensione.h"

struct Edge {
    int src;
    int dest;
    int weight;
};

class Graph {
public:
    Graph();
    void loadFromFile(const char *filename);
    int numNodes() const;
    int numEdges() const;
    const Edge* getEdges() const;
    void addNode();
    void addEdge(int u, int v, int w);

    void printGraph(const char *filename) const;

    Graph* Kruskal();
private:
    int nNodes;
    int nEdges;
    Edge edges[MAX_EDGES];

    void merge(Edge arr[], int left, int mid, int right);
    void mergeSort(Edge arr[], int left, int right);

};

#endif // GRAPH_H