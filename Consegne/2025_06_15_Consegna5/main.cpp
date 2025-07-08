#include <iostream>

#include "Data_Structure/Graph.h"

int main() {

    Graph g;

    g.loadFromFile("file_input/graph.txt");
    g.printGraph("./dot_output/graph.dot");

    Graph* g_kruskal = g.Kruskal();
    g_kruskal->printGraph("./dot_output/graph_kruskal.dot");
    delete g_kruskal;
    return 0;
}
