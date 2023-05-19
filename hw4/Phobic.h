#ifndef PHOBIC_H
#define PHOBIC_H

#include <set>

class Phobic {
  public:
    // Constructor
    Phobic(int value = 0);
    // Copy constructor
    Phobic(const Phobic &);
    // Assignment operator
    Phobic &operator=(const Phobic &);
    // Destructor
    ~Phobic();

    // Add the current object and another, putting the result into the current object
    // Current object will acquire fear of all scary values of argument object
    // Returns the new value
    Phobic &operator +=(const Phobic &);

    // Subtract the current object and another, putting the result into the current object
    // Current object will acquire fear of all scary values of argument object
    // Returns the new value
    Phobic &operator -=(const Phobic &);

    // Multiply the current object and another, putting the result into the current object
    // Current object will acquire fear of all scary values of argument object
    // Returns the new value
    Phobic &operator *=(const Phobic &);

    // Divide the current object and another, putting the result into the current object
    // Current object will acquire fear of all scary values of argument object
    // Returns the new value
    Phobic &operator /=(const Phobic &);

    // Returns the int value associated with this object
    [[nodiscard]] int get() const;

    // Returns the set of scary numbers associated with this object
    [[nodiscard]] const std::set<int> &getScaryNumbers() const;

    // Adds integers to the set of scary numbers
    // Returns new value
    Phobic &operator <<(int);

    // Returns true iff the object fears the argument
    [[nodiscard]] bool is_scary(int) const;

  private:
    int currentValue;
    std::set<int> scaryNumbers;

    // Increments the current value until it is not scary
    void updateCurrentValue();
};

// Add the current object and another, yielding a third object with the expected value
// Fears all objects feared by either object
[[nodiscard]] Phobic operator +(const Phobic &, const Phobic &);

// Subtract the current object and another, yielding a third object with the expected value
// Fears all objects feared by either object
[[nodiscard]] Phobic operator -(const Phobic &, const Phobic &);

// Multiply the current object and another, yielding a third object with the expected value
// Fears all objects feared by either object
[[nodiscard]] Phobic operator *(const Phobic &, const Phobic &);

// Divide the current object and another, yielding a third object with the expected value
// Fears all objects feared by either object
[[nodiscard]] Phobic operator /(const Phobic &, const Phobic &);

// Returns true iff the value in the current object equals the value in the argument
[[nodiscard]] bool operator ==(const Phobic &, const Phobic &);

// Returns true iff the value in the current object is not equal to the value in the argument
[[nodiscard]] bool operator !=(const Phobic &, const Phobic &);

// Returns true iff the value in the current object is less than the value in the argument
[[nodiscard]] bool operator <(const Phobic &, const Phobic &);

// Returns true iff the value in the current object is greater than the value in the argument
[[nodiscard]] bool operator >(const Phobic &, const Phobic &);

// Returns true iff the value in the current object is less than or equal to 
// the value in the argument
[[nodiscard]] bool operator <=(const Phobic &, const Phobic &);

// Returns true iff the value in the current object is greater than or equal to
// the value in the argumentt
[[nodiscard]] bool operator >=(const Phobic &, const Phobic &);

#endif /* PHOBIC_H */
