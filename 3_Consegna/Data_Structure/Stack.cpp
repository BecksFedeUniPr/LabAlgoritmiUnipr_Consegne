#include "Stack.h"
#include <exception>

Stack::Stack() {
    top = nullptr;
    size = 0;
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}


void Stack::push(const int value) {
    Vertex* newVertex = new Vertex(value);
    newVertex->setNext(top);
    top = newVertex;
    size++;
}

int Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack vuoto");
    }
    
    Vertex* temp = top;
    int value = temp->getVal();
    top = temp->getNext();
    delete temp;
    size--;
    if(size == 0)
        top = nullptr;
    return value;
}

bool Stack::isEmpty() const {
    return size == 0;
}

int Stack::getSize() const {
    return size;
}