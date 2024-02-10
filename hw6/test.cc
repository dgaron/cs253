#include "Oval.h"
#include "Oval.h"       // I meant to do that.
#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
 
#include <vector>

using namespace std;

// Return a string with all the elements of this container.
template <typename T>
string cat(const T &container, string separator = "") {
    ostringstream oss;
    bool first = true;
    for (size_t i=0; i<container.size(); i++) {
        if (!first)
            oss << separator;
        first = false;
        oss << container[i];
    }
    return oss.str();
}
 
// case-independent comparison functor
class Fold {
  public:
    bool operator()(char a, char b) {
        return tolower(a) == tolower(b);
    }
};

int main() {

    vector<short> initial_values = {123, 11, 22, 123, 33, 22, 123};
    Oval<int> o(initial_values.begin(), initial_values.end());
    cout << cat(o, ",") << '\n';
    auto count = o.erase(123);
    assert(count == 3);
    cout << "Erased " << count << " of 123: " << cat(o, ",") << '\n';
    count = o.erase(666);
    cout << "Erased " << count << " of 666: " << cat(o, ",") << '\n';
    assert(count == 0);
    auto n = o.find(22); cout << "find 22: " << cat(o, ",") << '\n';
    assert(n == 0);
    n = o.find(33); cout << "find 33: " << cat(o, ",") << '\n';
    assert(n == 1);
    n = o.find(99); cout << "find 99: " << cat(o, ",") << '\n';
    assert(n == -1);
 
    for (auto target : {11,22,66})
        cout << "count(" << target << ")=" << o.count(target) << '\n';
 
    string s = "BONEhea";
    Oval<char, 2, Fold> ov(s.begin(), s.end());
    ov.push_back('d');
    cout << cat(ov) << '\n';
    assert(ov.count('e') == 2);
    assert(ov.count('&') == 0);
    n = ov.find('e');
    assert(n == 1);
    assert(cat(ov) == "BEONhead");
    n = ov.find('%');
    assert(n == -1);
    assert(cat(ov) == "BEONhead");
    n = ov.find('D');
    cout << cat(ov) << '\n';
    assert(n == 5);
    assert(cat(ov) == "BEONhdea");
    n = ov.erase('e');
    assert(n == 2);
    assert(cat(ov) == "BONhda");
    cout << cat(ov) << '\n';


    /* My tests */

    // Test default constructor
    Oval<int, 4> o1;

    // Test push_back
    for (int i = 0; i < 10; ++i) {
        o1.push_back(i);
    }

    // Test operator[]
    cout << "o1[0] should be 0: " << o1[0] << '\n';
    o1[0] = 5;
    cout << "o1[0] should be 5 now: " << o1[0] << '\n';

    // Test copy constructor
    const Oval o2(o1);

    // Test const operator[]
    cout << "o2[3] should be 3: " << o2[3] << '\n';

    // This should fail, and it does
    // o2[3] = 5; 

    // Test getData
    const vector<int> v1 = o1.getData();
    for (auto val : v1) {
        cout << val << ' ';
    }   
    cout << '\n';

    // Test iter-iter constructor
    Oval<int, 5> o3(v1.begin(), v1.end());

    // Test assignment operator
    Oval<int, 4> o4;
    o4 = o1;

    const vector<int> v2 = o4.getData();
    for (auto val : v2) {
        cout << val << ' ';
    }
    cout << '\n';

    // Test size
    cout << "o1 size (should be 10): " << o1.size() << '\n';

    // Test find
    cout << "Find 9, new index should be 5: " << o1.find(9) << '\n';
    cout << "Find 3, new index should be 0: " << o1.find(3) << '\n';
    cout << "Find 500, should return -1: " << o1.find(500) << '\n';

    // Test erase
    Oval<int, 3> o5;
    Oval<int, 2> o6;
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            o5.push_back(1);
        } else {
            o5.push_back(2);
        }
        o6.push_back(i);
    }

    cout << "Count should be 5: " << o5.count(2) << '\n';

    const vector<int> v3 =  o5.getData();
    for (auto val : v3) {
        cout << val << ' ';
    }
    cout << '\n';
    cout << "Erase count should be 5: " << o5.erase(2) << '\n';

    const vector<int> v4 = o5.getData();
    for (auto val : v4) {
        cout << val << ' ';
    }
    cout << '\n';

    cout << "Erase count should be 1: " << o6.erase(5) << '\n';
    cout << "o6 find 8, should be 5 now: " << o6.find(8) << '\n';

    return 0;

}
