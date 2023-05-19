#include <iostream>

#include "print_c_array.h"

using namespace std;

void printNxQ(const int *numbers, int length, int lowerBound) {
    string separator = "";
    for (int i = 0; i < length; ++i) {
        if (!numbers[i]) {
            continue;
        }
        // Add lower bound to i to correct for possible non-zero lower bound
        cout << separator << (i + lowerBound)<< 'x' << numbers[i];
        separator = " ";
    }
    cout << '\n';
}

void printNQTimes(const int *numbers, int length, int lowerBound) {
    string separator = "";
    for (int i = 0; i < length; ++i) {
        if(!numbers[i]) {
            continue;
        }
        for (int j = 0; j < numbers[i]; ++j) {
            // Add lower bound to i to correct for possible non-zero lower bound
            cout << separator << (i + lowerBound);
            separator = ",";
        }
    }
    cout << '\n';
}
