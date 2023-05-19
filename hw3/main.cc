#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include "print_c_array.h"

using namespace std;


void boboDestructor(int numbers[]) {
    delete[] numbers;
    exit(1);
}


int processArgument(const char *programName, const char *argVal) {
    // Exception handling to catch invalid command line arguments
    try {
        char *c1;
        int val = strtol(argVal, &c1, 10);
        // Inspect the end characters to see if you tried to sneak in a double
        if (*c1 != 0) {
            throw invalid_argument("Integer arguments only");
        }
        return val;
    } catch (const invalid_argument &e) {
        cerr << programName << ": " << e.what() << '\n';
        cerr << "Usage: " << programName << " lowerBound upperBound [input_file(s) ...]" << '\n';
        exit(1);
    }
}


void readNumbers(istream &in, int numbers[], int lowerBound, int upperBound) {
    for (int currentNumber; in >> currentNumber; ) {
        if (currentNumber < lowerBound || currentNumber > upperBound) {
            cerr << __func__ << ":" << '\n'
                 << "Error: " << currentNumber << " is outside of acceptable range" << '\n';
            boboDestructor(numbers);
        } else {
            // Subtract lower bound to current number to correctly align with index
            // values starting at 0
            ++numbers[currentNumber - lowerBound];
        }
    }
    if (in.fail() && !in.eof()) {
        cerr << __func__ << ":" << '\n'
             << "Input type error: integers only" << '\n';
        boboDestructor(numbers);;
    }
}


int main(int argc, char* argv[]) {

    // Verify the two mandatory arguments were passed, print usage message if not
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " lowerBound upperBound [input_file(s) ...]" << '\n';
        exit(1);
    } 
     
    // Convert argument strings to integers with type verification
    const int lowerBound = processArgument(argv[0], argv[1]);  
    const int upperBound = processArgument(argv[0], argv[2]); 

    // Verify that lower bound is less than upper bound
    if (lowerBound > upperBound) {
        cerr << argv[0] << ": Lower bound must be less than upper bound" << '\n';
        exit(1);
    }

    // Calculate size for the numbers array
    const int numbersSize = upperBound - lowerBound + 1;

    // Dynamically allocate space for numbers array
    int *numbers = new int[numbersSize]{0};

    /* 
     *  From this point on, any error condition will lead to a call to 
     *  boboDestructor(), ensuring that the dynamically allocated memory
     *  will be properly freed before program termination.
     *      - This includes any subsequent function calls
     */ 

    if (argc == 3) {
        // If no file arguments passed, read from input
        readNumbers(cin, numbers, lowerBound, upperBound);
    } else {
        // If file arguments provided, pass each file name to file reader function
        ifstream inFile;
        for (int i = 3; i < argc; ++i) {
            // Open file passed via command line
            inFile.open(argv[i]);
            // Ensure file opened successfully, print error message if not
            if (inFile.is_open()) {  
                // Read numbers from the file using the specified input stream
                readNumbers(inFile, numbers, lowerBound, upperBound);
                inFile.close();  
            } else {  
                cerr << argv[0] << ": Unable to open file: " << argv[i] << '\n';
                boboDestructor(numbers);;
            }
        }
    }

    // Print numbers array in NxQ format
    // e.g., for input: 1 1 2 2 3
    // Output is: 1x2 2x2 3x1
    printNxQ(numbers, numbersSize, lowerBound);

    // Print numbers array in comma separated N Q times format
    // e.g., for input: 1 1 2 2 3
    // Output is: 1,1,2,2,3
    printNQTimes(numbers, numbersSize, lowerBound);

    // Free dynamically allocated memory
    delete[] numbers;

    return 0;
}
