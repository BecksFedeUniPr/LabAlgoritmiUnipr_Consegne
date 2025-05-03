#include "List.h"

class Graph{
    private:
        List* adiance_list;
        int n_vertex;
    public:

        Graph(){
            this->adiance_list = new List();
            n_vertex = 0;
        }

        void insertNode(int idx_node , int idx_other_node,int value){
            if(idx_node < 0 or idx_other_node < 0)
                return;
            n_vertex++;
        }
};


