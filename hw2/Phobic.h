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

    // Add the current object and another, yielding a third object with the expected value
    // Fears all objects feared by either object
    Phobic add(const Phobic &) const;
    // Subtract the current object and another, yielding a third object with the expected value
    // Fears all objects feared by either object
    Phobic sub(const Phobic &) const;
    // Multiply the current object and another, yielding a third object with the expected value
    // Fears all objects feared by either object
    Phobic mul(const Phobic &) const;
    // Divide the current object and another, yielding a third object with the expected value
    // Fears all objects feared by either object
    Phobic div(const Phobic &) const;

    // Add the current object and another, putting the result into the current object
    // Current object will acquire fear of all scary values of argument object
    // Returns the new value
    int add_to(const Phobic &);
    // Subtract the current object and another, putting the result into the current object
    // Current object will acquire fear of all scary values of argument object
    // Returns the new value
    int sub_from(const Phobic &);
    // Multiply the current object and another, putting the result into the current object
    // Current object will acquire fear of all scary values of argument object
    // Returns the new value
    int mul_by(const Phobic &);
    // Divide the current object and another, putting the result into the current object
    // Current object will acquire fear of all scary values of argument object
    // Returns the new value
    int div_by(const Phobic &);

    // Returns true iff the value in the current object equals the value in the argument
    bool eq(const Phobic &) const;

    // Returns true iff the value in the current object is less than the value in the argument
    bool lt(const Phobic &) const;

    // Returns the int value associated with this object
    int get() const;

    // Returns the set of scary numbers associated with this object
    const std::set<int> &getScaryNumbers() const;

    // Adds integers to the set of scary numbers
    // Returns new value
    int make_scary(int, int n2 = 13, int n3 = 13, int  n4 = 13, int n5 = 13, 
                   int n6 = 13, int n7 = 13, int n8 = 13, int n9 = 13, int n10 = 13);

    // Returns true iff the object fears the argument
    bool is_scary(int) const;

  private:
    int currentValue;
    std::set<int> scaryNumbers;

    // Increments the current value until it is not scary
    void updateCurrentValue();
};

#endif /* PHOBIC_H */
