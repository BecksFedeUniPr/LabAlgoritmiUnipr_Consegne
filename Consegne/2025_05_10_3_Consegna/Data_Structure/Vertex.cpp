#include "Vertex.h"


void Vertex::VertexPrint(std::ofstream &output_graph){

    output_graph << this->getVal() <<  std::endl;
    output_graph << "[ shape = oval; \n";
    switch (this->getState())
    {
        case UNVISITED:
            output_graph << "fillcolor = \"#bbbbbb\"; style=filled; \n";
            break;
        case VISITED:
            output_graph << "fillcolor = \"#555555\"; style=filled; \n";
        default:
            break;
    }

    output_graph << "];\n";
}