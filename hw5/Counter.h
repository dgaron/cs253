#ifndef COUNTER_H
#define COUNTER_H

#include <string>

class Counter {
  public:
    // Constructor
    Counter(int lowerBound = 0, int upperBound = 99);
    // Copy constructor
    Counter(const Counter &);
    // Copy assignment operator
    Counter &operator =(const Counter &);
    // Destructor
    ~Counter();

    // Get the size
    int getSize() const;
    // Get the lower bound
    int getLB() const;
    // Get the upper bound
    int getUB() const;
    // Get the numbers array
    const int *getNumbers() const;

    // Indexing operators
    int operator [](int) const;

    // Add an item
    void add(int);

    // Print numbers in NxQ format
    // N is the number
    // Q is the count
    void printNxQ() const;

    // Print numbers in NQTimes format
    // N is the number
    // Number is printed Q times
    // Separated by sep string
    //   default is comma
    void printNQTimes(const std::string &) const;

  private:
    int *numbers = nullptr;
    int lowerBound;
    int upperBound;
    int size;
};

#endif
