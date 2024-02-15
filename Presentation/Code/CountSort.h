#ifndef COUNTSORT_H
#define COUNTSORT_H

#include <initializer_list> // std::intializer_list
#include <cstddef>  // std::ptrdiff_t
#include <iterator> // std::random_access_iterator_tag

class CountSort {
  public:
    CountSort(int, int);
    CountSort(const CountSort &);
    CountSort(const std::initializer_list<int>);
    CountSort &operator=(const CountSort &);
    CountSort &operator=(const std::initializer_list<int>);
    // Not implemented
    // CountSort(CountSort &&);
    // CountSort &operator=(const CountSort &&);
    ~CountSort();

    int operator()(int) const;
    int operator[](unsigned int) const;

    int min() const;
    int max() const;
    unsigned int width() const;
    unsigned long size() const;
    bool empty() const;
    void insert(int);
    void clear();

    class Iterator {
      public:
        // Iterator traits
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = value_type *;
        using reference = value_type &;
        using iterator_category = std::random_access_iterator_tag;

        Iterator();
        Iterator(const CountSort *, unsigned int ii = 0);
        Iterator(const Iterator &) = default;
        Iterator &operator=(const Iterator &) = default;
        ~Iterator() = default;

        int operator*() const;
        int operator[](unsigned long) const;

        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);

        Iterator &operator+=(difference_type);
        Iterator &operator-=(difference_type);

        friend Iterator operator+(const Iterator &, difference_type);
        friend Iterator operator+(difference_type, const Iterator &);
        friend Iterator operator-(const Iterator &, difference_type);

        friend difference_type operator-(const Iterator &, const Iterator &);

        friend bool operator==(const Iterator &, const Iterator &);
        friend bool operator!=(const Iterator &, const Iterator &);
        friend bool operator>(const Iterator &, const Iterator &);
        friend bool operator>=(const Iterator &, const Iterator &);
        friend bool operator<(const Iterator &, const Iterator &);
        friend bool operator<=(const Iterator &, const Iterator &);
      private:
        const CountSort *parent = nullptr;
        unsigned int integer_index = 0;
        unsigned int current_integer_count = 1;
    };

    Iterator begin() const;
    Iterator end() const;
  private:
    unsigned int *numbers_;
    const int lower_bound_;
    const int upper_bound_;
    const unsigned int width_;
    unsigned long size_ = 0;
    void check_range_(int, int, int) const;
};

std::ostream& operator<<(std::ostream &, const CountSort &);

#endif // COUNTSORT_H