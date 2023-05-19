#include "Phobic.h"
#include "Phobic.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
 
using namespace std;
 
int main() {

/*
    Phobic a(13);
    assert(a.get() == 14);

    a << 14;
    assert(a.get() == 15);
    a << 15 << 16 << 17;
    assert(a.get() == 18);

    Phobic b(5);
    b << 23 << 29;

    Phobic c = a + b;
    assert(c.get() == 24);

    a += 10;
    assert(a.get() == 28);

    b += c;
    assert(b.get() == 30);

    a -= 18;
    assert(a.get() == 10);

    b /= a;
    assert(b.get() == 3);

    a *= 5;
    assert(a.get() == 50);

    c = b * a;
    assert(c.get() == 150);

    c = b / 1;
    assert(c.get() == 3);

    assert(c == b);

    assert(a > c);
    assert(c < a);
    assert(a >= 50);
    
    c = a;
    assert(a == c);

    assert(a != b);

    try {
        a /= 0;
    } catch (const runtime_error &e) {
        cout << e.what() << '\n';
    }

    assert(a == 50);

    const Phobic d(13);
    Phobic e;
    e << 14 << 15 << 16;
    e = d;
    assert(e == 17);

    Phobic f(d);
    assert(f == 14);
*/

    const Phobic three(3), seven(7), two=seven/three, five{seven-two}, ten=10;
    assert(five == 5);
    assert(ten-two == 4*two);
    assert(ten/two == two+two+two/two);

    Phobic dotcom(three);
 
    Phobic x(4); x << 12 << 3;  // fears 3, 12, and 13
    Phobic y; y << 11;          // fears 11 & 13
    Phobic fearful(y/x);
    assert(fearful.is_scary(11));
    assert(fearful.is_scary(12));
    assert(fearful.is_scary(13));
    assert(!x.is_scary(11));
    assert(!y.is_scary(3));
    assert(!y.is_scary(2));

    Phobic a(13);               // 14
    assert(a.get() == 14);
    a << 14;                    // a is bumped to 15
    assert(a.get() == 15);
    a = a;                      // fraught with peril
    assert(a.is_scary(14));     // did it survive?

    assert(2 + a == 17);
    assert(a - two == 15);      // 15 - 2 is 13 bumped to 15
    assert(30 == two * a);
    assert(seven == a / two);
 
    a += ten;                   // 15 ⇒ 25
    assert(a == 25);
    a -= 5;                     // 25 ⇒ 20
    assert(20 == a);
    a *= a;                     // 20 ⇒ 400
    assert(a == 400);
    a /= ten;                   // 400 ⇒ 40
    assert(a == 40);
 
    assert(two < three);
    assert(3 > two);
    assert(3 <= ten);
    assert(ten >= 5);
    assert(ten == ten);
    assert(-10 != ten);
 
    try {
        a /= (two/ten);         // attempt division by zero
    }
    catch (const runtime_error &) {  // Hey, no variable!
        a += 3 - two;           // 40 ⇒ 41
    }
    assert(a.get() == 41);      // Did we catch the divide by zero?
 
    cout << "SUCCESS!" << '\n';

    return 0;
}
