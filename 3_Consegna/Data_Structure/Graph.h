#include "Vertex.h"
#include <fstream>

#ifndef GRAPH
#define GRAPH

class Graph {
private:
    Vertex** edges;
    int numVertices;
    int capacity;

    void resize(int newCapacity);

public:
    Graph(int initialCapacity = 10);
    ~Graph();
    int addVertex(int value);
    void addEdge(int from, int to);
    void edgePrint(std::ofstream &buffer ,const Vertex& from , const Vertex& to);
    void graph_print(std::ofstream &buffer);
    void list_print(Vertex& list);
    int DFS(Vertex& root);
};

#endif