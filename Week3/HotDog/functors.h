#pragma once 
#include "foodstuff.h"

/**
 * This structure implements the cheapest comparator for the 
 * foodstuff by costperpound
 */
struct Cheapest {
    /**
     * Returns if a is cheaper than b, a being the first item if it is cheaper than the 
     * second item.
     */
    bool operator()(const Foodstuff& a, const Foodstuff& b){
        return a.getCostPerPound() < b.getCostPerPound();
    }
};