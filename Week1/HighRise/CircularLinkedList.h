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
            // Nothing in here?
            last = new Node(T());
            last->next = last;
        }
        /**
         * An initializer_list constructor so that it can create a circular linked list.
         * This is done to accept braced inputs in the parameter.
         * 
         * Precondition: called as CircularLinkedList<string> myList({"Ling", "Bob", "Harry"}); 
         * The list should be created via a already formatted list
         * Post condition: a newly created circular linked list.
         */
        CircularLinkedList(const std::initializer_list<T>& array){
            // Empty list, nothing is done
            if(array.size() == 0) {
                last = nullptr;
            } else {
                // if it is not a empty list it will create a array
                for(const T& val : array) {
                    addToList(val);
                }
            }
           
        }
        /**
         * The destructor for our circular linked list that calls the function
         * clear() so that all memory is deallocated and freed so that there are no memory leaks.
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
         * Precondition: k must be a positive constant, k >= 0;
         * Postcondition: TODO
         */
        std::string removeNext(int k) {
            // Empty list
            if(last == nullptr){
                return "List is empty";
            }
            // No negatives allowed, simply having positive constants
            if(k < 0) {
                return "None were removed, no negatives!";
            }
            // One node
            if(last->next == last) {
                T val = last->data;
                delete last;
                last = nullptr;
                return val;
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
            // if the node being deleted is the last item, make the last the prev node
            if(nodeToDelete == last) {
                last = prev;
            }

            prev->next = nodeToDelete->next;
            delete nodeToDelete;
            nodeToDelete = nullptr;

            last= prev;
            return removed;
        }
        /**
         * This function simply gets our current heads data, using the last node
         * to find the head. This is done soley for the assignment of getting the winner which will be often a 
         * single node in the list.
         */
        T getCurrent(){
            if(last == nullptr) throw std::runtime_error("Empty list");
            return last->next->data;
        }
        /**
         * This function simply goes through our circular linked list and prints out all the 
         * elements from the start to the end of our list.
         * Serves mainly for debugging and tracking.
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
            
            // Make sure head isn't a nullptr, so no nullptr undefined behavior.
            while(head != nullptr) {
                // get the nextNode immediately since we know curr is not nullptr
                // no errors.
                Node* nextNode = head->next;
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
        int size(){
            // List doesn't have any nodes since last points to head.
            if(last == nullptr) {
                return 0;
            }

            int count = 0;
            Node* curr = last->next;
            // Count the items in list
            do {
                count++;
                curr = curr->next;
            } while (curr != last->next);

            return count;
        }
};
#endif