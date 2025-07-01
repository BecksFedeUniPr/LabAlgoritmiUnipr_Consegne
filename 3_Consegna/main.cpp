#include "./Data_Structure/Graph.h"
#include <iostream>


int main()
{
    std::ofstream output_graph;
    Graph graph;

    output_graph.open("graph.dot");
    /// preparo header
    output_graph << "digraph g" << std::endl;
    output_graph << "{ " << std::endl;

    graph.addVertex(10);
    graph.addVertex(2);
    graph.addVertex(12);
    graph.addVertex(50);

    graph.addEdge(2, 10);
    graph.addEdge(10, 2);
    graph.addEdge(2,12);
    graph.addEdge(50,2);

    graph.graph_print(output_graph);

    graph.findLongestCycle();

    /// preparo footer e chiudo file
    output_graph << "\n}" << std::endl;
    output_graph.close();
    std::cout << " File graph.dot scritto" << std::endl << "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf" << std::endl;
}