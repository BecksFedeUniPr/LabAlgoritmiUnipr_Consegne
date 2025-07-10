#include "Vertex.h"
#include "Stack.h"
#include <fstream>

#ifndef GRAPH
#define GRAPH

class Graph {
private:
    Vertex** edges;
    int numVertices;
    int capacity;

    void resize(int newCapacity);
    void DFS(int node, bool* visited, bool* inStack, Stack& path, Stack& bestCycle, int& bestLen);

public:
    Graph(int initialCapacity = 10);
    ~Graph();
    int addVertex(int value);
    void addEdge(int from, int to);
    void edgePrint(std::ofstream &buffer ,const Vertex& from , const Vertex& to);
    void graph_print(std::ofstream &buffer);
    void list_print(Vertex& list);
    void findLongestCycle();
};

#endif