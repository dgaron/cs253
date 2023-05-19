#include "Phobic.h"
#include <stdexcept>

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
Phobic operator +(const Phobic &lhs, const Phobic &rhs) {
    Phobic resultPhobic(lhs);
    resultPhobic += rhs;
    return resultPhobic;
}

// Subtract an object from the current object, yielding a third object with the expected value
// Fears all objects feared by either object
Phobic operator -(const Phobic &lhs, const Phobic &rhs) {
    Phobic resultPhobic(lhs);
    resultPhobic -= rhs;
    return resultPhobic;
}

// Multiply the current object and another, yielding a third object with the expected value
// Fears all objects feared by either object
Phobic operator *(const Phobic &lhs, const Phobic &rhs) {
    Phobic resultPhobic(lhs);
    resultPhobic *= rhs;
    return resultPhobic;
}

// Divide the current object by another, yielding a third object with the expected value
// Fears all objects feared by either object
// 
// /= operator throws runtime_error in the case of attempted division by 0
Phobic operator /(const Phobic &lhs, const Phobic &rhs) {
    Phobic resultPhobic(lhs);
    resultPhobic /= rhs;
    return resultPhobic;
}

// Add the current object and another, putting the result into the current object
// Current object will acquire fear of all scary values of argument object
// Returns the new value
Phobic &Phobic::operator +=(const Phobic &rhs) {
    currentValue += rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return *this;
}

// Subtract an object from the current object, putting the result into the current object
// Current object will acquire fear of all scary values of argument object
// Returns the new value
Phobic &Phobic::operator -=(const Phobic &rhs) {
    currentValue -= rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return *this;
}

// Multiply the current object and another, putting the result into the current object
// Current object will acquire fear of all scary values of argument object
// Returns the new value
Phobic &Phobic::operator *=(const Phobic &rhs) {
    currentValue *= rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return *this;
}

// Divide the current object by another, putting the result into the current object
// Current object will acquire fear of all scary values of argument object
// Returns the new value
//
// Throws runtime_error in the case of attempted division by 0
Phobic &Phobic::operator /=(const Phobic &rhs) {
    if (rhs.get() == 0) {
        throw std::runtime_error("Error: division by zero is undefined\n" +
                                 std::to_string(currentValue) + "/0");
    }
    currentValue /= rhs.get();
    scaryNumbers.insert(rhs.getScaryNumbers().begin(), rhs.getScaryNumbers().end());
    updateCurrentValue();
    return *this;
}

// Returns true iff the value in the current object equals the value in the argument
bool operator ==(const Phobic &lhs, const Phobic &rhs) {
    return lhs.get() == rhs.get();
}

// Returns true iff the value in the current object is not equal to the value in the argument
bool operator !=(const Phobic &lhs, const Phobic &rhs) {
    return !(lhs == rhs);
}

// Returns true iff the value in the current object is less than the value in the argument
bool operator <(const Phobic &lhs, const Phobic &rhs) {
    return lhs.get() < rhs.get();
}

// Returns true iff the value in the current object is greater than the value in the argument
bool operator >(const Phobic &lhs, const Phobic &rhs) {
    return lhs.get() > rhs.get();
}

// Returns true iff the value in the current object is less than or equal to 
// the value in the argument
bool operator <=(const Phobic &lhs, const Phobic &rhs) {
    return !(lhs > rhs);
}

// Returns true iff the value in the current object is greater than or equal to
// the value in the argument
bool operator >=(const Phobic &lhs, const Phobic &rhs) {
    return !(lhs < rhs);
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
// Returns a reference to this object
Phobic &Phobic::operator <<(int rhs) {
    scaryNumbers.insert(rhs);
    updateCurrentValue();
    return *this;
}

// Returns true iff the object fears the argument
bool Phobic::is_scary(int val) const {
    return scaryNumbers.count(val);
}

// Private helper
// Increments the current value until it is not scary
void Phobic::updateCurrentValue() {
    while (is_scary(currentValue)) {
        ++currentValue;
    }
}








