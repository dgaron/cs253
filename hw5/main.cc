#include <unistd.h> // getopt
#include <iostream> // cout & cin
#include <string>   // string
#include <fstream>  // ifstream

#include "Counter.h"

using namespace std;

// Convert string argument to int
//
// throws invalid_argument exception if string cannot be converted
int processArgument(const string &arg) {
    char *c1;
    int val = strtol(arg.c_str(), &c1, 10);
    // Inspect the end character
    if (*c1 != 0) {
        throw invalid_argument("Integer bounds must be specified: lowerBound-upperBound");
    }
    return val;
}

// Read numbers from the stream
//
// throws out_of_range exception upon reading invalid number
// throws invalid_argument exception upon read failure
void readNumbers(istream &in, Counter &numbers) {
    for (int currentNumber; in >> currentNumber; ) {
        if (currentNumber < numbers.getLB() || currentNumber > numbers.getUB()) {
            throw out_of_range(to_string(currentNumber) + " is outside of acceptable range " +
                               "[" + to_string(numbers.getLB()) + "," + 
                               to_string(numbers.getUB()) + "]");
        } else {
            // Subtract lower bound to current number to correctly align with index
            // values starting at 0
            numbers.add(currentNumber);
        }
    }
    if (in.fail() && !in.eof()) {
        throw invalid_argument("Input read failure: Program accepts integers only");
    }
}


int main(int argc, char* argv[]) {

    // -r option flag
    // int for bounds set to default values 0 - 99
    bool boundsPassed = false;
    string bounds;
    int lowerBound = 0;
    int upperBound = 99;

    // -f option flag
    // sets printSecond to false
    bool printFirst = true;
    // -s option flag
    // sets printFirst to false
    bool printSecond = true;

    // -c option flag
    bool separatorPassed = false;
    string sep = ","; 

    // -v option flag
    bool verbose = false;

    // Option string
    // + stops option processing after the first non-option argument is encountered
    // r allows the user to specify the bounds
    //   -- argument required
    // f indicates that the first line of output is desired
    // s indicates that the second line of output is desired
    //   -- both output lines enabled by default
    //   -- selecting one, disables the other unless both are selected
    // c allows the user to specify a separator for the second output line
    //   -- argument required
    // v indicates that the source of input should be printed
    const char *optionString = "+r:fsc:v";

    int opt;
    while ((opt = getopt(argc, argv, optionString)) != -1) {
        switch (opt) {
            case 'r':
                if (boundsPassed) {
                    cerr << argv[0] << ": " << "Bounds may only be specified once" << '\n';
                    return 1;
                }
                boundsPassed = true;
                bounds = optarg;
                break;
            case 'f':
                printSecond = false;
                break;
            case 's':
                printFirst = false;
                break;
            case 'c':
                if (separatorPassed) {
                    cerr << argv[0] << ": " << "Separator may only be specified once" << '\n';
                    return 1;
                }
                separatorPassed = true;
                sep = optarg;
                break;
            case 'v':
                verbose = true;
                break;
            default:
                // Invalid option -- getopt prints an error by default
                return 1;
        }
    }

    if (!printSecond && !printFirst) {
        printFirst = true;
        printSecond = true;
    }
    if (separatorPassed && !printSecond) {
        cerr << argv[0] << ": " << "Separator passed with disabled output" << '\n';
        return 1;
    }

    // Deal with arg string from getopt
    if (boundsPassed) {
        try {
            int hyphen = bounds.find("-");
            if (hyphen == 0) {
                hyphen = bounds.find("-", 1);
            }  
            if (hyphen == -1) {
                throw invalid_argument("Integer bounds must be specified: lowerBound-upperBound");
            }
            lowerBound = processArgument(bounds.substr(0, hyphen));
            upperBound = processArgument(bounds.substr(hyphen + 1, bounds.length()));
        } catch (const invalid_argument &e) {
            cerr << argv[0] << ": Invalid argument for -r: " << bounds << '\n' << e.what() << '\n';
            return 1;
        }   
    }

    // Verify that lower bound is less than upper bound
    if (lowerBound > upperBound) {
        cerr << argv[0] << ": Lower bound must be less than or equal to upper bound" << '\n';
        return 1;
    }

    // Counter object will store the array and deal with cleanup
    Counter numbers(lowerBound, upperBound);

    // Read integers from standard input or file(s)
    if (optind >= argc) {
        // If no file arguments passed, read from input
        if (verbose) {
            cout << "Reading from standard input" << '\n';
        }
        try {
            readNumbers(cin, numbers);
        } catch (const logic_error &e) {
            cerr << argv[0] << ": " << e.what() << '\n';
            return 1;
        }
    } else {
        for (int i = optind; i < argc; ++i) {
            if (verbose) {
                cout << "Reading from " << argv[i] << '\n';
            }
            // If file arguments provided, pass each file name to file reader function
            ifstream inFile(argv[i]);
            // Ensure file opened successfully, print error message if not
            if (inFile) {  
                // Read numbers from the file using the specified input stream
                try {
                    readNumbers(inFile, numbers);
                } catch (const logic_error &e) {
                    cerr << argv[0] << ":" << '\n'
                         << e.what() << '\n';
                    return 1;
                }
            } else {  
                cerr << argv[0] << ": " << "unable to open file: " << argv[i] << '\n';
                return 1;
            }
        }
    }

    if (printFirst) {
        numbers.printNxQ();
    }

    if (printSecond) {
        numbers.printNQTimes(sep);
    }

    return 0;
}
