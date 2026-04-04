#include <iostream>
#include "CircularLinkedList.h"
#include <string>
using namespace std;

int passed = 0;
int testTotal = 0;
void testEqual(const std::string& test, const string& expected, const string& actual){
    testTotal++;
    if(expected == actual) {
        cout << "[PASS] " << test
                    << " | Expected: " << expected 
                    << " | Actual: " << actual << "\n";
        passed ++;
    } else {
        cout << "[FAIL] " << test 
                    << " | Expected: " << expected 
                    << " | Actual: " << actual << "\n";
    }
}
void testEqualInts(const std::string& test, int expected, int actual) {
    testTotal++;
    if(expected == actual) {
        cout << "[PASS] " << test
                    << " | Expected: " << expected 
                    << " | Actual: " << actual << "\n";
        passed++;
    } else {
        cout << "[FAIL] " << test 
                  << " | Expected: " << expected 
                  << " | Actual: " << actual << "\n";
    }
}

int main() {
    

    CircularLinkedList<string> emptyList({});
    testEqualInts("Empty list size", 0, emptyList.size());
    testEqual("Remove off empty", "List is empty", emptyList.removeNext(0));
    cout << "\n";
    /*
    This is the scenario given by the assignment.
    */
    CircularLinkedList<string> residents({"Laing", "Wilder",  "Frobisher"});
    testEqualInts("List of size 3", 3, residents.size());
    while(residents.size() > 1) {
        const string eaten = residents.removeNext(1);  // k == 1
        cout << "Eaten: " << eaten << "\n";
    }
    const string winner = residents.getCurrent();
    testEqual("Winner of 3", "Frobisher", winner);
    
    cout << "\n";
    CircularLinkedList<string> friends({"Laing", "Wilder",  "Frobisher", "Kinda"});
    testEqualInts("List of size 4", 4, friends.size());
    while(friends.size() > 1) {
        const string eaten = friends.removeNext(1);  // k == 1
        cout << "Eaten: " << eaten << "\n";
    }
    testEqual("Winner of 4", "Laing", friends.getCurrent());

    cout << "\n";
    CircularLinkedList<string> stepTwo({"Laing", "Wilder",  "Frobisher", "Kinda"});
    testEqualInts("List of size 4", 4, stepTwo.size());
    while(stepTwo.size() > 1) {
        const string eaten = stepTwo.removeNext(2);  // k == 2
        cout << "Eaten: " << eaten << "\n";
    }
    testEqual("Winner of 4, k = 2", "Laing", stepTwo.getCurrent());

    cout << "\n";
    CircularLinkedList<string> size1({"Liasy"});
    testEqualInts("1 node list size", 1, size1.size());
    testEqual("Negative remove", "None were removed, no negatives!", size1.removeNext(-1));
    testEqual("Remove only node", "Liasy", size1.removeNext(1));

    cout << "Total passed: " << passed << "/" << testTotal << "\n";
}

