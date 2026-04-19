#include <iostream>
#include <string>
#include "rng.h"
#include "foodstuff.h"
#include "heap.h"   // TODO
#include "functors.h" // TODO

using std::cout;
using std::string;
using std::vector;
using std::less;

int testsPassed = 0;
int totalTests = 0;
/**
 * Helper method for simpleIntTests.
 */
void assertHeapVal(const string& testName, const int expected, const int actual) {
    totalTests++;
    cout << testName;
    if (actual == expected) {
        cout << "[PASSED]\n"
             << "  Expected: " << expected << "\n"
             << "  Actual:   " << actual << "\n";
        testsPassed++;
    } else {
        cout << "[FAILED]\n"
             << "  Expected: " << expected << "\n"
             << "  Actual:   " << actual << "\n";
    }
}

/**
 * Tests the heap using simple ints 
 * based off the logic it gives the ordering for a int heap.
 */
void simpleTestInt() {
    Heap<int,less<int>> myHeap;
    const int INPUT_VALUES[] = {50,30,5,10};
    for(int i = 0 ; i < sizeof(INPUT_VALUES) / sizeof(INPUT_VALUES[0]); i++) {
        myHeap.add(INPUT_VALUES[i]);
    }
    const int EXPECTED_VALUES[] = {5,10,30,50};

    int actualRemoved = myHeap.remove();
    int expected = EXPECTED_VALUES[0];
    assertHeapVal("Test 1: First int is the smallest", expected, actualRemoved);
    
    actualRemoved = myHeap.remove();
    expected = EXPECTED_VALUES[1];
    assertHeapVal("Test 2: Second int is the next smallest", expected, actualRemoved);

    actualRemoved = myHeap.remove();
    expected = EXPECTED_VALUES[2];
    assertHeapVal("Test 3: Third int", expected, actualRemoved);

    actualRemoved = myHeap.remove();
    expected = EXPECTED_VALUES[3];
    assertHeapVal("Test 4: Last int", expected, actualRemoved);
}
/**
 * This is a test that tests the function upHeap be always called so that it can
 * catch any faults in the method.
 */
void evokeUpHeap() {
    cout << "Test 5: Reverse Order Insertion... ";
    Heap<int, less<int>> myHeap;
    const int MAX_HEAP_SIZE = 10;
    for (int i = MAX_HEAP_SIZE; i > 0; i--) {
        myHeap.add(i);
    }

    bool passed = true;
    for (int i = 1; i <= MAX_HEAP_SIZE; i++) {
        const int expected = i;
        const int actual = myHeap.remove();
        if (actual != expected) {
            cout << "[FAILED]\n Expected: " << expected << "\nActual: " << actual;
            passed = false;
        }
    }
    if(passed) {
        cout << "[PASSED UPHEAP]" << "\n";
        testsPassed++;
    } else {
        cout << "[FAILED UPHEAP]" << "\n";
    }
    totalTests++;
}
/**
 * This method tests duplicates and whether heap can correctly handle duplicates in the heap.
 */
void duplicates() {
    cout << "Test 6: Duplicate Values... ";
    Heap<int, less<int>> myHeap;
    myHeap.add(1); 
    myHeap.add(1); 
    myHeap.add(5); 
    myHeap.add(1);
    
    const bool PASSED = (myHeap.remove() == 1 && myHeap.remove() == 1 && myHeap.remove() == 1 && myHeap.remove() == 5);
    if(PASSED) {
        cout << "[PASSED DUPLICATES]" << "\n";
        testsPassed++;
    } else {
        cout <<  "[FAILED DUPLICATES]" << "\n";
    }
    totalTests++;
}
/**
 * Tests the heap using the FoodStuff class which bases the created functor for it.
 */
void foodCheapest() {
    cout << "Test 7: Foodstuff Cheapest Functor... ";
    Heap<Foodstuff, Cheapest> myHeap;
    // Constructor being weight then cost, 
    // Cost: 10, Weight: 10 -> CPP: 1.0
    // Cost: 10, Weight: 100 -> CPP: 0.1 (Winner)
    // Cost: 100, Weight: 10 -> CPP: 10.0
    myHeap.add(Foodstuff("Expensive", 10, 100));
    myHeap.add(Foodstuff("Mid", 10, 10));
    myHeap.add(Foodstuff("Cheapest", 100, 10)); 

    Foodstuff cheapest = myHeap.remove();
    const bool PASSED = (cheapest.name == "Cheapest");
    if(PASSED) {
        cout << "[PASSED CHEAPEST]" << "\n";
        testsPassed++;
    } else {
        cout <<  "[FAILED CHEAPEST]" << "\n";
    }
    totalTests++;
}
/**
 * Runs all of my tests and outputs which tests passed and how many.
 * It runs the tests for duplicates, reverse insertion that tests the upheap, 
 * simple int heap using the less comparator. Also, using the FoodStuff objs
 */
void runTests() {
    simpleTestInt();
    evokeUpHeap();
    duplicates();
    foodCheapest();
    cout << "[TESTS PASSED:] " << testsPassed << "/" << totalTests << "\n";
}

void makeHotDogs() {
    Rng rng(21324); 

    Heap<Foodstuff, Cheapest> h;
    vector<Foodstuff> ingredients;

    for(int i = 0; i < 10; i++) {
        while(h.size() < 10) {
            Foodstuff ingredient = getRandomFoodstuff(rng);
            h.add(ingredient);
        }
        ingredients.push_back(h.remove());
    }

    int totalCost = 0;
    int totalWeight = 0;
    for(Foodstuff ingredient : ingredients) {
        printf("%-12s - cost: %3d  weight: %3d  CostPerPound: %3f\n", ingredient.name.c_str(), ingredient.cost, ingredient.weight, ingredient.getCostPerPound());
        totalCost += ingredient.cost;
        totalWeight += ingredient.weight;
    }
    cout << "total cost:   " << totalCost << "\n";
    cout << "total weight: " << totalWeight << "\n";
}

int main() {
    runTests();
    makeHotDogs();
    return 0;
}
