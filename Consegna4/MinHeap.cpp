#include "MinHeap.h"
#include <stdexcept>
#include <cstring>

MinHeap::MinHeap(int max_nodes): capacity(max_nodes), size(0) {
    heap = new HeapElem[capacity];
    pos = new int[capacity];
    for (int i = 0; i < capacity; ++i) pos[i] = -1; // -1 significa non presente nella heap
}

MinHeap::~MinHeap() {
    delete[] heap;
    delete[] pos;
}

void MinHeap::swap(int a, int b) {
    HeapElem tmp = heap[a];
    heap[a] = heap[b];
    heap[b] = tmp;
    pos[heap[a].idx] = a;
    pos[heap[b].idx] = b;
}

void MinHeap::heapify_up(int i) {
    while (i > 0 && heap[parent(i)].distance > heap[i].distance) {
        swap(i, parent(i));
        i = parent(i);
    }
}

void MinHeap::heapify_down(int i) {
    int min = i;
    int l = left(i);
    int r = right(i);
    if (l < size && heap[l].distance < heap[min].distance) min = l;
    if (r < size && heap[r].distance < heap[min].distance) min = r;
    if (min != i) {
        swap(i, min);
        heapify_down(min);
    }
}

void MinHeap::resize() {
    int old_capacity = capacity;
    capacity *= 2;
    HeapElem* newHeap = new HeapElem[capacity];
    int* newPos = new int[capacity];

    for (int i = 0; i < old_capacity; ++i) newPos[i] = pos[i];
    for (int i = old_capacity; i < capacity; ++i) newPos[i] = -1;
    for (int i = 0; i < size; ++i) newHeap[i] = heap[i];
    delete[] heap;
    delete[] pos;
    heap = newHeap;
    pos = newPos;
}

void MinHeap::insert(int idx, float distance) {
    if (size == capacity) resize();
    heap[size] = { idx, distance };
    pos[idx] = size;
    heapify_up(size);
    size++;
}

HeapElem MinHeap::extractMin() {
    if (size == 0) throw std::runtime_error("Heap vuoto");
    HeapElem minElem = heap[0];
    pos[minElem.idx] = -1;
    heap[0] = heap[size - 1];
    pos[heap[0].idx] = 0;
    size--;
    heapify_down(0);
    return minElem;
}

void MinHeap::decreaseKey(int idx, float new_dist) {
    int i = pos[idx];
    if (i == -1) return; // non presente nella heap
    if (heap[i].distance <= new_dist) return; // già migliore
    heap[i].distance = new_dist;
    heapify_up(i);
}