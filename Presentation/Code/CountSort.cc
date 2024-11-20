#include <stdexcept>    // std::invalid_argument, std::out_of_range, std::range_error
#include <string>       // std::string, std::to_string()
#include <initializer_list> // std::initializer_list
#include <algorithm>    // std::min(), std::max(), std::fill(), std::copy()
#include <iterator>     // std::advance()
#include <ostream>      // std::ostream
#include <climits>       // INT_MIN, INT_MAX
#include "CountSort.h"

CountSort::CountSort(int lb, int ub) : lower_bound_(lb), upper_bound_(ub), width_(calculate_width_(lb, ub)) {
    if (upper_bound_ < lower_bound_) {
        std::string msg = "Invalid range: [" + std::to_string(lower_bound_) + " - " + std::to_string(upper_bound_) + ']';
        throw std::invalid_argument(msg);
    }
    numbers_ = new unsigned int[width_] {0};
}

CountSort::CountSort(const CountSort &rhs) : CountSort(rhs.min(), rhs.max()) {
    size_ = rhs.size();
    std::copy(rhs.numbers_, rhs.numbers_ + width_, numbers_);
}

CountSort::CountSort(CountSort &&rhs) noexcept
        : lower_bound_(rhs.min()), upper_bound_(rhs.max()), width_(rhs.width()) {
    numbers_ = rhs.numbers_;
    size_  = rhs.size();

    rhs.numbers_ = nullptr;
    rhs.size_ = 0;
}

CountSort::CountSort(const std::initializer_list<int> il) : CountSort(std::min(il), std::max(il)) {
    for (auto n : il) {
        insert(n);
    }
}

CountSort &CountSort::operator=(const CountSort &rhs) {
    if (this != &rhs) {
        if (lower_bound_ != rhs.min() || upper_bound_ != rhs.max()) {
            std::string msg = "Object with bounds: [" + std::to_string(rhs.min()) + " - " + std::to_string(rhs.max()) + ']';
            msg += " cannot be assigned to object with bounds: [" + std::to_string(lower_bound_) + " - " + std::to_string(upper_bound_) + ']';
            throw std::range_error(msg);
        }
        size_ = rhs.size();
        std::copy(rhs.numbers_, rhs.numbers_ + width_, numbers_);
    }
    return *this;
}

CountSort &CountSort::operator=(CountSort &&rhs) {
    if (lower_bound_ != rhs.min() || upper_bound_ != rhs.max()) {
        std::string msg = "Object with bounds: [" + std::to_string(rhs.min()) + " - " + std::to_string(rhs.max()) + ']';
        msg += " cannot be assigned to object with bounds: [" + std::to_string(lower_bound_) + " - " + std::to_string(upper_bound_) + ']';
        throw std::range_error(msg);
    }
    delete[] numbers_;
    numbers_ = rhs.numbers_;
    size_ = rhs.size();
    
    rhs.numbers_ = nullptr;
    rhs.size_ = 0;

    return *this;
}

CountSort &CountSort::operator=(const std::initializer_list<int> il) {
    auto lowest = std::min(il);
    check_range_(lowest, lower_bound_, upper_bound_);
    auto highest = std::max(il);
    check_range_(highest, lower_bound_, upper_bound_);
    clear();
    for (auto n : il) {
        insert(n);
    }
    return *this;
}

CountSort::~CountSort() {
    delete[] numbers_;
}

void CountSort::check_range_(int n, int lower, int upper) const {
    if (n < lower || n > upper) {
        std::string msg = std::to_string(n) + " is outside of allowable range [" + std::to_string(lower) + " - " + std::to_string(upper) + ']';
        throw std::out_of_range(msg);
    }
}

unsigned int CountSort::calculate_width_(int lb, int ub) const {
    if (ub < lb) {
        // Constructor throws in this case
        return 0;
    }
    if (ub == INT_MAX && lb == INT_MIN) {
        std::string msg = "Error constructing range using lower bound: " + std::to_string(lb) + " and upper bound: " + std::to_string(ub) + '\n';
        msg += "Width is limited to " + std::to_string(UINT_MAX);
        throw std::invalid_argument(msg);
    }
    unsigned int width = static_cast<unsigned int>(ub) - lb + 1;

    // unsigned int width = 0;
    // Returns true in the case of an overflow
        // I think this is unreachable because of previous check
    // if (__builtin_sub_overflow (ub, lb, &width))  {
    //     std::string msg = "Error constructing range using lower bound: " + std::to_string(lb) + " and upper bound: " + std::to_string(ub) + '\n';
    //     msg += "Width is limited to " + std::to_string(UINT_MAX);
    //     throw std::overflow_error(msg);
    // }
    // return width + 1;

    return width;
}


int CountSort::operator()(int n) const {
    check_range_(n, 0, width_ - 1);
    return numbers_[n];
}

int CountSort::operator[](unsigned int n) const {
    if (size_ == 0) {
        std::string msg = "Attempt to access empty object";
        throw std::out_of_range(msg);
    }
    check_range_(n, 0, size_ - 1);
    Iterator it = begin();
    std::advance(it, n);
    return *it;
}

int CountSort::min() const {
    return lower_bound_;
}

int CountSort::max() const {
    return upper_bound_;
}

unsigned int CountSort::width() const {
    return width_;
}

unsigned long CountSort::size() const {
    return size_;
}

bool CountSort::empty() const {
    return !size_;
}

void CountSort::insert(int n) {
    check_range_(n, lower_bound_, upper_bound_);
    ++numbers_[n - lower_bound_];
    ++size_;
}

void CountSort::clear() {
    std::fill(numbers_, numbers_ + width_, 0);
    size_ = 0;
}

CountSort::Iterator CountSort::begin() const {
    return Iterator(this);
}

CountSort::Iterator CountSort::end() const {
    return Iterator(this, width_);
}

CountSort::Iterator::Iterator() {}

CountSort::Iterator::Iterator(const CountSort *p, unsigned int ii) : parent(p), integer_index(ii) {
    while (integer_index < parent->width_ && !(parent->numbers_[integer_index])) {
        ++integer_index;
    }
}

int CountSort::Iterator::operator*() const {
    if (integer_index >= parent->width_) {
        std::string msg = "Attempt to dereference invalid iterator";
        throw std::out_of_range(msg);
    }
    return integer_index + parent->lower_bound_;
}

int CountSort::Iterator::operator[](unsigned long n) const {
    if (n < 0 || n >= parent->size()) {
        std::string msg = std::to_string(n) + " is outside of allowable range [0-" + std::to_string(parent->size() - 1) + ']';
        throw std::invalid_argument(msg);
    }
    auto it = parent->begin();
    it += n;
    return *it;
}

CountSort::Iterator &CountSort::Iterator::operator++() {
    if (integer_index >= parent->width_) {
        std::string msg = "Attempt to increment Iterator past end()";
        throw std::out_of_range(msg);
    }
    if (++current_integer_count <= parent->numbers_[integer_index]) {
        return *this;
    }
    do {
        ++integer_index;
        // Find the next integer with non-zero count, if it exists
    } while (integer_index < parent->width_ && !(parent->numbers_[integer_index]));
    current_integer_count = 1;
    return *this;
}

CountSort::Iterator CountSort::Iterator::operator++(int) {
    const auto save = *this;
    ++*this;
    return save;
}

CountSort::Iterator &CountSort::Iterator::operator--() {
    if (*this == parent->begin()) {
        std::string msg = "Attempt to decrement Iterator before begin()";
        throw std::out_of_range(msg);
    }
    if (--current_integer_count > 0) {
        return *this;
    }
    do {
        --integer_index;
        // Find the previous integer with non-zero count, if it exists
    } while (integer_index >= 0 && !(parent->numbers_[integer_index]));
    current_integer_count = parent->numbers_[integer_index];
    return *this;
}

CountSort::Iterator CountSort::Iterator::operator--(int) {
    const auto save = *this;
    --*this;
    return save;
}

CountSort::Iterator &CountSort::Iterator::operator+=(CountSort::Iterator::difference_type n) {
    Iterator temp(*this);
    for (int i = 0; i < n; ++i) {
        ++temp;
    }
    *this = temp;
    return *this;
}

CountSort::Iterator &CountSort::Iterator::operator-=(CountSort::Iterator::difference_type n) {
    Iterator temp(*this);
    for (CountSort::Iterator::difference_type i = 0; i < n; ++i) {
        --temp;
    }
    *this = temp;
    return *this;
}



CountSort::Iterator operator+(const CountSort::Iterator &it, CountSort::Iterator::difference_type n) {
    CountSort::Iterator temp(it);
    temp += n;
    return temp;
}

CountSort::Iterator operator+(CountSort::Iterator::difference_type n, const CountSort::Iterator &it) {
    return it + n;
}

CountSort::Iterator operator-(const CountSort::Iterator &it, CountSort::Iterator::difference_type n) {
    CountSort::Iterator temp(it);
    temp -= n;
    return temp;
}

CountSort::Iterator::difference_type operator-(const CountSort::Iterator &lhs, const CountSort::Iterator &rhs) {
    if (lhs.parent != rhs.parent) {
        std::string msg = "Attempt to subtract iterators for different object instances";
        throw std::invalid_argument(msg);
    }
    if (rhs > lhs) {
        return -(rhs - lhs);
    }
    CountSort::Iterator temp(rhs);
    CountSort::Iterator::difference_type distance = 0;
    while (temp != lhs) {
        ++temp;
        ++distance;
    }
    return distance;
}

bool operator==(const CountSort::Iterator &lhs, const CountSort::Iterator &rhs) {
    return (lhs.parent == rhs.parent && 
            lhs.integer_index == rhs.integer_index && 
            lhs.current_integer_count == rhs.current_integer_count);
}

bool operator!=(const CountSort::Iterator &lhs, const CountSort::Iterator &rhs) {
    return !(lhs == rhs);
}

bool operator>(const CountSort::Iterator &lhs, const CountSort::Iterator &rhs) {
    return (lhs.parent == rhs.parent && 
            (lhs.integer_index > rhs.integer_index || 
            (lhs.integer_index == rhs.integer_index && lhs.current_integer_count > rhs.current_integer_count)));
}

bool operator>=(const CountSort::Iterator &lhs, const CountSort::Iterator &rhs) {
    return !(lhs < rhs);
}

bool operator<(const CountSort::Iterator &lhs, const CountSort::Iterator &rhs) {
    return (lhs.parent == rhs.parent && 
            (lhs.integer_index < rhs.integer_index || 
            (lhs.integer_index == rhs.integer_index && lhs.current_integer_count < rhs.current_integer_count)));
}

bool operator<=(const CountSort::Iterator &lhs, const CountSort::Iterator &rhs) {
    return !(lhs > rhs);
}

std::ostream &operator<<(std::ostream &os, const CountSort &cs) {
    std::string sep = "";
    for (auto n : cs) {
        os << sep << std::to_string(n);
        sep = ", ";
    }
    return os;
}
