#include "Graph.h"
#include <fstream>

#define INITIAL_NODES_CAP 8
#define INITIAL_EDGES_CAP 16

Graph::Graph()
    : nNodes(0), nEdges(0),
      nodesCapacity(INITIAL_NODES_CAP), edgesCapacity(INITIAL_EDGES_CAP)
{
    nodes = new int[nodesCapacity];
    edges = new Edge[edgesCapacity];
}

Graph::~Graph() {
    delete[] nodes;
    delete[] edges;
}

void Graph::growNodes() {
    nodesCapacity *= 2;
    int* newNodes = new int[nodesCapacity];
    for (int i = 0; i < nNodes; ++i)
        newNodes[i] = nodes[i];
    delete[] nodes;
    nodes = newNodes;
}

void Graph::growEdges() {
    edgesCapacity *= 2;
    Edge* newEdges = new Edge[edgesCapacity];
    for (int i = 0; i < nEdges; ++i)
        newEdges[i] = edges[i];
    delete[] edges;
    edges = newEdges;
}

bool Graph::nodeExists(int node) const {
    for (int i = 0; i < nNodes; ++i)
        if (nodes[i] == node)
            return true;
    return false;
}

void Graph::addEdge(int u, int v, int w) {
    addNode(u);
    addNode(v);
    if (nEdges == edgesCapacity)
        growEdges();
    edges[nEdges].src = u;
    edges[nEdges].dest = v;
    edges[nEdges].weight = w;
    nEdges++;
}

void Graph::addNode(int x) {
    if (!nodeExists(x)) {
        if (nNodes == nodesCapacity) growNodes();
        nodes[nNodes++] = x;
    }
}


void Graph::loadFromFile(const char *filename) {
    std::ifstream file(filename);
    if (!file)
        throw "Error opening file";
    int u, v, w;
    nNodes = 0;
    nEdges = 0;
    while (file >> u >> v >> w)
        addEdge(u, v, w);
    file.close();
}

int Graph::numNodes() const { return nNodes; }
int Graph::numEdges() const { return nEdges; }
const Edge* Graph::getEdges() const { return edges; }

// Stesso merge e mergeSort che già usavi:
void Graph::merge(Edge arr[], int left, int mid, int right) {
    int n_l = mid - left + 1;
    int n_r = right - mid;

    Edge* L = new Edge[n_l];
    Edge* R = new Edge[n_r];
    for (int i = 0; i < n_l; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n_r; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n_l && j < n_r) {
        if (L[i].weight <= R[j].weight)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n_l)
        arr[k++] = L[i++];
    while (j < n_r)
        arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void Graph::mergeSort(Edge arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

Graph* Graph::Kruskal() {
    Graph* mst = new Graph();
    DisjointSet ds;
    ds.makeSet(nNodes);

    mergeSort(edges, 0, nEdges - 1);

    for (int i = 0; i < nEdges; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        // Serve trovare la posizione nell'array nodes[] per u e v
        int idxU = -1, idxV = -1;
        for (int j = 0; j < nNodes; ++j) {
            if (nodes[j] == u) idxU = j;
            if (nodes[j] == v) idxV = j;
        }
        if (ds.find(idxU) != ds.find(idxV)) {
            ds.unite(idxU, idxV);
            mst->addEdge(idxU, idxV, edges[i].weight);
        }
    }
    return mst;
}

void Graph::printGraph(const char* filename) const {
    std::ofstream file(filename);
    if (!file)
        throw "Error opening file";
    file << "graph G {\n";
    for (int i = 0; i < nEdges; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int w = edges[i].weight;
        file << "    " << u << " -- " << v << " [label=" << w << "];\n";
    }
    file << "}\n";
    file.close();
}