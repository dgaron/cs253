#include "Directory.h"
#include <iostream>
#include <stdexcept> // For runtime_error

using namespace std;

// The directory iterator pre-fetches the name.  That is, readdir()
// is called when you first create the iterator, and upon ++.
//
// An end() iterator is designated by a null pointer for its DIR *.
// When readdir() fails, we set our pointer to null.

// Part of Fix #3 involved adding a data member to store the match string
DirectoryIterator::DirectoryIterator(DIR *dp_arg, string match) : dp(dp_arg),
                                                                  match(match) {
    ++*this;				// get that first entry
}

// Get the next entry in the directory (that we like) and
// put it in the member variable name.

DirectoryIterator &DirectoryIterator::operator++() {	// pre-increment
    // Fix #2
    if (wanted()) {
        return *this;
    }
    dp = nullptr;			// readdir failed; don’t try again.
    return *this;
}

string DirectoryIterator::operator*() const {
    return name;			// Fetched in a previous ++.
}

bool DirectoryIterator::operator!=(const DirectoryIterator &rhs) const {
    return dp != rhs.dp;
}

// Fix #2
bool DirectoryIterator::wanted() {
    while (auto p = readdir(dp)) {	// Read a directory entry.
    	name = p->d_name;		// C-string ⇒ C++ string
	    if (name == ".")		// Stupid entry for current directory?
	        continue;			// Nobody wants that.
	    if (name == "..")		// Stupid entry for parent directory?
	        continue;			// Nobody wants that.
        // Fix #3
	    if (name.find(match) != string::npos)
            return true;			// Everything else, I like!
    }
    return false;
}


//////////////// Directory methods

Directory::Directory(const char dirname[], string match) : dp(opendir(dirname)),
                                                           match(match) { 
    // Fix #1
    // If dp is null, opendir() failed, throw runtime_error
    if (!dp) {
        throw runtime_error("Unable to open directory stream");
    }
}

Directory::~Directory() {
    if (dp)				// Only if opendir() succeeded:
	closedir(dp);			//   should we close it.
}

Directory::iterator Directory::begin() const {
    return iterator(dp, match);
}

Directory::iterator Directory::end() const {
    return iterator();
}
