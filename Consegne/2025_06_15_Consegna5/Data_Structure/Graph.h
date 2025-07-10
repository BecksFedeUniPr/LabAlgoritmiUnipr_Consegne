#ifndef GRAPH_H
#define GRAPH_H

#include "DisjointSet.h"

// Struttura per rappresentare un arco
struct Edge {
    int src;
    int dest;
    int weight;
};

class Graph {
public:
    Graph();
    ~Graph();

    void loadFromFile(const char *filename);
    int numNodes() const;
    int numEdges() const;
    const Edge* getEdges() const;
    void addEdge(int u, int v, int w);
    void addNode(int x);
    void printGraph(const char *filename) const;
    Graph* Kruskal();

private:
    int nNodes;
    int nEdges;
    int nodesCapacity;
    int edgesCapacity;
    int* nodes;    // array dinamico dei nodi
    Edge* edges;   // array dinamico degli archi

    void growNodes();
    void growEdges();
    bool nodeExists(int node) const;

    void merge(Edge arr[], int left, int mid, int right);
    void mergeSort(Edge arr[], int left, int right);
};

#endif // GRAPH_H