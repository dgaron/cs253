#include <iostream>

#include "print_c_array.h"

using namespace std;

void printNxQ(const int *numbers, int length) {
    bool isFirst = true;
    for (int i = 0; i < length; ++i) {
        if (!numbers[i]) {
            continue;
        }
        if (!isFirst) {
            cout << ' ';
        } else { 
            isFirst = false;
        }
        cout << i << 'x' << numbers[i];
    }
    cout << '\n';
}

void printNQTimes(const int *numbers, int length) {
    bool isFirst = true;
    for (int i = 0; i < length; ++i) {
        if(!numbers[i]) {
            continue;
        }
        for (int j = 0; j < numbers[i]; ++j) {
            if (!isFirst) {
                cout << ',';
            } else {
                isFirst = false;
            }
            cout << i;
        }
    }
    cout << '\n';
}
