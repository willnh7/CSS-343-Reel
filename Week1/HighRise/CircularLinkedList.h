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
        // Private vars for the circular list ( initialized to null due to it being flagged by 
        // valgrind)
        Node* head = nullptr;
        Node* last = nullptr;
    public:
        // Start with the constructors
        //TODO: create one node circular list, test
        CircularLinkedList() {
            // single node circular list
            head = new Node(T());
            head->next = head;
            last = head;
        }
        /**
         * 
         * 
         * 
         * 
         * Precondition: called as CircularLinkedList<string> myList({"Ling", "Bob", "Harry"}); 
         * The list should be created via a already formatted list
         * Post condition: a newly created circular linked list.
         * 
         */
        CircularLinkedList(const std::initializer_list<T>& array){
            // Empty list, nothing is done
            if(array.size() == 0) {
                std::cout << "Empty List\n";
            } else {
                 // if it is not a empty list it will create a array
                std::cout << "This takes a ARRAY\n";
                for(const T& val : array) {
                    addToList(val);
                }
            }
           
        }
        /**
         * The destructor for our circular linked list that calls the function
         * clear() so that all memory is deallocated and freed so that there are no memory leaks.
         * 
         */
        ~CircularLinkedList() {
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
        /**
         * This function deletes the next node from the head node,
         * changing the pointers to reflect the deletion and also moving the head pointer to the node
         * that was after the deleted one.
         * Precondition: the int next is a constant
         * Post condition: a shifted circular linked list, head begining from 
         * the node after the deleted node
         * EX: {"Ling", "Bob", "Jennet"} the head is Ling, after deletion, it should be
         * Jennet.
         */
        std::string removeNext(int k) {
            
            std::string removed = "";
            // the general logic is as follows
            /** 
             * First we check the size, if the size is only 1, return, so we need
             * a size for the circular linked list(with tests). 
             * 
             * 
             * so pseudo code would be, 
             * check size > 1
             * if not { return head}
             * if  size > 1 {
             *      Node* temp = head->next;
             *      string removed = temp->data;
             *      head->next = temp->next;
             *      delete temp;
             *      temp = nullptr;
             *      
             * //shifting the pointers
             *      Node* tempHead = head->next;
             *      last = head;
             *      head = tempHead;
             *      
             * }
             */
            if(size() > 1) {
                /**
                 * Deletes the next node for the assignment which the next will be constant
                 * k = 1
                 */
                Node* temp = head->next;
                removed = temp->data;
                head->next = temp->next;
                // added to account for edge cases.
                if(temp == last) {
                    last = head;
                }
                delete temp;
                temp = nullptr;
                /*
                Node* tempHead = head->next;
                if(tempHead == last) {

                }
                */
            }
            return removed;
        }

        T getCurrent(){
            return head->data;
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
            // If the list is already empty, return
            if(head == nullptr) {
                std::cout << "\nClearing a already empty list!\n";
                return;
            }
            // start with the head to start deletion
            Node* curr = head;
            Node* nextNode = curr->next;
            // breaking the connection and essentially making it a regular
            // linked list
            last->next = nullptr;
            // Since we start at the head, we must use do while 
            while(curr != nullptr) {
                // get the nextNode immediately since we know curr is not nullptr
                // no errors.
                nextNode = curr->next;

                std::cout << "\nDeleting Node: " << curr->data << "\n";
                // If the next node havent reached the end, print which node we are moving to
                // and assign the curr node to the next node we have to delete
                if(nextNode != nullptr) {
                    std::cout << "Moving to Node: " << nextNode->data << "\n";
                }
                // 
                delete curr;
                curr = nextNode;
            }
            // This is to ensure there are no dangling ptrs
            head = nullptr;
            last = nullptr;
                
        }

        int size(){
            int count = 0;
            Node* curr = head;
            if(curr == last) {
                return count;
            }
            do {
                count++;
                curr = curr->next;
            } while (curr != head);
            return count;
        }
};
#endif