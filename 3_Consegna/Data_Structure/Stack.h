#ifndef STACK_H
#define STACK_H

#include "Vertex.h"

class Stack {
private:
    Vertex* top; // Ultimo elemento
    Vertex* bottom; // Primo elemento
    int size;

public:
    Stack();
    ~Stack();

    void push(const int value);
    int pop();  // Restituisce il valore del vertice rimosso
    bool isEmpty() const;
    int getSize() const;
};

#endif // STACK_H