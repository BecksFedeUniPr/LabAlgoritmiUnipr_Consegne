#include <fstream>
#ifndef VERTEX_H
#define VERTEX_H


enum State {
    UNVISITED = 0,
    VISITED = 1,
    PROCESSED = 2
};

class Vertex {
    private:
    int val;          // Valore del vertice
    State state;      // Stato del vertice
    Vertex* next;     // Puntatore al prossimo vertice nella lista

public:
    // Definizione dell'enum per lo stato del vertice

    // Costruttore
    Vertex(int val) {
        this->val = val;
        this->state = UNVISITED; // Stato iniziale
        this->next = nullptr;
    }

    Vertex(const Vertex& other) {
        this->val = other.val;
        this->state = other.state;
        this->next = nullptr; // Non copiamo il puntatore `next` per evitare aliasing
    }

    // Getter per 'val'
    int getVal() const {
        return val;
    }

    // Setter per 'val'
    void setVal(int value) {
        val = value;
    }

    // Getter per 'state'
    State getState() const {
        return state;
    }

    // Setter per 'state'
    void setState(State newState) {
        state = newState;
    }

    // Getter per 'next'
    Vertex* getNext() {
        return this->next;
    }

    // Setter per 'next'
    void setNext(Vertex* nextVertex) {
        this->next = nextVertex;
    }

    void VertexPrint(std::ofstream &output_graph);

};

#endif // VERTEX_H