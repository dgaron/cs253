#include <iostream>
#include "Directory.h"

using namespace std;

int main() {
    
    // try catch block added as part of Fix #1
    try {
        Directory dir(".", "object");
        for (auto name : dir)
	    cout << "Filename: " << name << '\n';
    } catch (const runtime_error &e) {
        cerr << e.what() << '\n';
    }

}

