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
        Node* last = nullptr;
    public:
        // Start with the constructors
        CircularLinkedList() {
            // single node circular list
            last = new Node(T());
            last->next = last;
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

            if(!last) {
                // for a circular linked list, there won't be a nullptr as it will 
                // wrap around itself essentially
                last = newNode;
                newNode->next = last;
            } else {
                newNode->next = last->next;
                last->next = newNode;
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
            if(size() <= 1 ) {
                return last->data;
            }
            if(k < 0) {
                return "None were removed, no negatives";
            }
            std::string removed = "";
            Node* prev = last;
            /**
             * Goes to the node before deletion
             */
            for(int i = 0; i < k; i++) {
                prev = prev->next;
            }
            Node* nodeToDelete = prev->next;
            removed = nodeToDelete->data;
            if(nodeToDelete == last) {
                last = prev;
            }
            prev->next = nodeToDelete->next;
            
            delete nodeToDelete;
            nodeToDelete = nullptr;

            last->next= prev->next;
            return removed;
        }
        /**
         * This function TODO: Explain why it is set up as such.
         */
        T getCurrent(){
            return last->next->data;
        }
        /**
         * This function simply goes through our circular linked list and prints out all the 
         * elements from the start to the end of our list.
         * Serves mainly for debugging and tracking.
         * 
         * 
         */
        void printList() {
            // empty list
            if(last == nullptr) {
                return;
            }
            // Start at head and then print head
            Node* head = last->next;
            do{
                std::cout << head->data << " ";
                head = head->next;
            } while(head != last->next);
            std::cout << "\n";
        }
        /**
         * The function clears the circular linked list. This is used by our destructor
         * and frees up memory.
         */
        void clear() {
            // If the list is already empty, return
            if(last == nullptr) {
                std::cout << "\nClearing a already empty list!\n";
                return;
            }
            // start with the head to start deletion
            Node* head = last->next;
            // Break the circular link
            last->next = nullptr;
            Node* nextNode = nullptr;
            
            // Since we start at the head, we must use do while 
            while(head != nullptr) {
                // get the nextNode immediately since we know curr is not nullptr
                // no errors.
                nextNode = head->next;
                std::cout << "Deleting Node: " << head->data << "\n";
                // If the next node havent reached the end, print which node we are moving to
                // and assign the curr node to the next node we have to delete
                if(nextNode != nullptr) {
                    std::cout << "Moving to Node: " << nextNode->data << "\n";
                }
                // 
                delete head;
                head = nextNode;
            }
            last = nullptr;
        }
        /**
         * Gets the size of the circular linked list.
         * @return size of list
         */
        //TODO: ERR in size after deletion
        int size(){
            if(last == nullptr) {
                // TODO; FIX ERRORS
            }
            int count = 0;
            Node* curr = last->next;
            if(curr == last) {
                return count;
            }
            do {
                count++;
                curr = curr->next;
            } while (curr != last->next);
            return count;
        }
};
#endif