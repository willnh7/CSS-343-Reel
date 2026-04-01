#include <iostream>
#include "CircularLinkedList.h"
#include <string>
using namespace std;

int main() {
    cout << "Bleht\n";
    CircularLinkedList<string> residents({"Laing", "Wilder",  "Frobisher"});
    
    /*
   
    while(residents.size() > 1) {
        string eaten = residents.removeNext(1);  // k == 1
        cout << "Eaten: " << eaten << "\n";
    }

    string winner = residents.getCurrent();
    cout << "The winner is " << winner << "!\n";
    */
}