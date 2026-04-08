#include <string>
#include <iostream>


class Node {
public:
  std::string value;
  Node* pLeft;
  Node* pRight;
};

// root to node(depth) 
void high(Node* root, int depth) {
    if(root == nullptr) { 
        return; 
    }
   
    std::cout << root->value << " & depth " << depth << "\n"; 
    if ( root->pLeft != nullptr) {
        high(root->pLeft, depth + 1);
    }
    if ( root->pRight != nullptr) {
        high(root->pRight, depth + 1);
    }
    return;
}


int main() {
    Node* root = new Node();
    root->value = "Bobby";
    root->pLeft = new Node();
    root->pLeft->value = "Jill";
    root->pRight = new Node();
    root->pRight->value = "Still";
    high(root, 0);
}