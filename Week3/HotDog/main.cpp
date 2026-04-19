#include <iostream>
#include <string>
#include "rng.h"
#include "foodstuff.h"
#include "heap.h"   // TODO
#include "functors.h" // TODO

using std::cout;
using std::string;


// TODO:  implement heap class
// TODO:  implement Cheapest functor to prioritize queue of foodstuffs by lowest cost per weight

void runTests() {
    // TODO:  add some tests make sure the code actually works?

    Heap<int,std::less<int>> myHeap;
    myHeap.add(50);
    myHeap.add(30);
    myHeap.add(10);
    myHeap.add(5);
    int actualRemoved = myHeap.remove();
    int expected = 5;
    if(actualRemoved != expected) {
        cout << "[TEST FAILED] First should be 5" << "\nExpected: " << expected << "Actual: " << actualRemoved;
    } 
    actualRemoved = myHeap.remove();
    expected = 10;
    if(actualRemoved != expected) {
        cout << "[TEST FAILED] Next should be 10" << "\nExpected: " << expected << "Actual: " << actualRemoved;
    }
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
