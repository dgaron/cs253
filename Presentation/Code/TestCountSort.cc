#include <iostream>
#include <string>
#include <cassert>  // assert()
#include <limits>   // UINT_MAX, ULONG_MAX
#include "CountSort.h"

using namespace std;

void test_constructor() {
    cout << "Testing CountSort constructor" << '\n';
    cout << "Constructor throws std::invalid_exception when upper bound < lower bound" << '\n';
    cout << '\n';
    try {
        CountSort cs(99, 0);
    } catch (const invalid_argument &e) {
        cout << "CountSort object creation failed with invalid range [99 - 0]" << '\n';
        cout << "Error message produced: " << e.what() << '\n';
    }
    cout << '\n';
    CountSort cs(-100, 100);
    cout << "CountSort object creation succeeded with valid range [-100 - 100]" << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_insert() {
    cout << "Testing insert()" << '\n';
    cout << "insert() throws std::out_of_range when n is outside of allowable range" << '\n';
    CountSort cs(10, 99);
    cout << '\n';
    try {
        cs.insert(100);
    } catch (const out_of_range &e) {
        cout << "Insertion failed for 100 with range [10 - 99]" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << '\n';
    cs.insert(10);
    assert(cs(0) == 1);
    cout << "Insertion succeeded for 0 with range [10 - 99]" << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_copy_constructor() {
    cout << "Testing CountSort copy constructor" << '\n';
    CountSort cs1(0, 99);
    cs1 = {99, 99, 99};
    // CountSort cs2(cs1);
    CountSort cs2 = cs1;
    cout << "Successfully copied CountSort object:" << '\n';
    cout << "cs1: " << cs1  << '\n';
    cout << "cs2: " << cs2  << '\n';
    assert(cs1.size() == cs2.size());
    cout << "cs1.size() expected return: 3 -- actual: " << cs1.size() << '\n';
    cout << "cs2.size() expected return: 3 -- actual: " << cs2.size() << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_min_max() {
    CountSort cs(0, 99);
    cout << "Testing min()" << '\n';
    cout << "min() returns the lower bound" << '\n';
    assert(cs.min() == 0);
    cout << "min() expected return: 0 -- actual: " << cs.min() << '\n';
    cout << '\n';
    cout << "Testing max()" << '\n';
    cout << "max() returns the upper bound" << '\n';
    assert(cs.max() == 99);
    cout << "max() expected return: 99 -- actual: " << cs.max() << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_width() {
    cout << "Testing width()" << '\n';
    cout << "width() returns the how many different int values the object can hold" << '\n';
    CountSort cs(-100, 100);
    assert(cs.width() == 201);
    cout << "width() expected return: 201 -- actual: " << cs.width() << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_size() {
    cout << "Testing size()" << '\n';
    cout << "size() returns the number of int values stored in the container" << '\n';
    CountSort cs(0, 99);
    cs.insert(10);
    cs.insert(10);
    cs.insert(10);
    assert(cs.size() == 3);
    cout << "size() expected return: 3 -- actual: " << cs.size() << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_clear_empty() {
    cout << "Testing clear() & empty()" << '\n';
    cout << "clear() empties the container" << '\n';
    cout << "empty() returns true iff there are no values in the container" << '\n';
    CountSort cs(0, 99);
    cs = {10, 10, 10};
    assert(cs.empty() == false);
    assert(cs.size() == 3);
    cout << "Before clear(), size() expected return: 3 -- actual: " << cs.size() << '\n';
    cout << "Before clear(), empty() expected return: false -- actual: " << boolalpha << cs.empty() << '\n';
    cs.clear();
    assert(cs.size() == 0);
    assert(cs.empty() == true);
    cout << "After clear(), size() expected return: 0 -- actual: " << cs.size() << '\n';
    cout << "After clear(), empty() expected return: true -- actual: " << cs.empty() << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_assignment_operator_cs() {
    cout << "Testing assignment operator" << '\n';
    cout << "Assignment operator implemented for const CountSort &" << '\n';
    CountSort cs1(0, 99);
    cout << '\n';
    try {
        CountSort cs2(0, 49);
        cs1 = cs2;
    } catch (const range_error &e) {
        cout << "Assignment fails when rhs object has different bounds" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << '\n';
    CountSort cs2(0, 99);
    cs2 = {10, 10, 10};
    cs1 = cs2;
    cout << "Successfully assigned CountSort object to CountSort object with same bounds:" << '\n';
    cout << "cs1: " << cs1 << '\n';
    cout << "cs2: " << cs2 << '\n';
    assert(cs1.size() == cs2.size());
    cout << "cs1.size() expected return: 3 -- actual: " << cs1.size() << '\n';
    cout << "cs2.size() expected return: 3 -- actual: " << cs2.size() << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_assignment_operator_il() {
    cout << "Testing assignment operator" << '\n';
    cout << "Assignment operator implemented for std::initializer_list<int>" << '\n';
    CountSort cs(0, 99);
    cout << '\n';
    try {
        cs = {1, 2, 100};
    } catch (const out_of_range &e) {
        cout << "Assignment fails when initializer_list contains invalid entries" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << '\n';
    cs = {0, 1, 2, 2, 99};
    cout << "Successfully assigned std::initializer_list<int> to CountSort object" << '\n';
    cout << "Expected: 0, 1, 2, 2, 99" << '\n';
    cout << "Actual:   " << cs << '\n';
    assert(cs.size() == 5);
    cout << "cs.size() expected return: 5 -- actual: " << cs.size() << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_il_constructor() {
    cout << "Testing initializer_list constructor" << '\n';
    cout << "Constructor implemented for std::initializer_list<int>" << '\n';
    CountSort cs = {0, 1, 2, 2, 99};
    cout << "Successfully constructed CountSort object from std::initializer_list<int>" << '\n';
    cout << "Expected: 0, 1, 2, 2, 99" << '\n';
    cout << "Actual:   " << cs << '\n';
    assert(cs.size() == 5);
    cout << "cs.size() expected return: 5 -- actual: " << cs.size() << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_call_operator() {
    cout << "Testing operator()" << '\n';
    cout << "operator() returns the nth raw count from the array of counts" << '\n';
    CountSort cs(0, 99);
    cs = {1, 1, 1};
    cout << '\n';
    try {
        cout << cs(100) << '\n';
    } catch (const out_of_range &e) {
        cout << "operator() fails when user requests an index < 0 or >= width" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << '\n';
    assert(cs(0) == 0);
    assert(cs(1) == 3);
    cout << "cs(0) expected return: 0 -- actual: " << cs(0) << '\n';
    cout << "cs(1) expected return: 3 -- actual: " << cs(1) << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_subscript_operator() {
    cout << "Testing operator[]" << '\n';
    cout << "operator[] returns the nth int from the object, in sorted order" << '\n';
    CountSort cs(0, 99);
    cs = {1, 1, 99, 99, 99};
    cout << '\n';
    try {
        cout << cs[5] << '\n';
    } catch (const out_of_range &e) {
        cout << "operator[] fails when user requests an index < 0 or >= size" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << '\n';
    assert(cs[0] == 1);
    assert(cs[1] == 1);
    assert(cs[2] == 99);
    assert(cs[3] == 99);
    assert(cs[4] == 99);
    cout << "cs[0] expected return: 1 -- actual: " << cs[0] << '\n';
    cout << "cs[1] expected return: 1 -- actual: " << cs[1] << '\n';
    cout << "cs[2] expected return: 99 -- actual: " << cs[2] << '\n';
    cout << "cs[3] expected return: 99 -- actual: " << cs[3] << '\n';
    cout << "cs[4] expected return: 99 -- actual: " << cs[4] << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_iterator_constructor_increment() {
    cout << "Testing Iterator constructor & operator++" << '\n';
    CountSort cs(0, 99);
    cs = {1, 1, 29};
    auto it = cs.begin();
    assert(*it == 1);
    cout << "*it expected return: 1 -- actual: " << *it << '\n';
    ++it;
    assert(*it == 1);
    cout << "*it expected return: 1 -- actual: " << *it << '\n';
    ++it;
    assert(*it == 29);
    cout << "*it expected return: 29 -- actual: " << *it << '\n';
    ++it;
    cout << '\n';
    try {
        ++it;
    } catch (const out_of_range &e) {
        cout << "Iterator::operator++ fails when attempting increment past end()" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << "------------------------------------------------------------------------\n";
}

void test_iterator_equality_dereference() {
    cout << "Testing Iterator::operator==, operator!=, & operator*" << '\n';
    CountSort cs(0, 99);
    cs = {1, 1, 29};
    auto it1 = cs.begin();
    auto it2 = cs.end();
    assert(it1 != it2);
    cout << "it1 == it2 expected return: false -- actual: " << boolalpha << (it1 == it2) << '\n';
    cout << "it1 != it2 expected return: true -- actual: " << boolalpha << (it1 != it2) << '\n';
    cout << "Incrementing it1 to end: " << cs.size() << '\n';
    for (unsigned int i = 0; i < cs.size(); ++i) {
        ++it1;
    }
    assert(it1 == it2);
    cout << "it1 == it2 expected return: true -- actual: " << boolalpha << (it1 == it2) << '\n';
    cout << '\n';
    try {
        cout << *it1 << '\n';
    } catch (const out_of_range &e) {
        cout << "Iterator::operator* fails when attempting to dereference exhausted iterator" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << "------------------------------------------------------------------------\n";
}

void test_for_each_loop() {
    cout << "Testing for each loop" << '\n';
    CountSort cs = {1, 1, 1, 3, 3, 3, 99};
    cout << "for (auto n : cs) { cout << n; } // basically" << '\n';
    cout << "Expected: 1, 1, 1, 3, 3, 3, 99" << '\n';
    cout << "Actual:   ";
    string sep = "";
    for (auto n : cs) {
        cout << sep << n;
        sep = ", ";
    }
    cout << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_iterator_decrement() {
    cout << "Testing Iterator::operator--" << '\n';
    CountSort cs(1, 99);
    cs = {1, 1, 29};
    auto it = cs.end();
    --it;
    assert(*it == 29);
    cout << "*it expected return: 29 -- actual: " << *it << '\n';
    --it;
    assert(*it == 1);
    cout << "*it expected return: 1 -- actual: " << *it << '\n';
    --it;
    assert(*it == 1);
    cout << "*it expected return: 1 -- actual: " << *it << '\n';
    cout << '\n';
    try {
        --it;
        cout << *it << '\n';
    } catch (const out_of_range &e) {
        cout << "Iterator::operator-- fails when attempting to decrement past begin()" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << "------------------------------------------------------------------------\n";
}

void test_iterator_plus_equals() {
    cout << "Testing Iterator::operator+= & Iterator::operator-=" << '\n';
    CountSort cs(0, 99);
    cs = {1, 1, 29};
    auto it = cs.begin();
    assert(*it == 1);
    cout << "*it expected return: 1 -- actual: " << *it << '\n';
    it += 2;
    assert(*it == 29);
    cout << "it += 2; *it expected return: 29 -- actual: " << *it << '\n';
    it -= 2;
    assert(*it == 1);
    cout << "it -= 2; *it expected return: 1 -- actual: " << *it << '\n';
    cout << '\n';
    try {
        it += 5;
    } catch (const out_of_range &e) {
        cout << "operator+ fails when attempting increment past end()" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }    
    cout << '\n';
    try {
        it -= 5;
        cout << *it << '\n';
    } catch (const out_of_range &e) {
        cout << "operator- fails when attempting to decrement past begin()" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << "------------------------------------------------------------------------\n";
}

void test_iterator_add_subtract() {
    cout << "Testing operator+ & operator-" << '\n';
    CountSort cs(0, 99);
    cs = {1, 1, 29};
    auto it = cs.begin();
    assert(*it == 1);
    cout << "*it expected return: 1 -- actual: " << *it << '\n';
    it = it + 2;
    assert(*it == 29);
    cout << "it = it + 2; *it expected return: 29 -- actual: " << *it << '\n';
    it = it - 2;
    assert(*it == 1);
    cout << "it = it - 2; *it expected return: 1 -- actual: " << *it << '\n';
    it = 2 + it;
    assert(*it == 29);
    cout << "it = 2 + it; *it expected return: 29 -- actual: " << *it << '\n';
    cout << '\n';
    try {
        it = it + 5;
    } catch (const out_of_range &e) {
        cout << "operator+ fails when attempting increment past end()" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }    
    cout << '\n';
    try {
        it = it - 5;
        cout << *it << '\n';
    } catch (const out_of_range &e) {
        cout << "operator- fails when attempting to decrement past begin()" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }
    cout << "------------------------------------------------------------------------\n";
}

void test_iterator_subscript() {
    cout << "Testing Iterator::operator[]" << '\n';
    cout << "operator[] returns the nth int from the object, in sorted order" << '\n';
    CountSort cs {1, 1, 2, 2, 99};
    auto it = cs.begin();
    cout << '\n';
    try {
        cout << it[5] << '\n';
    } catch (const out_of_range &e) {
        cout << "operator[] fails when user requests an index < 0 or >= size" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    } catch (const invalid_argument &e) {
        cout << "operator[] fails when user requests a negative index" << '\n';
        cout << "Error message produced: " << e.what() << '\n';   
    }  
    cout << '\n';
    assert(it[0] == 1);
    assert(it[1] == 1);
    assert(it[2] == 2);
    assert(it[3] == 2);
    assert(it[4] == 99);
    cout << "it[0] expected return: 1 -- actual: " << it[0] << '\n';
    cout << "it[1] expected return: 1 -- actual: " << it[1] << '\n';
    cout << "it[2] expected return: 2 -- actual: " << it[2] << '\n';
    cout << "it[3] expected return: 2 -- actual: " << it[3] << '\n';
    cout << "it[4] expected return: 99 -- actual: " << it[4] << '\n';
    cout << "------------------------------------------------------------------------\n";
}

void test_iterator_difference() {
    cout << "Testing operator-(const Iterator &, const Iterator &)" << '\n';
    CountSort cs {1, 1, 1, 9, 9, 9};
    auto d = cs.end() - cs.begin();
    assert(d == 6);
    cout << "cs.end() - cs.begin() expected value: 6 -- actual: " << d << '\n';
    d = cs.begin() - cs.end();
    assert(d == -6);
    cout << "cs.begin() - cs.end() expected value: -6 -- actual: " << d << '\n';
    d = std::distance(cs.begin(), cs.begin() + 4);
    assert(d == 4);
    cout << "std::distance(cs.begin(), cs.begin() + 4) expected value: 4 -- actual: " << d << '\n';
    cout << "------------------------------------------------------------------------\n";
}


int main() {

    cout << '\n';
    cout << "Running CountSort Tests ..." << '\n';
    cout << "------------------------------------------------------------------------\n";

    test_constructor();
    test_insert();
    test_copy_constructor();
    test_min_max();
    test_width();
    test_size();
    test_clear_empty();
    test_assignment_operator_cs();
    test_assignment_operator_il();
    test_il_constructor();
    test_call_operator();
    test_subscript_operator();
    test_iterator_constructor_increment();
    test_iterator_equality_dereference();
    test_for_each_loop();
    test_iterator_decrement();
    test_iterator_plus_equals();
    test_iterator_add_subtract();
    test_iterator_subscript();
    test_iterator_difference();

    cout << "All tests completed successfully" << '\n';

    return 0;
}