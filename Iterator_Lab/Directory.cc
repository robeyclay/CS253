#include "Directory.h"
#include <iostream>

using namespace std;

// The directory iterator pre-fetches the name.  That is, readdir()
// is called when you first create the iterator, and upon ++.
//
// An end() iterator is designated by a null pointer for its DIR *.
// When readdir() fails, we set our pointer to null.

DirectoryIterator::DirectoryIterator(DIR *dp_arg) : dp(dp_arg) {
    ++*this;				// get that first entry
}

// Get the next entry in the directory (that we like) and
// put it in the member variable name.

DirectoryIterator &DirectoryIterator::operator++() {	// pre-increment
    while (auto p = readdir(dp)) {	// Read a directory entry.
	name = p->d_name;
	if (wanted(name))		// Fix #2
	    return *this;		// Fix #2
	else				// Fix #2
	   continue;			// Fix #2
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




//////////////// Directory methods

Directory::Directory(const char dirname[]) {
    if (opendir(dirname)) { //Fix #1
	cout << "directory ctor\n"; //Fix #1
	dp = opendir(dirname); //Fix #1
    } else { //Fix #1
	try{ //Fix #1
	throw runtime_error("ERROR: Failed to open directory"); //Fix #1
	} catch (...) { //Fix #1
	    throw; //Fix #1
	    exit(0); //Fix #1
	}
    }
}

Directory::~Directory() {
    if (dp)				// Only if opendir() succeeded:
	closedir(dp);			//   should we close it.
}

Directory::iterator Directory::begin() const {
    return iterator(dp);
}

Directory::iterator Directory::end() const {
    return iterator();
}
