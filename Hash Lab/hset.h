#ifndef HSET_H_INCLUDED
#define HSET_H_INCLUDED

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include "hasher.h"
#include "hset_iter.h"

                      // Exercise 1
template <typename T, unsigned N = 5, typename H = Hasher>
class hset {
  private:
    // Exercise 1
    const unsigned table_size = N;
    std::vector<std::list<T>> table;

  public:
    using iterator = hset_iter<T>;
    using value_type = T;
    using size_type = size_t;

    hset() : table(table_size) { }
    hset(const hset &) = default;
    hset &operator=(const hset &) = default;
    ~hset() = default;

    void insert(const T &datum) {
	    unsigned hashval = H()(datum) % table.size();
	    auto &lr = table[hashval];
	    if (find(lr.begin(), lr.end(), datum) == lr.end())
	        lr.push_back(datum);
    }

    // Walk down the hash table, adding up all the sizes.
    size_type size() const {
	    size_type total = 0;
	    for (const auto &row : table)
	        total += row.size();
    	return total;
    }

    iterator begin() {
    	return iterator(table, 0);
    }

    iterator end() {
        // Exercise 4
	    return iterator(table, table_size);
    }

    void dump() const {
    	for (unsigned i=0; i<table.size(); i++) {
	        std::cout << "table[" << i << "]";
	        for (auto v : table[i]) 
		        std::cout << ' ' << v;
    	    std::cout << '\n';
	    }
    }
    // Exercise 2
    bool empty() const {
        for (auto x : table) {
            if (!x.empty()) {
                return false;
            }
        }
        return true;
    }

};

#endif /* HSET_H_INCLUDED */
