#ifndef HSET_ITER_H_INCLUDED
#define HSET_ITER_H_INCLUDED

#include <list>
#include <vector>
#include <iterator>	// for advance()

// Each hset_iter contains a reference to its associated hash,
// and an int indicating progress within the hash.

template <typename T>
class hset_iter {
  private:
    using table_t = typename std::vector<std::list<T>>;
    const table_t &parent;  // reference to the hash table we’re iterating over
    unsigned int vector_index;		// how far along vector we are -- 0 = first item
    unsigned int list_index;         // how far along list we are -- 0 = first item

  public:
    hset_iter(table_t &table, int vi, int li = 0) : parent(table), vector_index(vi), list_index(li) { 
        while (vector_index < parent.size() && parent[vector_index].empty()) {
            ++vector_index;
        }
    }

    bool operator==(const hset_iter &rhs) const {
    	return vector_index == rhs.vector_index;
    }

    bool operator!=(const hset_iter &rhs) const {
	    return !(*this == rhs);
    }

    // Return a pointer to the vector_index'th element,
    // where vector_index==0 is the first element.

    T operator*() const {
        auto it = parent[vector_index].begin();
        advance(it, list_index);
	    return *it;
    }

    // Pre-increment
    void operator++() {
        auto &current = parent[vector_index];
        if (current.empty() || list_index == (current.size() - 1)) {
            ++vector_index;
            list_index = 0;
        } else {
	        ++list_index;
        }
    }
};

#endif /* HSET_ITER_H_INCLUDED */
