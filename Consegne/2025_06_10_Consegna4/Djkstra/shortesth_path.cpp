#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#define INFTY 1000000

// ----- HEAP STRUTTURA E FUNZIONI -----

typedef struct {
    int idx;
    float distance;
} HeapElem;

typedef struct {
    HeapElem* data;
    int* pos;     // posizioni correnti degli indici nell'heap
    int size, capacity;
} MinHeap;

MinHeap* heap_create(int max_nodes) {
    MinHeap* h = new MinHeap;
    h->data = new HeapElem[max_nodes];
    h->pos = new int[max_nodes];
    h->capacity = max_nodes;
    h->size = 0;
    for (int i = 0; i < max_nodes; ++i)
        h->pos[i] = -1;
    return h;
}

void heap_destroy(MinHeap* h) {
    delete[] h->data;
    delete[] h->pos;
    delete h;
}

void heap_swap(MinHeap* h, int a, int b) {
    HeapElem tmp = h->data[a];
    h->data[a] = h->data[b];
    h->data[b] = tmp;
    h->pos[h->data[a].idx] = a;
    h->pos[h->data[b].idx] = b;
}

int heap_parent(int i) { return (i - 1) / 2; }
int heap_left(int i) { return 2 * i + 1; }
int heap_right(int i) { return 2 * i + 2; }

void heapify_up(MinHeap* h, int i) {
    while (i > 0 && h->data[heap_parent(i)].distance > h->data[i].distance) {
        heap_swap(h, i, heap_parent(i));
        i = heap_parent(i);
    }
}
void heapify_down(MinHeap* h, int i) {
    int min = i, l = heap_left(i), r = heap_right(i);
    if (l < h->size && h->data[l].distance < h->data[min].distance) min = l;
    if (r < h->size && h->data[r].distance < h->data[min].distance) min = r;
    if (min != i) {
        heap_swap(h, i, min);
        heapify_down(h, min);
    }
}

void heap_insert(MinHeap* h, int idx, float distance) {
    h->data[h->size] = { idx, distance };
    h->pos[idx] = h->size;
    heapify_up(h, h->size);
    h->size++;
}

HeapElem heap_extractMin(MinHeap* h) {
    if (h->size == 0) throw "Heap vuoto";
    HeapElem minElem = h->data[0];
    h->pos[minElem.idx] = -1;
    h->data[0] = h->data[h->size - 1];
    h->pos[h->data[0].idx] = 0;
    h->size--;
    heapify_down(h, 0);
    return minElem;
}

void heap_decreaseKey(MinHeap* h, int idx, float new_dist) {
    int i = h->pos[idx];
    if (i == -1) return;
    if (h->data[i].distance <= new_dist) return;
    h->data[i].distance = new_dist;
    heapify_up(h, i);
}

bool heap_isEmpty(MinHeap* h) {
    return h->size == 0;
}
// ----- FINE HEAP -----

//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

typedef struct node {
    int idx;   // indice nodo
    float w;
    struct node *next;
} node_t;

typedef struct list {
    node *head;
} list_t;

list_t *list_new(void) {
    list_t *l = new list;
    l->head = NULL;
    return l;
}

void list_insert_front(list_t *l, int elem, float w) {
    node_t *new_node = new node_t;
    new_node->idx = elem;
    new_node->w = w;
    new_node->next = l->head;
    l->head = new_node;
}

void list_print(list_t *l) {
    node_t *current = l->head;
    while (current != NULL) {
        printf("%d w:%f, ", current->idx, current->w);
        current = current->next;
    }
    printf("\n");
}

//////////////////////////////////////////////////
/// Definizione della struttura dati grafo
//////////////////////////////////////////////////

int *V; // Vertici
int *V_visitato; // Vertici con il flag_visitato
int *V_prev; // Per ogni vertice il suo precedessore
float *V_dist;
list_t **E; // lista di adiacenza
int n_nodi;

//////////////////////////////////////////////////
/// Algoritmo di Dijkstra (shortest path)
//////////////////////////////////////////////////

void shortest_path(int n) {
    MinHeap* heap = heap_create(n_nodi);
    V_dist[n] = 0;
    for (int i = 0; i < n_nodi; i++) {
        heap_insert(heap, i, V_dist[i]);
    }

    while (!heap_isEmpty(heap)) {
        HeapElem best_elem = heap_extractMin(heap);
        int best_idx = best_elem.idx;
        V_visitato[best_idx] = 1;

        node_t *elem = E[best_idx]->head;
        while (elem != NULL) {
            int v = elem->idx;
            float alt = V_dist[best_idx] + elem->w;
            if (alt < V_dist[v]) {
                V_dist[v] = alt;
                V_prev[v] = best_idx;
                heap_decreaseKey(heap, v, alt);
            }
            elem = elem->next;
        }
    }
    heap_destroy(heap);
}

//////////////////////////////////////////////////
/// Funzione principale
//////////////////////////////////////////////////

int main() {
    srand((unsigned) time(NULL));

    n_nodi = 10;
    V = new int[n_nodi];
    V_visitato = new int[n_nodi];
    V_prev = new int[n_nodi];
    V_dist = new float[n_nodi];
    E = new list_t *[n_nodi];

    for (int i = 0; i < n_nodi; i++) {
        V[i] = 2 * i;
        V_visitato[i] = 0; // Non Visitato
        V_prev[i] = -1; // Nessuno prima
        V_dist[i] = INFTY;
        E[i] = list_new();
    }

    int arrivo = n_nodi - 1;
    int w_max = 100;

    for (int i = 0; i < n_nodi - 1; i++) {
        list_insert_front(E[i], arrivo, w_max - 2 * i);
        if (i > 0)
            list_insert_front(E[i - 1], i, 1);
    }

    for (int i = 0; i < n_nodi; i++) {
        printf("Nodo %d (valore %d): ", i, V[i]);
        list_print(E[i]);
    }

    shortest_path(0);

    printf("\nDistanze finali dalla sorgente:\n");
    for (int i = 0; i < n_nodi; i++) {
        printf("Nodo %d: distanza = %f, predecessore = %d\n", i, V_dist[i], V_prev[i]);
    }

    return 0;
}