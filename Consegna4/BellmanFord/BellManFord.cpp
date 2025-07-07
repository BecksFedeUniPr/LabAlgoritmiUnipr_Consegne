#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

using namespace std;

#define INFTY 1000000


int max_dim = 0;
int ntests = 1;
int ndiv = 1;
int details = 0;
int graph = 0;

/// file di output per grafo
ofstream output_graph;
int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step
int ct_visit = 0; // contatore durante visita

//////////////////////////////////////////////////
/// Definizione della struttura dati lista
//////////////////////////////////////////////////

/// struct per il nodo della lista
typedef struct node {
    int idx; /// prossimo nodo (era: val)
    float w;
    node *next;
} node_t;

/// struct per la lista
typedef struct list {
    node *head;
} list_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati lista
//////////////////////////////////////////////////

//////////////////////////////////////////////////
/// Definizione della struttura dati grafo
//////////////////////////////////////////////////

int *V;          // elenco dei nodi del grafo
int *V_prev;     // nodo precedente dalla visita
float *V_dist;   // distanza da sorgente

// list_t* E;  /// array con le liste di adiacenza per ogni nodo
list_t **E; /// array di puntatori a le liste di adiacenza per ogni nodo
int n_nodi;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati grafo
//////////////////////////////////////////////////

/// Questo e' un modo per stampare l'indirizzo node relativamente ad un altro di riferimento.
/// Permette di ottenere offset di piccola dimensione per essere facilmente visualizzati
/// Nota: il metodo non e' robusto e potrebbe avere comportamenti indesiderati su architetture diverse
/// L'alternativa corretta' e' utilizzare %p di printf: es. printf("%p\n",(void*) node);
/// con lo svantaggio di avere interi a 64 bit poco leggibili

list_t *global_ptr_ref = nullptr; /// usato per memorizzare il puntatore alla prima lista allocata

int get_address(void *node) {
    return (int)((long)node - (long)global_ptr_ref);
}

void node_print(int n) {

    /// calcolo massima distanza (eccetto infinito)
    float max_d = 0;
    for (int i = 0; i < n_nodi; i++)
        if (max_d < V_dist[i] && V_dist[i] < INFTY)
            max_d = V_dist[i];

    output_graph << "node_" << n << "_" << n_operazione << endl;
    output_graph << "[ shape = oval; ";


    float col =abs( V_dist[n] / max_d); /// distanza in scala 0..1
    output_graph << "fillcolor = \"0.0 0.0 " << col / 2 + 0.5 << "\"; style=filled; ";
    if (V_dist[n] < INFTY)
        output_graph << "label = "
                     << "\"Idx: " << n << ", dist: " << V_dist[n] << "\" ];\n";
    else
        output_graph << "label = "
                     << "\"Idx: " << n << ", dist: INF\" ];\n";

    node_t *elem = E[n]->head;
    while (elem != NULL) { /// disegno arco
        output_graph << "node_" << n << "_" << n_operazione << " -> ";
        output_graph << "node_" << elem->idx << "_" << n_operazione << " [ label=\"" << elem->w << "\", len=" << elem->w / 100 * 10 << " ]\n";
        elem = elem->next;
    }

    if (V_prev[n] != -1) { // se c'e' un nodo precedente visitato -> disegno arco

        float len = 0;
        /*
        //cerco arco V_prev[n] --> V[n]
        node_t* elem=E[ V_prev[n] ]->head;
        while (elem!=NULL){
        int v=elem->val; /// arco u --> v
        if (v == V[n])
          len=elem->w;
        elem=elem->next;
          }
        */

        len = 1;
        output_graph << "node_" << n << "_" << n_operazione << " -> ";
        output_graph << "node_" << V_prev[n] << "_" << n_operazione << " [ color=blue, penwidth=5, len=" << len / 100 * 10 << " ]\n";
    }
}


void graph_print() {
    for (int i = 0; i < n_nodi; i++)
        node_print(i);
    n_operazione++;
}

void list_print(list_t *l) {
    printf("Stampa lista\n");

    if (l->head == nullptr) {
        printf("Lista vuota\n");
    } else {
        node_t *current = l->head;

        while (current != nullptr) {
            if (!details)
                printf("%d w:%f, ", current->idx, current->w);
            else { /// stampa completa
                if (current->next == nullptr)
                    printf("allocato in %d [Val: %d, W: %f, Next: NULL]\n",
                           get_address(current),
                           current->idx,
                           current->w);
                else
                    printf("allocato in %d [Val: %d, W: %f, Next: %d]\n",
                           get_address(current),
                           current->idx,
                           current->w,
                           get_address(current->next));
            }
            current = current->next;
        }
        printf("\n");
    }
}

list_t* list_new(void) {
    list_t* l = new list_t();
    if (details) {
        printf("Lista creata\n");
    }

    l->head = nullptr;
    if (details) {
        printf("Imposto a NULL head\n");
    }

    return l;
}

void list_insert_front(list_t *l, int elem, float w) {
    /// inserisce un elemento all'inizio della lista
    node_t* new_node = new node_t;
    new_node->next = nullptr;

    new_node->idx = elem;
    new_node->w = w;

    new_node->next = l->head;

    l->head = new_node;
}

void print_array(int *A, int dim) {
    for (int j = 0; j < dim; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

void print_array_graph(int *A, int n, string c, int a, int l, int m, int r) {
    /// prepara il disegno dell'array A ed il suo contenuto (n celle)
    /// a e' il codice del nodo e c la stringa
    /// l,m,r i tre indici della bisezione

    // return ;

    output_graph << c << a << " [label=<" << endl;

    /// tabella con contenuto array
    output_graph << "<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"0\" > " << endl;
    /// indici
    output_graph << "<TR  >";
    for (int j = 0; j < n; j++) {
        output_graph << "<TD ";
        output_graph << ">" << j << "</TD>" << endl;
    }
    output_graph << "</TR>" << endl;
    output_graph << "<TR>";
    // contenuto
    for (int j = 0; j < n; j++) {
        output_graph << "<TD BORDER=\"1\"";
        if (j == m)
            output_graph << " bgcolor=\"#00a000\""; /// valore testato
        else if (j >= l && j <= r)
            output_graph << " bgcolor=\"#80ff80\""; /// range di competenza
        output_graph << ">" << A[j] << "</TD>" << endl;
    }
    output_graph << "</TR>" << endl;
    output_graph << "</TABLE> " << endl;

    output_graph << ">];" << endl;
}

void BellmanFord(float *V_dist , int* V_prev , list_t** E , int source) {
    for (int i = 0; i < n_nodi; i++) {
            V_dist[i] = INFTY;
            V_prev[i] = -1;
    }

    V_dist[source] = 0;

    for (int i = 0; i < n_nodi - 1; i++) {
        for (int j = 0; j < n_nodi; j++) {
            node_t* elem = E[j]->head;
            while (elem != nullptr) {
                if (V_dist[j] + elem->w < V_dist[elem->idx]) {
                    V_dist[elem->idx] = V_dist[j] + elem->w;
                    V_prev[elem->idx] = j;
                }
                elem = elem->next;
            }
        }
    }

    for (int i = 0; i < n_nodi; i++) {
        node_t* elem = E[i]->head;
        while (elem != nullptr) {
            if (V_dist[i] + elem->w < V_dist[elem->idx]) {
                printf("Errore: ciclo negativo\n");
            }
            elem = elem->next;
        }
    }
}

void test1();

void test2();

int parse_cmd(int argc, char **argv) {
    /// controllo argomenti
    int ok_parse = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][1] == 'v') {
            details = 1;
            ok_parse = 1;
        }
        if (argv[i][1] == 'g') {
            graph = 1;
            ok_parse = 1;
        }
    }

    if (argc > 1 && !ok_parse) {
        printf("Usage: %s [Options]\n", argv[0]);
        printf("Options:\n");
        printf("  -verbose: Abilita stampe durante l'esecuzione dell'algoritmo\n");
        printf("  -graph: creazione file di dot con il grafo dell'esecuzione (forza d=1 t=1)\n");
        return 1;
    }

    return 0;
}

int main(int argc, char **argv) {

    // init random
    srand((unsigned)time(0));

    if (parse_cmd(argc, argv))
        return 1;

    if (graph) {
        output_graph.open("graph.dot");
        /// preparo header
        output_graph << "digraph g" << endl;
        output_graph << "{ " << endl;
        output_graph << "node [shape=none]" << endl;
        output_graph << "rankdir=\"LR\"" << endl;
        //    output_graph << "edge[tailclip=false,arrowtail=dot];"<<endl;
    }

    n_nodi = 5;
    V = new int[n_nodi];
    V_prev = new int[n_nodi];
    V_dist = new float[n_nodi];
    E = new list_t *[n_nodi];

    for (int i = 0; i < n_nodi; i++) {
        V_prev[i] = -1;
        V_dist[i] = INFTY;
        E[i] = list_new();
    }

    // Aggiungi archi normali (esempio)
    list_insert_front(E[0], 1, 2);   // 0 → 1 (peso 2)
    list_insert_front(E[1], 2, 3);   // 1 → 2 (peso 3)
    list_insert_front(E[2], 3, 2);   // 2 → 3 (peso 2)
    list_insert_front(E[3], 4, 2);   // 3 → 4 (peso 2)
    list_insert_front(E[1], 4, 7);   // 1 → 4 (peso 7)
    // **Arco negativo**
    list_insert_front(E[3], 1, -4);  // 3 → 1 (peso -4)
    global_ptr_ref = E[0];

    for (int i = 0; i < n_nodi; i++) {
        printf("Sono il nodo di indice %d nell'array\n", i);
        printf("Il valore del nodo e' %d\n", V[i]);
        printf("La lista di adiacenza e'\n");
        list_print(E[i]);
    }

    output_graph << "subgraph cluster_" << n_operazione << " {\n";
    output_graph << "label = \"Grafo " << n_operazione + 1 << "\";\n";
    graph_print();
    output_graph << "}\n";
    BellmanFord(V_dist, V_prev, E, 0);
    output_graph << "subgraph cluster_" << n_operazione << " {\n";
    output_graph << "label = \"Grafo " << n_operazione + 1 << "\";\n";
    graph_print();
    output_graph << "}\n";


    delete []  V;
    delete [] V_prev;
    delete [] V_dist;
    for (int i = 0; i < n_nodi ; i++){
        delete E[i];
    }
    delete  [] E;


    n_nodi = 5;
    V = new int[n_nodi];
    V_prev = new int[n_nodi];
    V_dist = new float[n_nodi];
    E = new list_t *[n_nodi];


    for (int i = 0; i < n_nodi; i++) {
        V_prev[i] = -1;
        V_dist[i] = INFTY;
        E[i] = list_new();
    }

    // Archi normali
    list_insert_front(E[0], 1, 4);    // 0 → 1
    list_insert_front(E[1], 2, 3);    // 1 → 2
    list_insert_front(E[1], 3, 2);    // 1 → 3

    // Ciclo negativo diverso dal primo
    list_insert_front(E[2], 4, -2);   // 2 → 4
    list_insert_front(E[4], 2, -3);   // 4 → 2   (ciclo negativo: 2 → 4 → 2 peso -5)

    // Un arco extra fuori dal ciclo negativo
    list_insert_front(E[3], 4, 1);    // 3 → 4


    global_ptr_ref = E[0];

    output_graph << "subgraph cluster_" << n_operazione << " {\n";
    output_graph << "label = \"Grafo " << n_operazione + 1 << "\";\n";
    graph_print();
    output_graph << "}\n";
    BellmanFord(V_dist, V_prev, E, 0);
    output_graph << "subgraph cluster_" << n_operazione << " {\n";
    output_graph << "label = \"Grafo " << n_operazione + 1 << "\";\n";
    graph_print();
    output_graph << "}\n";


    delete []  V;
    delete [] V_prev;
    delete [] V_dist;

    for (int i = 0; i < n_nodi; i++) {
        delete E[i];
    }

    delete  [] E;

    if (graph) {
        /// preparo footer e chiudo file
        output_graph << "}" << endl;
        output_graph.close();
        cout << " File graph.dot scritto" << endl
             << "****** Creare il grafo con: neato graph.dot -Tpdf -o graph.pdf" << endl;
    }

    return 0;
}