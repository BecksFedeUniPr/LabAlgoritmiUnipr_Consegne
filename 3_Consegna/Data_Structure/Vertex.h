#ifndef VERTEX_H
#define VERTEX_H
#include <fstream>

enum State {
    UNVISITED = 0,
    VISITED = 1,
    PROCESSED = 2
};

class Vertex {
private:
    int val;
    State state;
    Vertex* next;

public:
    Vertex(int val) {
        this->val = val;
        this->state = UNVISITED;
        this->next = nullptr;
    }

    Vertex(const Vertex& other) {
        this->val = other.val;
        this->state = other.state;
        this->next = nullptr;
    }

    int getVal() const {
        return val;
    }

    void setVal(int value) {
        val = value;
    }

    State getState() const {
        return state;
    }

    void setState(State newState) {
        state = newState;
    }

    Vertex* getNext() {
        return this->next;
    }

    void setNext(Vertex* nextVertex) {
        this->next = nextVertex;
    }

    void VertexPrint(std::ofstream &output_graph);
};

#endif