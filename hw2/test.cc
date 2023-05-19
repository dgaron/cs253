#include "Phobic.h"
#include <iostream>
#include <cassert>
 
using namespace std;
 
int main() {

    cout << "Testing default constructor" << '\n';
    Phobic alpha;
    assert(alpha.get() == 0);

    cout << "Testing constructor with int argument & updateCurrentValue()" << '\n';
    Phobic beta(13); 
    assert(beta.get() == 14);

    cout << "Testing copy constructor" << '\n';              
    Phobic gamma(alpha);
    assert(gamma.get() == 0);
    Phobic delta = beta;
    assert(delta.get() == 14);

    cout << "Testing assignment operator" << '\n';
    Phobic epsilon;
    epsilon = beta;
    assert(epsilon.get() == 14);

    cout << "Testing add()" << '\n';
    Phobic zeta = epsilon.add(beta);
    assert(zeta.get() == 28);

    cout << "Testing add() with self" << '\n';
    zeta = epsilon.add(epsilon);
    assert(zeta.get() == 28);

    cout << "Testing sub()" << '\n';
    zeta = beta.sub(epsilon);
    assert(zeta.get() == 0);

    cout << "Testing sub() with self" << '\n';
    zeta = beta.sub(beta);
    assert(zeta.get() == 0);

    cout << "Testing mul()" << '\n';
    zeta = epsilon.mul(2);
    assert(zeta.get() == 28);

    cout << "Testing div()" << '\n';
    zeta = epsilon.div(7);
    assert(zeta.get() == 2); 

    cout << "Testing eq()" << '\n';
    assert(beta.eq(epsilon));
    assert(!beta.eq(alpha));

    cout << "Testing lt()" << '\n';
    assert(zeta.lt(epsilon));
    assert(!zeta.lt(alpha));

    cout << "Testing add_to()" << '\n';
    zeta.add_to(beta);
    assert(zeta.get() == 16);

    cout << "Testing add_to() with self" << '\n';
    zeta.add_to(zeta);
    assert(zeta.get() == 32);

    cout << "Testing sub_from()" << '\n';
    zeta.sub_from(epsilon);
    assert(zeta.get() == 18);

    cout << "Testing mul_by()" << '\n';
    zeta.mul_by(alpha);
    assert(zeta.get() == 0);

    cout << "Testing div_by()" << '\n';
    beta.div_by(epsilon);
    assert(beta.get() == 1);

    cout << "Testing make_scary()" << '\n';
    alpha.make_scary(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    alpha.make_scary(10, 11, 12);
    assert(alpha.get() == 14);

    cout << "Testing is_scary()" << '\n';
    assert(alpha.is_scary(11));
    assert(!alpha.is_scary(100));

    // Updated assignment operator test
    Phobic p1(20);
    p1.make_scary(20,22,24,26,28);
    Phobic p2;
    p2.make_scary(21,23,25,27,29);

    p2 = p1;

    assert(p2.is_scary(20));
    assert(p2.is_scary(21));
    assert(p2.is_scary(28));
    assert(p2.is_scary(29));

    assert(p2.get() == 30);

    // p1 == 21
    Phobic p100;

    p1.div_by(p100);

    assert(p1.get() == 21);
    assert(p100.get() == 0);
    assert(p100.is_scary(13));
    assert(!p100.is_scary(21));


    Phobic a(13);               // a is 13 bumped to 14
    assert(a.get() == 14);      // since 13 is always scarry
    a.make_scary(14);           // bumps a to 15
    assert(a.get() == 15);
 
    Phobic b = a.add(4);        // b is 15+4 = 19
    assert(a.get() == 15);
    assert(b.get() == 19);
 
    b.make_scary(35,12,34);     // b now fears 12,13,34,35
    assert(b.is_scary(12));
    assert(b.is_scary(13));
    assert(b.is_scary(35));
    assert(b.is_scary(34));
    assert(!b.is_scary(42));
 
    a.add_to(b);                // a is 15+19 = 34, bumped to 36
    assert(a.get() == 36);
    assert(b.add(0).get() == 19);
 
    assert(a.is_scary(12));     // b’s fears should get merged into a.
    assert(a.is_scary(13));     // a now fears 12,13,14,34,35
    assert(a.is_scary(14));
    assert(a.is_scary(34));
    assert(a.is_scary(35));
 
    a.mul_by(2);                // a is 36*2 = 72
    const Phobic c(72);
    assert(a.eq(c));            // 72 == 72
    assert(b.lt(c));            // 19 < 72
    assert(c.get() == 72);
    assert(c.eq(72));           // 72 == 72
    assert(c.eq(c));            // 72 == 72
    assert(!c.eq(99));          // !(72 == 99)
    assert(c.lt(99));           // 72 < 72
    assert(!c.lt(-12));         // !(72 < -12)
    assert(!c.lt(c));           // !(72 < 72)
    assert(c.add(1).eq(73));
 
    cout << "Success!\n";

    return 0;
}
