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
    Node* newNode = new Node{value, top};
    top = newNode;
    size++;
}

int Stack::pop() {
    if (isEmpty()) {
        //TODO
    }

    Node* temp = top;
    int value = temp->value;
    top = top->next;
    delete temp;
    size--;
    return value;
}

bool Stack::isEmpty() const {
    return size == 0;
}

int Stack::getSize() const {
    return size;
}