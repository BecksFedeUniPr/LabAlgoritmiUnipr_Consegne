#include "Vertex.h"
#include <iostream>

class Graph {
private:
    Vertex** edges;
    int numVertices;
    int capacity;

    // Metodo per ridimensionare l'array di vertici
    void resize(int newCapacity) {
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

public:
    // Costruttore
    Graph(int initialCapacity = 10) {
        edges = new Vertex*[initialCapacity];
        for (int i = 0; i < initialCapacity; i++) {
            edges[i] = nullptr;
        }
        numVertices = 0;
        capacity = initialCapacity;
    }

    // Distruttore
    ~Graph() {
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

    // Funzione per aggiungere un nuovo nodo
    int addVertex(int value) {
        if (numVertices == capacity) {
            resize(capacity * 2); // Raddoppia la capacità se necessario
        }
        edges[numVertices] = new Vertex(value); // Crea un nuovo vertice
        return numVertices++;                   // Restituisce l'indice del nuovo vertice
    }

    // Funzione per aggiungere un arco tra due nodi
    void addEdge(int from, int to) {
        if (from >= 0 && from < numVertices && to >= 0 && to < numVertices) {
            Vertex* newVertex = new Vertex(to);
            newVertex->setNext(edges[from]); // Inserisce il nuovo vertice in testa alla lista di adiacenza
            edges[from] = newVertex;
        }
    }

    // Funzione per stampare il grafo
    void printGraph() {
        
    }
};