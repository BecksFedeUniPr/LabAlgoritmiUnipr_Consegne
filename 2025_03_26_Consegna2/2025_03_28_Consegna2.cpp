#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <queue>

using namespace std;

/*
 * Flip albero: per ogni nodo il sottoalbero destro diventa il sottoalbero sinistro e viceversa.
Calcolo profondità di ciascun nodo dell'albero
Funzione isBalanced: restituire un flag che indichi se l'albero è bilanciato o meno. Bonus: l'algoritmo è O ( n ) con n nodi
Funzione isComplete: restituire un flag che indiche se l'albero è completo secondo la definizione classica
Funzione Lowest Common Ancestor: dati due valori presenti nell'albero, restituire il valore del nodo piu' basso che contiene entrambi nel suo sottoalbero
*/


int details = 0;
int graph = 0;


int max_nodes = 10;
int n_nodes = 0;
int ct_visit = 0;

int n = 0; /// dimensione dell'array

/// file di output per grafo
ofstream output_graph;
int n_operazione = 0; /// contatore di operazioni per visualizzare i vari step

ofstream output_visit;
ifstream input_visit;
//////////////////////////////////////////////////
/// Definizione della struttura dati tree
//////////////////////////////////////////////////

/// struct per il nodo dell'albero
typedef struct node {
    int val;
    node *L;
    node *R;
    node *parent;
} node_t;

//////////////////////////////////////////////////
/// Fine Definizione della struttura dati tree
//////////////////////////////////////////////////

/// Questo e' un modo per stampare l'indirizzo node relativamente ad un altro di riferimento.
/// Permette di ottenere offset di piccola dimensione per essere facilmente visualizzati
/// Nota: il metodo non e' robusto e potrebbe avere comportamenti indesiderati su architetture diverse
/// L'alternativa corretta' e' utilizzare %p di printf: es. printf("%p\n",(void*) node);
/// con lo svantaggio di avere interi a 64 bit poco leggibili

node_t *global_ptr_ref = NULL; /// usato per memorizzare il puntatore alla prima lista allocata

int get_address(void *node) {
    if (node == NULL)
        return 0;
    return abs((node_t*)node - global_ptr_ref);
}

/// stampa il codice del nodo per dot
void print_node_code(node_t *n) {
    output_graph << "node_" << get_address(n) << "_" << n_operazione;
}


int height(const node_t* node) {
    if(node == nullptr)
        return -1;
    return max(height(node->L), height(node->R)) + 1;
}


int depth(node_t* node) {
    if(node->parent == nullptr)
        return 0;
    return depth(node->parent) + 1;
}

int heightAndCheckBalance(const node_t* node) {
    if (node == nullptr) {
        return 0; 
    }

    int leftHeight = heightAndCheckBalance(node->L);
    if (leftHeight == -1) {
        return -1;
    }

    int rightHeight = heightAndCheckBalance(node->R);
    if (rightHeight == -1) {
        return -1;
    }

    if (abs(leftHeight - rightHeight) > 1) {
        return -1;
    }

    return max(leftHeight, rightHeight) + 1;
}

// Funzione per verificare se l'albero è bilanciato
bool isBalanced(const node_t* node) {
    return heightAndCheckBalance(node) != -1;
}

void node_print_graph(node_t *n) {
    // Compute height and depth for the current node
    int node_height = height(n);
    int node_depth = depth(n);

    // Print node code
    print_node_code(n);
    output_graph << "\n[label=<\n<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\" >\n";

    // Node address row
    output_graph << "<TR> <TD CELLPADDING=\"3\" BORDER=\"0\" ALIGN=\"LEFT\" bgcolor=\"#f0f0f0\" PORT=\"id\">";
    output_graph << get_address(n) << "</TD> </TR>\n";

    // Node value row
    output_graph << "<TR><TD PORT=\"val\" bgcolor=\"#a0FFa0\">";
    output_graph << n->val << "</TD></TR>\n";

    // Height and Depth row
    output_graph << "<TR><TD bgcolor=\"#FFD700\">Height: " << node_height << "</TD></TR>\n";
    output_graph << "<TR><TD bgcolor=\"#87CEEB\">Depth: " << node_depth << "</TD></TR>\n";

    // Left child row
    output_graph << "<TR> <TD PORT=\"L\" ";
    if (n->L == NULL)
        output_graph << "bgcolor=\"#808080\"> NULL";
    else
        output_graph << "> " << get_address(n->L);
    output_graph << "</TD>\n";

    // Right child row
    output_graph << "<TD PORT=\"R\" ";
    if (n->R == NULL)
        output_graph << "bgcolor=\"#808080\"> NULL";
    else
        output_graph << "> " << get_address(n->R);
    output_graph << "</TD>\n</TR></TABLE>>];\n";

    // Visualize sibling nodes on the same rank
    if (n->L != NULL && n->R != NULL) {
        output_graph << "rank = same; ";
        print_node_code(n);
        output_graph << ";";
        print_node_code(n->L);
        output_graph << ";";
        print_node_code(n->R);
        output_graph << ";\n";
    }

    // Draw edges to children
    if (n->L != NULL) {
        print_node_code(n);
        output_graph << ":L:c -> ";
        print_node_code(n->L);
        output_graph << ":id ;\n";
    }

    if (n->R != NULL) {
        print_node_code(n);
        output_graph << ":R:c -> ";
        print_node_code(n->R);
        output_graph << ":id ;\n";
    }
}


void tree_print_rec_graph(node_t *n) {
    if (n != NULL) {
        node_print_graph(n);
        tree_print_rec_graph(n->L);
        tree_print_rec_graph(n->R);
    }
}

void tree_print_graph(node_t *n) {
    /// stampa ricorsiva del nodo
    tree_print_rec_graph(n);
    n_operazione++;
}

void node_print(node_t *n) {
    if (n == NULL)
        printf("Puntatore vuoto\n");
    else
        printf("allocato in %d [Val: %d, L: %d, R: %d]\n",
               get_address(n),
               n->val,
               get_address(n->R),
               get_address(n->L));
}

node_t *node_new(int elem,node_t* parent) { /// crea nuovo nodo
    node_t *t = new node_t;
    if (details) {
        printf("nodo creato\n");
    }

    t->val = elem;
    t->L = NULL;
    t->R = NULL;
    t->parent = parent;
    if (details) {
        printf("Imposto a NULL children\n");
    }

    return t;
}

void tree_insert_child_L(node_t *n, int elem) {
    /// inserisco il nuovo nodo con contenuto elem
    /// come figlio Left del nodo n

    /// creo nodo
    n->L = node_new(elem,n);
}

void tree_insert_child_R(node_t *n, int elem) {
    /// inserisco il nuovo nodo con contenuto elem
    /// come figlio Right del nodo n
    n->R = node_new(elem,n);
}

void insert_random_rec(node_t *n) {
    if (n_nodes >= max_nodes) // Ensure strict bound
        return;

    printf("inserisco %d\n", n_nodes);

    float probabilita = 0.8;

    if (rand() % 100 < probabilita * 100 && n_nodes < max_nodes) {
        tree_insert_child_R(n, rand() % 100);
        n_nodes++;
    }
    if (rand() % 100 < probabilita * 100 && n_nodes < max_nodes) {
        tree_insert_child_L(n, rand() % 100);
        n_nodes++;
    }

    // Re-check the condition before recursion
    if (n->L != NULL && n_nodes < max_nodes)
        insert_random_rec(n->L);
    if (n->R != NULL && n_nodes < max_nodes)
        insert_random_rec(n->R);
}

bool isCompleteTree(node_t* root) {
    if (root == nullptr) {
        return true; // An empty tree is complete
    }

    std::queue<node_t*> q;
    q.push(root);

    bool encounteredNull = false;

    while (!q.empty()) {
        node_t* current = q.front();
        q.pop();

        if (current == nullptr) {
            encounteredNull = true; // If we encounter a null, all subsequent nodes must also be null
        } else {
            if (encounteredNull) {
                return false; // If we encounter a non-null node after a null, the tree is not complete
            }
            q.push(current->L); // Add left child to the queue
            q.push(current->R); // Add right child to the queue
        }
    }

    return true; // If we traverse the entire tree without issues, it is complete
}


void EulerOrder(node_t *n) {

    if (details)
        printf("%d ", n->val);

    output_visit << n->val << "\n";

    if (graph) {
        node_print_graph(n);
    }

    if (n->L != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":id:w -> ";
            print_node_code(n->L);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }

        EulerOrder(n->L);

        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->L);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":val:s [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);
    output_visit << n->val << "\n";

    if (n->R != NULL) {
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n);
            output_graph << ":val:s -> ";
            print_node_code(n->R);
            output_graph << ":id:w [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
        EulerOrder(n->R);
        if (graph) {
            // scrivo arco con numero operazione di visita
            print_node_code(n->R);
            output_graph << ":id:e -> ";
            print_node_code(n);
            output_graph << ":id:e [ color=blue, fontcolor=blue, penwidth=3, label = \"" << ct_visit++ << "\"]\n";
        }
    }

    if (details)
        printf("%d ", n->val);
    output_visit << n->val << "\n";
}

void swap(node_t* left , node_t* right){
    node_t temp = *left;
    left = right;
    right = &temp;
}

/// crea una copia dell'albero in input, scambiando i sottoalberi L e R
node_t *flip(node_t *n) {
    if (n == nullptr)
        return nullptr;
    
    node_t* new_node = node_new(n->val, n->parent);
    
    // Inverti i sottoalberi: nuovo sinistro da flip del sottoalbero destro originale e viceversa.
    new_node->L = flip(n->R);
    if (new_node->L != nullptr)
        new_node->L->parent = new_node;
    
    new_node->R = flip(n->L);
    if (new_node->R != nullptr)
        new_node->R->parent = new_node;
    
    return new_node;
}

node_t* lowest_common_anchestor(node* t1,node* t2){
    node* t1_cpy = t1;
    node* t2_cpy = t2;

    int depth1 = depth(t1);
    int depth2 = depth(t2);

    while (depth1 > depth2) {
        t1_cpy = t1_cpy->parent;
        depth1--;
    }
    while (depth2 > depth1) {
        t2_cpy = t2_cpy->parent;
        depth2--;
    }
    
    while (t1_cpy != t2_cpy) {
        t1_cpy = t1_cpy->parent;
        t2_cpy = t2_cpy->parent;
    }
    
    return t1_cpy;
}

// costruzione albero in base ai valori stampati dalla visita di eulero
// la funzione restituisce il puntatore alla radice dell'albero
// Es. input: 32 74 74 64 76 76 44 44 44 76 64 64 74 32 85 85 2 36 36 36 2 85 85 85 2 85 32
node_t *build_euler() {

    return NULL;
}

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
    int i, test;

    if (parse_cmd(argc, argv))
        return 1;

    // init random
    srand((unsigned)time(NULL));

    node_t *root = node_new(1,global_ptr_ref);
    node_t* root_flipped;

    // creo albero random
    //insert_random_rec(root);
    root->L = node_new(2, root);
    root->R = node_new(3, root);
    root->L->L = node_new(4, root->L);
    root->L->R = node_new(5, root->L);
    root_flipped = flip(root);

    if (graph) {
        output_graph.open("graph.dot");

        output_graph << "digraph g" << endl;
        output_graph << "{" << endl;
        output_graph << "node [shape=none]" << endl;
        output_graph << "rankdir=\"TB\"" << endl;
        output_graph << "edge[tailclip=false,arrowtail=dot];" << endl;


        output_graph << "tree_properties [label=<" << endl;
        output_graph << "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">" << endl;
        output_graph << "<TR><TD><B>Tree Properties</B></TD></TR>" << endl;
        output_graph << "<TR><TD>Balanced: " << (isBalanced(root) ? "Yes" : "No") << "</TD></TR>" << endl;
        output_graph << "<TR><TD>Complete: " << (isCompleteTree(root) ? "Yes" : "No") << "</TD></TR>" << endl;
        output_graph << "</TABLE>>];" << endl;

        tree_print_graph(root);
        tree_print_graph(root_flipped);


        output_graph << "}" << endl;
        output_graph.close();

        cout << " File graph.dot scritto" << endl
             << "Creare il grafo con: dot graph.dot -Tpdf -o graph.pdf" << endl;
    }

    delete root;
    delete root_flipped;

    return 0;
}