#include "hset.h"
#include <iostream>
#include <iomanip>			// for setw()
#include <time.h>			// for time() (duh)

using namespace std;

int main() {
    cout << setprecision(4);		// Display four significant digits

    hset<int> h;
    for (int j=0; j<20; j++)		// Put some numbers into the set
	    h.insert(j*17 % 100);		// Each number is [0,100).
    h.dump();				// Let’s see what’s in there

    cout << "size=" << h.size() << ':';
    for (auto v : h)
	    cout << ' ' << v;
    cout << '\n';

    hset<string> hs;
    for (auto s : {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta"})
	    hs.insert(s);
    hs.dump();

    cout << "size=" << hs.size();
    for (auto v : hs)
	    cout << ' ' << v;
    cout << '\n';

    /*
    // Test empty() for exercise 2
    cout << boolalpha <<  hs.empty() << '\n';

    hset<int, 10> emptySet;
    cout << emptySet.empty() << '\n';
    */
    
    // Test exercise 3
    hset<double> exer3;
    for (double i = 1.1; i < 2.0; i += 0.1) {
        exer3.insert(i);
    }
    exer3.dump();

    // Test exercise 4
    hset<string> exer4;
    for (auto s : {"alpha", "beta", "gamma", "epsilon", "zeta", "eta"})
        exer4.insert(s);
    exer4.dump();
    auto iter = exer4.begin();
    cout << "First bucket is empty. Here's the first item: " << *iter << '\n';


}
