#include "Node.h"

class List {
    private:
        Node *head;
    public:
        List(){
            this->head = nullptr;
        }


        void insert_front(int val){
            Node* new_node = new Node(val);
            
            Node* old_head = this->head;

            this->head = new_node;

            new_node->setNext(old_head);
        }

        ~List() {
            Node* current = head;

            while(current != nullptr){
                Node* next_node = current->getNext();
                delete current;
                current = next_node;
            }
        }
} list_t;