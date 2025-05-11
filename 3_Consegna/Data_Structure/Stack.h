#ifndef STACK_H
#define STACK_H


class Stack {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* top;
    int size;

public:
    Stack();
    ~Stack();

    void push(const int value);
    int pop();
    bool isEmpty() const;
    int getSize() const;
};

#endif // STACK_H