#ifndef COUNTSORT_H
#define COUNTSORT_H

#include <initializer_list> // intializer_list
#include <stdexcept> // exceptions

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
    class iterator {
      private:
        const CountSort &parent;
        int array_index;
        int element_index = 1;
      public:
        // Constructor
        iterator(const CountSort &p, int ai = 0) : parent(p), array_index(ai) {
            while (array_index < parent.range && !parent.numbers[array_index]) {
                ++array_index;
            }
        }
        // Copy constructor
        iterator(const iterator &rhs) = default;
        // Copy assignment operator
        iterator &operator =(const iterator &rhs) = default;
        // Destructor
        ~iterator() = default;

        // Preincrement
        iterator &operator ++() {
            if (element_index < parent.numbers[array_index]) {
                ++element_index;
                return *this;
            }
            if (array_index >= parent.range) {
                throw std::out_of_range("Attempt to increment iterator past end()");
            }
            do {
                ++array_index;
            } while (array_index < parent.range && !parent.numbers[array_index]);
            element_index = 1;
            return *this;
        }
        // Postincrement
        iterator operator ++(int) {
            const auto save = *this;
            ++*this;
            return save;
        }
        // Operator *
        int operator *() const {
            return array_index + parent.lower_bound;
        }
        // Operator ==
        bool operator ==(const iterator &rhs) const {
            return parent == rhs.parent && array_index == rhs.array_index &&
                   element_index == rhs.element_index;
        }
        // Operator != 
        bool operator !=(const iterator &rhs) const {
            return !(*this == rhs);
        }
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

    // Return a CountSort::iterator that corresponds to the smallest int stored
    iterator begin() const;
    // Return a CountSort::iterator that corresponds one past the largest int stored
    iterator end() const;

};

#endif /* COUNTSORT_H */
