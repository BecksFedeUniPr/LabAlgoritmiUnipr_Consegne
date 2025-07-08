#include "Graph.h"
#include <fstream>

Graph::Graph() : nNodes(0), nEdges(0) {}

void Graph::loadFromFile(const char *filename) {
    std::ifstream file(filename);
    if (!file)
        throw "Error opening file";

    int u, v, w;
    nNodes = 0;
    nEdges = 0;
    while (file >> u >> v >> w) {
        if (nEdges >= MAX_EDGES)
            throw "Too many edges";
        edges[nEdges].src = u;
        edges[nEdges].dest = v;
        edges[nEdges].weight = w;
        nEdges++;
        if (u > nNodes) nNodes = u + 1; // Assunzione che i nodi siano di indice da 0 a N-1
        if (v > nNodes) nNodes = v + 1; // Assunzione che i nodi siano di indice da 0 a N-1
    }
    file.close();
}

void Graph::addNode() {
    nNodes++;
}

void Graph::merge(Edge arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Array temporanei
    Edge L[MAX_EDGES], R[MAX_EDGES];
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    // Merge degli array temporanei
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].weight <= R[j].weight) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge sort ricorsivo
void Graph::mergeSort(Edge arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Aggiunge un arco da u a v con peso w
void Graph::addEdge(int u, int v, int w) {
    if (nEdges < MAX_EDGES) {
        edges[nEdges].src = u;
        edges[nEdges].dest = v;
        edges[nEdges].weight = w;
        nEdges++;
    }
}

Graph* Graph::Kruskal() {
    Graph* g = new Graph();
    DisjointSet ds;
    for (int i = 0 ; i < nNodes ; ++i)
        ds.makeSet(nNodes);
    this->mergeSort(edges, 0, nEdges - 1);
    for (int i = 0 ; i < nEdges ; ++i) {
        if (ds.find(edges[i].src) != ds.find(edges[i].dest)) {
            ds.unite(edges[i].src, edges[i].dest);
            g->addEdge(edges[i].src, edges[i].dest, edges[i].weight);
        }
    }
    return g;
}

void Graph::printGraph(const char* filename) const {
    std::ofstream file(filename);
    if (!file) {
        throw "Error opening file";
    }

    file << "graph G {\n";
    for (int i = 0; i < nEdges; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;
        // Per evitare duplicati negli archi non orientati (0-1 e 1-0)
        if (u <= v) {
            file << "    " << u << " -- " << v << " [label=" << w << "];\n";
        }
    }
    file << "}\n";
    file.close();
}


int Graph::numNodes() const { return nNodes; }
int Graph::numEdges() const { return nEdges; }
const Edge* Graph::getEdges() const { return edges; }