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

    /*
    cout << "\nThe size of the residents is: " << residents.size() << "\n";
    cout << "The size of the friends is: " << friends.size() << "\n";
    cout << "\nEaten: " << residents.removeNext(1) << "\n";
    cout << "The size of the residents is: " << residents.size() << "\n";
    residents.printList();
    */

    while(residents.size() > 1) {
        const string eaten = residents.removeNext(1);  // k == 1
        cout << "Eaten: " << eaten << "\n";
    }
    const string winner = residents.getCurrent();
    cout << "The winner is " << winner << "!\n";
}