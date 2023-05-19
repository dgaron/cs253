#include "CountSort.h"
#include "CountSort.h"  // I meant to do that.
#include <iostream>     // cout, cerr
#include <cassert>      // assert()
#include <cstdlib>      // malloc()
 
using namespace std;
 
// Ensure that the student is not just storing the items in a vector,
// by forbidding large allocations.
 
void *operator new(size_t size) {
    assert(size < 10'000);          // should never need this much
    return malloc(size);
}
 
void operator delete(void *p, size_t /* size */) {
    free(p);
}
 
void operator delete(void *p) {
    free(p);
}
 
int main() {
    
    
    CountSort cs(10,19);
    assert(cs.size()==0);
    assert(cs.empty());
    assert(cs.begin() == cs.end());
    cs.insert(11);
    assert(cs.size()==1);
    assert(!cs.empty());
    assert(cs.begin() != cs.end());
    cs = {11, 17, 13, 19, 19, 17, 19, 13, 17};
    assert(cs.size() == 9);
    cs.insert(19);
    // Now contains 11×1, 13×2, 17×3, 19×4.
 
    cout << "size: " << cs.size() << '\n';
    for (auto n : cs)
        cout << n << ' ';
    cout << '\n';
    for (int i=0; i<cs.size(); i++)
        cout << cs[i] << ' ';
    cout << '\n';
    for (int i=0; i<=cs.max()-cs.min(); i++)
        cout << cs.min()+i << 'x' << cs(i) << " ";
    cout << '\n';
 
    // Make sure they’re not storing all the numbers, just counts.
    for (int i=0; i<10'000; i++)
        cs.insert(15);
    // Now contains 11×1, 13×2, 15×10⁴ 17×3, 19×4.
    assert(cs.size() == 10'010);
 
    CountSort::iterator it = cs.begin();
    assert(*it == 11);
    assert(*it == 11);
    assert(*it == 11);
    assert(it == cs.begin());
    assert(it != cs.end());
    it++;               // now points at first 13
    assert(it != cs.begin());
    ++it;               // now points at second 13
    assert(*it == 13);
    assert(*it == 13);
    ++it;               // now points at first 15
    assert(*it == 15);
    for (int i=0; i<9'999; i++)
        it++;
    // it now points at the last 15
    assert(*it++ == 15);
    // it now points at the first 17
    assert(*it == 17);
    assert(*it == 17);
    assert(*it == 17);
    assert(*it == 17);
    assert(*it == 17);
    assert(*it == 17);
    
    
    CountSort alpha(-10,10);
    alpha = {-10,10};
    // alpha = {-11,10};
    // alpha = {-10,11};
    alpha.insert(-10);
    alpha.insert(10);
    alpha.insert(0);
    // alpha.insert(-11);
    // alpha.insert(11);
    
    // alpha contains -10, -10, 0, 10, 10
    cout << "alpha(0) should be 2: " << alpha(0) << '\n' 
         << "alpha(1) should be 0: " << alpha(1) << '\n'
         << "alpha(20) should be 2: " << alpha(20) << '\n';
    // alpha(-1);
    // alpha(21);
    
    for (int i = 0; i < alpha.size(); ++i) {
        cout << alpha[i] << ' ';
    }
    cout << '\n';
    // alpha[-1];
    // alpha[5];

    const CountSort &beta = alpha;

    cout << "min() should be -10: " << beta.min() << '\n'
         << "max() should be 10: " << beta.max() << '\n'
         << "size() should be 5: " << beta.size() << '\n'
         << "empty() should be 0: " << beta.empty() << '\n';

    alpha.clear();
    cout << "size() should be 0 now: " << alpha.size() << '\n'
         << "empty() should be 1 now: " << alpha.empty() << '\n';

    CountSort gamma(0,9);
    gamma = {1,1,9,9,9,9};
    for (auto n : gamma) {
        cout << n << ' ';
    }
    cout << '\n';

    auto iter = gamma.begin();
    for (auto iter_copy = iter; iter_copy != gamma.end(); ++iter_copy) {
        cout << *iter_copy << ' ';
    }
    cout << '\n';    

    cout << *(iter++) << ' ' << *(iter++) << ' ' << *iter << '\n';

    return 0;
}

