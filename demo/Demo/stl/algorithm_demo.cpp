#include "../include/stl/algorithm_demo.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <cassert>
#include <iostream>

void AlgorithmDemo::Demo() {
    RemoveDemo();
    RemoveIfDemo();
}

// (!) Removing is done by shifting the elements in the range in such a way that 
// the elements that are not to be removed appear in the beginning of the range. 
// Relative order of the elements that remain is preserved and the physical size 
// of the container is unchanged.
//
// A call to remove is typically followed by a call to a container's erase method, 
// which erases the unspecified values and reduces the physical size of the 
// container to match its new logical size.
//
// This function contains an example of "Erase-remove" idiom.
void AlgorithmDemo::RemoveDemo() {
    std::string s = {"This is a string."};
    auto it = std::remove(std::begin(s), std::end(s), ' ' );

    // This assertion fails!
    //assert(s == "Thisisastring.");

    // (!) Elements between new logical and physical end are unspecified
    // but still dereferencable. Those are characters '.ng' at the end.
    assert(s == "Thisisastring.ng");

    // align physical end with logical one.
    s.erase(it, s.end());
    assert(s == "Thisisastring.");
}

void AlgorithmDemo::RemoveIfDemo() {
    
}