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

void Graph::DFS(int node, bool* visited, bool* inStack, Stack& path, Stack& bestCycle, int& bestLen) {
    visited[node] = true;
    inStack[node] = true;
    path.push(node);

    Vertex* currentVertex = edges[node]; //Trovo nodo di indice node
    Vertex* neighbor = currentVertex->getNext(); // prendo il primo vicino

    // Visito tutti i vicini
    while (neighbor != nullptr) { // Non altri vicini
        int neighborVal = neighbor->getVal();
        int neighborIndex = -1;
        
        // Trova l'indice del nodo vicino
        for (int i = 0; i < numVertices; i++) {
            if (edges[i]->getVal() == neighborVal) {
                neighborIndex = i;
                break;
            }
        }

        if (!visited[neighborIndex]) {
            DFS(neighborIndex, visited, inStack, path, bestCycle, bestLen);
        } else if (inStack[neighborIndex]) { // Ciclo trovato
            Stack tempStack;

            while(!path.isEmpty()){
                int last_value = path.pop();
                tempStack.push(last_value);
                if(last_value == neighborVal) // Arrivo al vertice a cui è iniziato il ciclo
                    break;
            }

            // Se questo ciclo è più lungo del precedente, aggiornalo
            if (tempStack.getSize() > bestLen) {
                bestLen = tempStack.getSize();
                bestCycle.~Stack(); //Svuota il ciclo precedente
                while (!tempStack.isEmpty()) {
                    int value = tempStack.pop(); 
                    bestCycle.push(value); // Costruisco bestcycle
                    path.push(value); // Ricostruisco il path
                }
            }
        }
        neighbor = neighbor->getNext();
    }

    inStack[node] = false;
    path.pop();
}

void Graph::findLongestCycle() {
    bool* visited = new bool[numVertices]();
    bool* inStack = new bool[numVertices]();
    Stack path;
    Stack bestCycle;
    int bestLen = 0;

    // Visita ogni componente connessa del grafo
    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            DFS(i, visited, inStack, path, bestCycle, bestLen);
        }
    }

    // Stampa i risultati
    if (bestLen > 0) {
        std::cout << "Lunghezza del ciclo più lungo: " << bestLen << std::endl;
        std::cout << "Nodi del ciclo: ";
        
        // Crea uno stack temporaneo per invertire l'ordine
        Stack tempStack;
        while (!bestCycle.isEmpty()) {
            tempStack.push(bestCycle.pop());
        }
        
        // Stampa i nodi nel corretto ordine
        while (!tempStack.isEmpty()) {
            int nodeIndex = tempStack.pop();
            std::cout << edges[nodeIndex]->getVal() << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Nessun ciclo trovato nel grafo." << std::endl;
    }

    // Pulizia della memoria
    delete[] visited;
    delete[] inStack;
}