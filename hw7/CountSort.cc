#include <string> // to_string
#include <stdexcept> // exceptions

#include "CountSort.h"

using namespace std;

// Constructor
CountSort::CountSort(int lb, int ub) : lower_bound(lb), upper_bound(ub), range(ub - lb + 1) {
    if (ub < lb) {
        throw invalid_argument("Error: " + to_string(ub) + " < " + to_string(lb) + ". Please specify (lower_bound, upper_boud)");
    }
    numbers = new int[range]{0};
}
// Initializer list assignment operator
CountSort &CountSort::operator =(const initializer_list<int> &il) {
    clear();
    for (auto n : il) {
        insert(n);
    }
    return *this;
}

// Destructor
CountSort::~CountSort() {
    delete[] numbers;
}

// Checks if a number is within the specified range (inclusive)
// throws out_of_range 
bool CountSort::check_range(int n, int lower, int upper) const {
    if (n < lower || n > upper) {
        throw out_of_range(to_string(n) + " is outside of acceptable range [" +
                           to_string(lower) + "-" + to_string(upper) + "]");
    }
    return true;
}

// Insert an item
void CountSort::insert(int n) {
    check_range(n, lower_bound, upper_bound);
    ++numbers[n - lower_bound]; 
    ++size_;
}

// Operator (): Retrieve the nth raw count from the array of counts
int CountSort::operator ()(int n) const {
    check_range(n, 0, range - 1);
    return numbers[n];
}

// Operator []: Retrieve the n th int from the object, in sorted order.
int CountSort::operator [](int n) const {
    if (size_ == 0) {
        throw out_of_range("attempting to access an empty object"); 
    } else if (n >= size_) {
        throw out_of_range(to_string(n) + " is outside of the acceptable range [0" +
                        "-" + to_string(size_ - 1) + "] for object of size " + to_string(size_));
    }
    Iterator it = begin();
    for (int i = 0; i < n; ++i) {
        ++it;
    }
    return *it;
}

// Operator ==
bool CountSort::operator ==(const CountSort &rhs) const {
    return numbers == rhs.numbers;
}

// Return the lower bound
int CountSort::min() const {
    return lower_bound;
}
// Return the upper bound
int CountSort::max() const {
    return upper_bound;
}
// Return the range
int CountSort::width() const {
    return range;
}
// Get the number of int values stored in the container
int CountSort::size() const {
    return size_;
    /* 
    int numItems = 0;
    for (int i = 0; i < range; ++i) {
        if (numbers[i]) {
            numItems += numbers[i];
        }
    }
    return numItems;
    */
}
// Return true iff there are no values in this container
bool CountSort::empty() const {
    if (size_) {
        return false;
    } else {
        return true;
    }
    /*
    for (int i = 0; i < range; ++i) {
        if (numbers[i]) {
            return false;
        }
    }
    return true;
    */
}
// Clear the container
void CountSort::clear() {
    for (int i = 0; i < range; ++i) {
        numbers[i] = 0;
    }
    size_ = 0;
}

// Return a CountSort::Iterator that corresponds to the smallest int stored
CountSort::Iterator CountSort::begin() const {
    return CountSort::Iterator(this);
}
// Return a CountSort::Iterator that corresponds one past the largest int stored
CountSort::Iterator CountSort::end() const {
    return CountSort::Iterator(this, range);
}

// Iterator implementation

// Constructor
CountSort::Iterator::Iterator(const CountSort *p, int ai) : parent(p), array_index(ai) {
    while (array_index < parent->range && !parent->numbers[array_index]) {
        ++array_index;
    }
}

// Preincrement
CountSort::Iterator &CountSort::Iterator::operator ++() {
    if (element_index < parent->numbers[array_index]) {
        ++element_index;
        return *this;
    }
    if (array_index >= parent->range) {
        throw std::out_of_range("Attempt to increment Iterator past end()");
    }
    do {
        ++array_index;
    } while (array_index < parent->range && !parent->numbers[array_index]);
    element_index = 1;
    return *this;
}
// Postincrement
CountSort::Iterator CountSort::Iterator::operator ++(int) {
    const auto save = *this;
    ++*this;
    return save;
}
// Operator *
int CountSort::Iterator::operator *() const {
    return array_index + parent->lower_bound;
}
// Operator ==
bool CountSort::Iterator::operator ==(const CountSort::Iterator &rhs) const {
    return parent == rhs.parent && array_index == rhs.array_index &&
            element_index == rhs.element_index;
}
// Operator != 
bool CountSort::Iterator::operator !=(const CountSort::Iterator &rhs) const {
    return !(*this == rhs);
}


