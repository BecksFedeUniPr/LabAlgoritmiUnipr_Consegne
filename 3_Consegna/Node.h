class Node {
    private:
        int val;
        int state;
        struct Node* next;

    public:

        Node(int val){
            this->val = val;
            this->state = 0;
            this->next = nullptr;
        }

        // Getter per 'val'
        int getVal() const {
            return val;
        }

        // Setter per 'val'
        void setVal(int value) {
            val = value;
        }

        // Getter per 'is_visited'
        int getState() const {
            return state;
        }

        // Setter per 'is_visited'
        void setState(int state) {
            state = state;
        }

        // Getter per 'next'
        Node* getNext(){
            return this->next;
        }

        // Setter per 'next'
        void setNext(struct Node* nextNode) {
            this->next = nextNode;
        }
};