#ifndef COUNTSORT_H
#define COUNTSORT_H

#include <initializer_list> // intializer_list

class CountSort {
  private:
    int *numbers = nullptr;
    const int lower_bound;
    const int upper_bound;
    const int range;
    int size_ = 0;
    // Checks if a number is within the specified range (inclusive)
    bool check_range(int, int, int) const;
  public:
    class Iterator {
      private:
        const CountSort &parent; // Pointer to a const CountSort not a const pointer
        int array_index;
        int element_index = 1;
      public:
        // Constructor
        Iterator(const CountSort &p, int ai = 0);
        // Copy constructor
        Iterator(const Iterator &rhs) = default;
        // Copy assignment operator
        Iterator operator =(const Iterator &rhs);
        // Destructor
        ~Iterator() = default;

        // Preincrement
        Iterator &operator ++();
        // Postincrement
        Iterator operator ++(int);
        // Operator *
        int operator *() const;
        // Operator ==
        bool operator ==(const Iterator &rhs) const;
        // Operator != 
        bool operator !=(const Iterator &rhs) const;
    };

    // Constructor
    // throws invalid_argument
    CountSort(int lower_bound = 0, int upper_bound = 99);
    // Initializer list assignment operator
    CountSort &operator =(const std::initializer_list<int> &);
    // Destructor
    ~CountSort();

    // Insert an item
    // throws out_of_range 
    void insert(int);

    // Operator (): Retrieve the nth raw count from the array of counts
    // throws out_of_range
    int operator ()(int) const;

    // Operator []: Retrieve the n th int from the object, in sorted order.
    // throws out_of_range
    int operator [](int) const;

    // Operator ==
    bool operator ==(const CountSort &) const;
 
    // Return the lower bound
    int min() const;
    // Return the upper bound
    int max() const;
    // Return the range
    int width() const;
    // Get the number of int values stored in the container
    int size() const;
    // Return true iff there are no values in this container
    bool empty() const;
    // Clear the container
    void clear();

    // Return a CountSort::Iterator that corresponds to the smallest int stored
    Iterator begin() const;
    // Return a CountSort::Iterator that corresponds one past the largest int stored
    Iterator end() const;

};

#endif /* COUNTSORT_H */
