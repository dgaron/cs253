#include <iostream>
#include <cstdlib>

#include "print_c_array.h"

using namespace std;

int main(int argc, char *argv[]) {

    constexpr int kNumbersLength {100};
    constexpr int kLowerBound {0};
    constexpr int kUpperBound {99}; 

    if (argc > 1) {
        cerr << "Program: " << argv[0] << '\n'
             << "Error: This program accepts no arguments" << '\n';
        exit(1);
    }

    int numbers[kNumbersLength] {0};

    for (int currentNumber; cin >> currentNumber; ) {
        if (currentNumber < kLowerBound || currentNumber > kUpperBound) {
            cerr << "Program: " << argv[0] << '\n'
                 << "Error: " << currentNumber << " is outside of acceptable range" << '\n'
                 << "Please enter integers between " << kLowerBound << " and " << kUpperBound << ", inclusive" << '\n';
            exit(1); 
        } else {
            ++numbers[currentNumber];
        }
    }

    // Print numbers array in NxQ format
    // e.g., for input: 1 1 2 2 3
    // Output is: 1x2 2x2 3x1
    printNxQ(numbers, kNumbersLength);

    // Print numbers array in comma separated N Q times format
    // e.g., for input: 1 1 2 2 3
    // Output is: 1,1,2,2,3
    printNQTimes(numbers, kNumbersLength);

    return 0;
}
