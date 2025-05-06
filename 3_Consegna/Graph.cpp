#include "Graph.h"

// Costruttore
Graph::Graph(int initialCapacity) {
    edges = new Vertex*[initialCapacity];
    for (int i = 0; i < initialCapacity; i++) {
        edges[i] = nullptr;
    }
    numVertices = 0;
    capacity = initialCapacity;
}

// Distruttore
Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        Vertex* current = edges[i];
        while (current != nullptr) {
            Vertex* temp = current;
            current = current->getNext();
            delete temp;
        }
    }
    delete[] edges;
}

// Metodo per ridimensionare l'array di vertici
void Graph::resize(int newCapacity) {
    Vertex** newEdges = new Vertex*[newCapacity];
    for (int i = 0; i < numVertices; i++) {
        newEdges[i] = edges[i];
    }
    for (int i = numVertices; i < newCapacity; i++) {
        newEdges[i] = nullptr;
    }
    delete[] edges;
    edges = newEdges;
    capacity = newCapacity;
}

// Funzione per aggiungere un nuovo nodo
int Graph::addVertex(int value) {
    if (numVertices == capacity) {
        resize(capacity * 2);
    }
    edges[numVertices] = new Vertex(value);
    return numVertices++;
}

// Funzione per aggiungere un arco tra due nodi
void Graph::addEdge(int from, int to) {
    if (from >= 0 && from < numVertices && to >= 0 && to < numVertices) {
        Vertex* newVertex = new Vertex(to);
        newVertex->setNext(edges[from]);
        edges[from] = newVertex;
    }
}

// Funzione per stampare il grafo
void Graph::graph_print(std::ofstream &buffer) {
    for (int i = 0; i < numVertices; i++) {
        this->edges[i]->VertexPrint(buffer, i + 1);
    }
}