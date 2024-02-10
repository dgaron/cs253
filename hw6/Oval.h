#ifndef OVAL_H
#define OVAL_H

#include <functional>   // std::equal_to<T>
#include <vector>       // std::vector<T> obviously
#include <algorithm>    // std::copy() in operator =
#include <iterator>     // std::distance() in find()

template <typename T, int P = 1, typename C = std::equal_to<T> >
class Oval {
  public:
    // Default constructor -- use default
    Oval() = default;
    // Copy constructor
    Oval(const Oval &);
    // iterator-iterator constructor
    template <typename I>
    Oval(I, I);
    // Assignment operator
    Oval &operator =(const Oval<T, P, C> &);
    // Destructor -- use default
    ~Oval() = default;

    // Return the number of data items currently stored
    size_t size() const;
    // Finds the first instance of T, promotes item by specified amount
    // Returns new index, -1 if not found
    int find(const T &);
    // Return how many times a given value occurs in the container
    size_t count(const T &) const;
    // Adds an item to the end of the container
    void push_back(const T &);
    // Erase all matching items
    // Returns number of items erased
    size_t erase(const T &);
    // Clear the container
    void clear();
    // Subscripting
    T &operator [](size_t);
    // Const subscripting
    const T &operator[](size_t) const;

    // Returns a const reference to the data container
    const std::vector<T> &getData() const;

  private:
    std::vector<T> data;
};

/* IMPLEMENTATION */

// Copy constructor
template <typename T, int P, typename C>
Oval<T, P, C>::Oval(const Oval<T, P, C> &rhs) : data(rhs.getData()) { 
}

// iterator - iterator constructor
template<typename T, int P, typename C>
template<typename I>
Oval<T, P, C>::Oval(I begin, I end) : data(begin, end) {
}

// Assignment operator
template <typename T, int P, typename C>
Oval<T, P, C> &Oval<T, P, C>::operator =(const Oval<T, P, C> &rhs) {
    const std::vector<T> rhData = rhs.getData();
    data.resize(rhData.size());
    std::copy(rhData.begin(), rhData.end(), data.begin());
    return *this;
}

// Return the number of data items currently stored
template <typename T, int P, typename C>
size_t Oval<T, P, C>::size() const {
    return data.size();
}

// Finds the first instance of T, promotes item by specified amount
// Returns new index, -1 if not found 
template <typename T, int P, typename C>
int Oval<T, P, C>::find(const T &val) {
    auto iter = data.begin();
    // Iterate through data, calling compare functor on each item & val
    for (C compare; !compare(*iter, val) && iter != data.end(); ++iter) {}
    // If it == data.end(), val not found, return -1
    if (iter == data.end()) {
        return -1;
    }
    // If index is 0, do nothing
    if (iter == data.begin()) {
        return 0;
    }
    // Remove item from current position, pointed to by iter
    T save = *iter;
    data.erase(iter);
    if (std::distance(data.begin(), iter) <= P) {
        // If distance from index 0 is <= P, move to index 0
        iter = data.begin();
    } else {
        // Else move forward by P positions
        iter -= P;
    }
    // Place item at new position
    data.insert(iter, save);
    return std::distance(data.begin(), iter);
}

// Return how many times a given value occurs in the container
template <typename T, int P, typename C>
size_t Oval<T, P, C>::count(const T &val) const {
    C compare;
    int count = 0;
    for (auto iter = data.begin(); iter != data.end(); ++iter) {
        if (compare(*iter, val)) {
            ++count;
        }
    }
    return count;
}
    
// Erase all matching items
// Returns number of items erased
template <typename T, int P, typename C>
size_t Oval<T, P, C>::erase(const T &val) {
    C compare;
    int count = 0;
    // Iterate through data, calling comparison functor on each item & val
    for (auto iter = data.begin(); iter != data.end(); ++iter) {
        if (compare(*iter, val)) {
            data.erase(iter);
            ++count;
            // Iterator moves to position after erased item
            // Decrement prevents a double hop in the iterator
            --iter;
        }
    }
    return count;
}

// Adds an item to the end of the container
template <typename T, int P, typename C>
void Oval<T, P, C>::push_back(const T &item) {
    data.push_back(item);
}

// Clear the container
template <typename T, int P, typename C>
void Oval<T, P, C>::clear() {
    data.clear();
}

// Subscripting
template <typename T, int P, typename C>
T &Oval<T, P, C>::operator [](size_t index) {
    return data[index];
}

// Const subscripting
template <typename T, int P, typename C>
const T &Oval<T, P, C>::operator[](size_t index) const {
    return data[index];
}

// Returns the data vector by const reference
template <typename T, int P, typename C>
const std::vector<T> &Oval<T, P, C>::getData() const {
    return data;
}

#endif /* OVAL_H */
