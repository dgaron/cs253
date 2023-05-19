#include "Counter.h"

#include <algorithm> // for copy
#include <iostream> // for print functions

using namespace std;

// Constructor
Counter::Counter(int lb, int ub) : lowerBound(lb), upperBound(ub), size(ub - lb + 1) {
    numbers = new int[size]{0};
}
// Copy constructor
Counter::Counter(const Counter &rhs) : Counter(rhs.getLB(), rhs.getUB()) {
   *this = rhs;
} 
// Copy assignment operator
Counter &Counter::operator =(const Counter &rhs) {
    if (this != &rhs) {
        // Allocate and copy numbers array
        delete[] numbers;
        numbers = new int[rhs.getSize()];
        copy(rhs.getNumbers(), rhs.getNumbers() + rhs.getSize(), numbers); 
        // Copy scalars
        size = rhs.getSize();
        lowerBound = rhs.getLB();
        upperBound = rhs.getUB();
    }
    return *this;
}
// Destructor
Counter::~Counter() {
    delete[] numbers;
}

// Get the size
int Counter::getSize() const {
    return size;
}
// Get the lower bound
int Counter::getLB() const {
    return lowerBound;
}
// Get the upper bound
int Counter::getUB() const {
    return upperBound;
}
// Get the numbers
const int *Counter::getNumbers() const {
    return numbers;
}

// Access with bracket notation
int Counter::operator [](int i) const {
    return numbers[i];
}

// Add an item
void Counter::add(int n) {
    ++numbers[n - lowerBound];
}

// Print in NxQ format
void Counter::printNxQ() const {
    string separator = "";
    for (int i = 0; i < size; ++i) {
        if (!numbers[i]) {
            continue;
        }
        // Add lower bound to i to correct for possible non-zero lower bound
        cout << separator << (i + lowerBound)<< 'x' << numbers[i];
        separator = " ";
    }
    cout << '\n';
}

// Print in N Q times format
// separator is a comma by default
void Counter::printNQTimes(const string &sep) const {
    string separator = "";
    for (int i = 0; i < size; ++i) {
        if(!numbers[i]) {
            continue;
        }
        for (int j = 0; j < numbers[i]; ++j) {
            // Add lower bound to i to correct for possible non-zero lower bound
            cout << separator << (i + lowerBound);
            separator = sep;
        }
    }
    cout << '\n';
}

