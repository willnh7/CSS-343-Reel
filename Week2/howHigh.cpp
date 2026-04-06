#include <string>
#include <iostream>


class Node {
public:
  std::string value;
  Node* pLeft;
  Node* pRight;
};

void high(Node* root, int edges) {
    if(root == nullptr) return;
    std::cout << root->value << " &  height " << edges << "\n"; 
    if ( root->pLeft != nullptr) {
        high(root->pLeft, edges++);
    }
    if ( root->pRight != nullptr) {
        high(root->pRight, edges++);
    }
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