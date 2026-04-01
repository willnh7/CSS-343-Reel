#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H



// fill the list with the array items
// default creates one node circular list 
template<typename T> 
class CircularLinkedList  {
    private:
        class Node {
            public: 
                T data;
                Node* next;
                Node(T myData): data(myData), next(nullptr){}
        };
        // Private vars for the circular list
        Node* head;
        Node* last;
    public:
        // Start with the constructors
        //TODO: create one node circular list, test
        CircularLinkedList() {
            // single node circular list
            head = new Node(T());
            head->next = head;
            last = head;
        }
        // Circular (array given) 
        //TODO: fill a list of appropriate size with array size
        // Need one for each 
        CircularLinkedList(const std::initializer_list<T>& array){
            std::cout << "This takes a ARRAY\n";
            for(const T& val : array) {
                std::cout << val <<"\n";
                addToList(val);
            }
           printList();
        }
        /**
         * The destructor for our circular linked list that calls the function
         * clear() so that all memory is deallocated and freed so that there are no memory leaks.
         * 
         */
        ~CircularLinkedList() {
            std::cout << "This is a destructor\n";
            clear();
        }
        
            
        /**
         * Helper to add to the list when we initialize using the initilizer 
         * list as a parameter
         * 
         * @para: a data value 
         */
        void addToList(const T& value) {
            Node* newNode = new Node(value);

            if(!head) {
                // for a circular linked list, there won't be a nullptr as it will 
                // wrap around itself essentially
                head = newNode;
                last = newNode;
                newNode->next = head;
            } else {
                last->next = newNode;
                newNode->next = head;
                last = newNode;
            }
        }

        void removeNext(int next) {
            if(head != nullptr){return;}

            // We don't want to remove when there is only one node, we will have a seperate clear function
            if(head == last) {
                return;
            } else {

            }
        }
        /**
         * This function simply goes through our circular linked list and prints out all the 
         * elements from the start to the end of our list.
         * Serves mainly for debugging and tracking.
         * 
         * 
         */
        void printList() {
            if(head == nullptr) {
                return;
            }

            Node* curr = head;
            do{
                std::cout << curr->data << " ";
                curr = curr->next;
            } while(curr != head);
        }
        /**
         * The function clears the circular linked list. This is used by our destructor
         * and frees up memory.
         */
        void clear() {
            if(head == nullptr) {
                return;
            }
            Node* curr = head;
            Node* nextNode = curr->next;

            while(curr != head) {
                delete curr;
                curr = nextNode;
                nextNode = curr->next;
            }
            
        }

};
#endif