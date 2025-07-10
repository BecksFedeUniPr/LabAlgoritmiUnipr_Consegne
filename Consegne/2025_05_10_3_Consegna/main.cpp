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

    graph.addVertex(1);
    graph.addVertex(5);
    graph.addVertex(100);

    // Ciclo semplice
    graph.addVertex(10);
    graph.addVertex(2);
    graph.addVertex(12);
    graph.addVertex(50);

    graph.addEdge(2, 10); // arco 2 → 10
    graph.addEdge(10, 2); // arco 10 → 2 ⇒ ciclo tra 2 e 10
    graph.addEdge(2, 12); // arco 2 → 12
    graph.addEdge(50, 2); // arco 50 → 2 ⇒ altro ingresso in 2

    // Aggiunta di un ciclo più lungo
    graph.addVertex(20);
    graph.addVertex(30);
    graph.addVertex(40);
    graph.addEdge(20, 30);
    graph.addEdge(30, 40);
    graph.addEdge(40, 20); // ciclo: 20 → 30 → 40 → 20

    // Nodo senza archi
    graph.addVertex(999); // isolato

    // Arco unidirezionale
    graph.addEdge(5, 1); // 5 → 1 (nessun ritorno)

    graph.graph_print(output_graph);
    graph.findLongestCycle();

    /// preparo footer e chiudo file
    output_graph << "\n}" << std::endl;
    output_graph.close();
    std::cout << " File graph.dot scritto" << std::endl
              << "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf" << std::endl;
}