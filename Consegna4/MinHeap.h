#ifndef MINHEAP_H
#define MINHEAP_H

struct HeapElem {
    int idx;        // Indice nell'array di shortesh path (nodo)
    float distance; // Priorità del nodo
};

class MinHeap {
private:
    HeapElem* heap;
    int* pos;          // pos[v] = indice nell'array heap per nodo v
    int capacity;
    int size;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i)   const { return 2 * i + 1; }
    int right(int i)  const { return 2 * i + 2; }
    void swap(int a, int b);
    void heapify_up(int i);
    void heapify_down(int i);
    void resize();

public:
    MinHeap(int max_nodes = 16);
    ~MinHeap();

    void insert(int idx, float distance);
    HeapElem extractMin();
    bool isEmpty() const { return size == 0; }
    void decreaseKey(int idx, float new_dist);
};

#endif // MINHEAP_H