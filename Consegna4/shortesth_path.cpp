#include <iostream>
#include <math.h>
#include <time.h>

#include "MinHeap.h"

using namespace std;

#define INFTY 1000000

//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

typedef struct node {
    int val;
    float w; // Weight
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
    new_node->val = elem;
    new_node->w = w;
    new_node->next = l->head;
    l->head = new_node;
}

void list_print(list_t *l) {
    node_t *current = l->head;
    while (current != NULL) {
        printf("%d w:%f, ", current->val, current->w);
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
    MinHeap heap;
    V_dist[n] = 0;

    for (int i = 0; i < n_nodi; i++) {
        heap.insert(i,V_dist[i]);
    }

    while (!heap.isEmpty()) {
        HeapElem best_elem = heap.extractMin();
        int best_idx = best_elem.idx;
        V_visitato[best_idx] = 1;

        node_t *elem = E[best_idx]->head;
        while (elem != NULL) {
            // Scorro tutti i vicini
            int v = elem->val;
            float alt = V_dist[best_idx] + elem->w;
            if (alt < V_dist[v]) {
                V_dist[v] = alt;
                V_prev[v] = best_idx;
                heap.decreaseKey(v, alt);
            }
            elem = elem->next;
        }
    }
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
