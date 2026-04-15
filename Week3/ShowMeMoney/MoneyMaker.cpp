#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;
/**
 * Provided class for the assignment.
 */
class SalesLead {
    public:
        string name;
        int income;
        SalesLead(const string& theName, int theIncome) : name(theName), income(theIncome) {}
};
/**
 * This is a wrapper for the Priority queue to make the std::priority_queue stable 
 * this is because the std::priority queue is not 
 * stable and cannot hold a FIFO, since it could get lost. Basically this holds the nessary data
 * to keep track of the priority.
 */
struct PQItem {
    // The wrapper needs the object and the seqo it entered in
    public:
        SalesLead myLead;
        int seqno;
        // Constructor for the wrapper class
        PQItem(SalesLead inLead, int mySeqno) : myLead(std::move(inLead)), seqno(mySeqno) {}
};

/**
 * This is the custom comparator, that is used to compare the sales leads.
 * Income is priority followed by who was there first.
 */
class SalesComparator {
    public:
        // Priority over income, then whoever has been in the queue first.
        // so if this->income < that->income, return?
        // the second one would be on sequence added
        bool operator()(const PQItem& first, const PQItem& second) {
            // This is if the values are not equal to each other
            if(first.myLead.income != second.myLead.income) {
                return first.myLead.income < second.myLead.income;
            }
            // if they are equal then we compare the longest they were there
            return second.seqno < first.seqno;

        }
};
/**
 * This will test the functionality of the priority queue.
 */
void testMyMoney() {
    priority_queue<PQItem, vector<PQItem>, SalesComparator> leadQueue;
    int currentSeq = 0;
    // Push/enqueue to the queue
    leadQueue.push(PQItem(SalesLead("Jamaaa", 3000),currentSeq++));
    //Bella should be first 
    leadQueue.push(PQItem(SalesLead("Bella", 20000),currentSeq++));
    // Assertions to make sure the priority queue is correct.
    assert(leadQueue.top().myLead.name == "Bella");
    leadQueue.pop();
    assert(leadQueue.top().myLead.name == "Jamaaa");
    leadQueue.pop();

    currentSeq = 0;
    leadQueue.push(PQItem(SalesLead("Yolla", 3000),currentSeq++));
    leadQueue.push(PQItem(SalesLead("Michale", 3000),currentSeq++));
    assert(leadQueue.top().myLead.name == "Yolla");
    while(!leadQueue.empty()) {
        const PQItem curr = leadQueue.top();
        cout << curr.myLead.name << " and " << curr.myLead.income;
        cout << "\nArrived: " << curr.seqno << "\n";
        leadQueue.pop();
    }
    currentSeq = 0;
    cout << "\nSECOND TEST\n------------------------------------\n";
    leadQueue.push(PQItem(SalesLead("Kevin Hart", 9000),currentSeq++));
    leadQueue.push(PQItem(SalesLead("Freddy Kruger", 4500),currentSeq++));
    leadQueue.push(PQItem(SalesLead("Luke Skywalker", 5000),currentSeq++));
    leadQueue.push(PQItem(SalesLead("JOJO!", 100000),currentSeq++));
    while(!leadQueue.empty()) {
        const PQItem curr = leadQueue.top();
        cout << curr.myLead.name << " and " << curr.myLead.income;
        cout << "\nArrived: " << curr.seqno << "\n";
        leadQueue.pop();
    }
    cout << "ALL TESTS PASSED\n";

}

int main() {
    // Tests 
    testMyMoney();
}