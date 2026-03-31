#pragma once
// Start with the constructors


// Circular (array given) 

// fill the list with the array items

// default creates one node circular list 

template<typename T> 
class CircularLinkedList  {
    public:
        //TODO: create one node circular list
        CircularLinkedList() {}
        //TODO: fill a list of appropriate size with array size
        CircularLinkedList(T array){}
    private:
        class Node {
            public: 
                T data;
                Node* next;
                Node(T myData): data(myData) {}
        }
        
        

};