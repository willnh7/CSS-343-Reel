#include <iostream>
#include "CircularLinkedList.h"
#include <string>
using namespace std;

int main() {
    cout << "Bleht\n";
    CircularLinkedList<string> residents({"Laing", "Wilder",  "Frobisher"});
    CircularLinkedList<string> friends({});
    residents.printList();
    friends.printList();
    // .clear() on a list before destructor,

    cout << "\nThe size of the residents is: " << residents.size() << "\n";
    cout << "\nThe size of the residents is: " << friends.size() << "\n";
    /*
    while(residents.size() > 1) {
        string eaten = residents.removeNext(1);  // k == 1
        cout << "Eaten: " << eaten << "\n";
    }
    */
    const string winner = residents.getCurrent();
    cout << "The winner is " << winner << "!\n";
}