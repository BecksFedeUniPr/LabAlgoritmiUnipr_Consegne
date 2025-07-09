
#include "Data_Structure/Graph.h"

int main() {

    Graph g;
    // Lettura Grafo file
    g.loadFromFile("file_input/graph_input.txt");
    // Scrittura grafo su dot
    g.printGraph("./dot_output/graph.dot");

    // Appllico Kruskal su g e ritorno il suo MST
    Graph* MST_G = g.Kruskal();
    // Scrivo su dot MST
    MST_G->printGraph("./dot_output/graph_kruskal.dot");
    delete MST_G; // Dealloco MST
    return 0;
}
