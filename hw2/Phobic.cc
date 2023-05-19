#include "Phobic.h"

using std::set;

// Constructor
//
// Accepts zero or one arguments
// int currentValue (defaults to 0)
// 
// 13 will be regarded as scary
Phobic::Phobic(int value) : currentValue(value) {
    scaryNumbers.insert(13);
    updateCurrentValue();
}

// Copy constructor
//
// Copies all information from another object of the same class
// Includes: value and the scary numbers
Phobic::Phobic(const Phobic &rhs) : currentValue(rhs.get()),
                                    scaryNumbers(rhs.getScaryNumbers()) {}

// Assignment operator
//
// Copies all information from another object of the same class
// Includes: value and the scary numbers
// Returns a reference to the assigned object
Phobic &Phobic::operator=(const Phobic &rhs) {
    currentValue = rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return *this;
}

// Destructor
//
// Use default
Phobic::~Phobic() = default;

// Add the current object and another, yielding a third object with the expected value
// Fears all objects feared by either object
Phobic Phobic::add(const Phobic &rhs) const {
    Phobic resultPhobic(*this);
    resultPhobic.add_to(rhs);
    return resultPhobic;
}

// Subtract an object from the current object, yielding a third object with the expected value
// Fears all objects feared by either object
Phobic Phobic::sub(const Phobic &rhs) const {
    Phobic resultPhobic(*this);
    resultPhobic.sub_from(rhs);
    return resultPhobic;
}

// Multiply the current object and another, yielding a third object with the expected value
// Fears all objects feared by either object
Phobic Phobic::mul(const Phobic &rhs) const {
    Phobic resultPhobic(*this);
    resultPhobic.mul_by(rhs);
    return resultPhobic;
}

// Divide the current object by another, yielding a third object with the expected value
// Fears all objects feared by either object
//
// I was going to have this emit an error in case of division by 0 but I didn't
// know if that violated the "no output" requirement. So if user attempts to divide
// by zero, the function returns a new default-constructed Phobic object.
Phobic Phobic::div(const Phobic &rhs) const {
    if (rhs.get() == 0) {
        return Phobic();
    }
    Phobic resultPhobic(*this);
    resultPhobic.div_by(rhs);
    return resultPhobic;
}

// Add the current object and another, putting the result into the current object
// Current object will acquire fear of all scary values of argument object
// Returns the new value
int Phobic::add_to(const Phobic &rhs) {
    currentValue += rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return currentValue;
}

// Subtract an object from the current object, putting the result into the current object
// Current object will acquire fear of all scary values of argument object
// Returns the new value
int Phobic::sub_from(const Phobic &rhs) {
    currentValue -= rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return currentValue;
}

// Multiply the current object and another, putting the result into the current object
// Current object will acquire fear of all scary values of argument object
// Returns the new value
int Phobic::mul_by(const Phobic &rhs) {
    currentValue *= rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return currentValue;
}

// Divide the current object by another, putting the result into the current object
// Current object will acquire fear of all scary values of argument object
// Returns the new value
//
// I was going to have this emit an error in case of division by 0 but I didn't
// know if that violated the "no output" requirement. So if user attempts to divide
// by zero, the function does nothing and returns the current value.
int Phobic::div_by(const Phobic &rhs) {
    if (rhs.get() == 0) {
        return currentValue;
    }
    currentValue /= rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return currentValue;
}

// Returns true iff the value in the current object equals the value in the argument
bool Phobic::eq(const Phobic &rhs) const {
    return currentValue == rhs.get();
}

// Returns true iff the value in the current object is less than the value in the argument
bool Phobic::lt(const Phobic &rhs) const {
    return currentValue < rhs.get();
}

// Returns the current value
int Phobic::get() const {
    return currentValue;
}

// Returns the set of scary numbers
const std::set<int> &Phobic::getScaryNumbers() const {
    return scaryNumbers;
}

// Adds integers to the set of scary numbers
// Returns new value
int Phobic::make_scary(int n1, int n2, int n3, int n4, int n5,
                       int n6, int n7, int n8, int n9, int n10) {
    scaryNumbers.insert({n1, n2, n3, n4, n5,
                         n6, n7, n8, n9, n10});
    updateCurrentValue();
    return currentValue;
}

// Returns true iff the object fears the argument
bool Phobic::is_scary(int val) const {
    return scaryNumbers.count(val);
}

// Private helper
// Increments the current value until it is not scary
void Phobic::updateCurrentValue() {
    while (scaryNumbers.find(currentValue) != scaryNumbers.end()) {
        ++currentValue;
    }
}








