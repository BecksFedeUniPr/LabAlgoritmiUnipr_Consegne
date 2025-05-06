#include "Vertex.h"


void Vertex::VertexPrint(std::ofstream &output_graph,int n_operazione){

    output_graph << "node_" << this->getVal() << "_" << n_operazione <<  std::endl;
    output_graph << "[ shape = oval; ";
    if (this->state == VISITED)
        output_graph << "fillcolor = \"#bbbbbb\"; style=filled; ";
    if (this->state == PROCESSED)
        output_graph << "fillcolor = \"#555555\"; style=filled; ";
    output_graph << "label = " << "\"Idx: " << this->getVal() << ", val: " << this->val << "\" ];\n";

    Vertex* elem = this->getNext();
    while (elem != nullptr){ /// disegno arco
        output_graph << "node_" << elem->getVal() << "_" << n_operazione << " -> ";
        output_graph << "node_" << elem->val << "_" << n_operazione <<" [  color=gray ]\n";
        elem=elem->next;
    }
}