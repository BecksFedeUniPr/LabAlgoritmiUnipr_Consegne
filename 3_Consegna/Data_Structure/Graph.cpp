#include "Graph.h"
#include "Stack.h"
#include <iostream>

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
    Vertex* v = new Vertex(value);
    v->setNext(nullptr);
    edges[numVertices] = v;
    return numVertices++;
}

// Funzione per aggiungere un arco tra due nodi
void Graph::addEdge(int from, int to) {
    Vertex* vertex_from = this->edges[0];
    Vertex* vertex_to = this->edges[0];
    int counter = 0;

    while (vertex_from->getVal() != from && counter < this->numVertices)
    {
        vertex_from = this->edges[counter++]; 
    }

    counter = 0;

    while (vertex_to->getVal() != to && counter < this->numVertices)
    {
        vertex_to = this->edges[counter++]; 
    }

    Vertex* place_to_insert = vertex_from;

    while (place_to_insert->getNext() != nullptr)
    {
        place_to_insert = place_to_insert->getNext();
    }

    place_to_insert->setNext(new Vertex(*vertex_to));
}

void Graph::edgePrint(std::ofstream &buffer ,const Vertex& from , const Vertex& to){
    buffer << from.getVal() << " -> " << to.getVal() << ";" << std::endl;
}

// Funzione per stampare il grafo
void Graph::graph_print(std::ofstream &buffer) {
    for(int i = 0; i < numVertices; ++i) {
        this->edges[i]->VertexPrint(buffer);
        Vertex* vertex = this->edges[i];
        this->list_print(*vertex);

        Vertex* current = vertex->getNext();

        while(current != nullptr){
            this->edgePrint(buffer,*vertex,*current);
            current = current->getNext();
        }
    }
}


void Graph::list_print(Vertex& l){
    Vertex* current = &l;
    std::cout << "Lista print: " << std::endl;
    while (current != nullptr)
    {
        std::cout << current->getVal() << " ";
        current = current->getNext();
    }

    std::cout << std::endl;
}

/* int Graph::DFS(Vertex& root){


    Stack stack;

    root.setState(VISITED);

    stack.push(root.getVal());

    while (!stack.isEmpty())
    {
        
    }
    

    // STACK PER CALCOLARE IL NUMERO DEL CICLO E I NODI COINVOLTI , SE CE NE SONO PIU' DI UNO CON LA STESSA LUNGHEZZA ? 
}
 */