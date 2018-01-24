#include "../include/stl/iterator_demo.h"
#include <iterator>
#include <vector>
#include <cassert>
#include <iostream>

void IteratorDemo::Demo() {
    BeginEndDemo();
    ConstBeginEndDemo();
}

// Type: Container<T>::iterator
// std::begin(c) - Retrieves an iterator to the first element in a specified container.  
// std::end(c) - Retrieves an iterator to the element that follows the last element in the specified container.
void IteratorDemo::BeginEndDemo() {
    auto v = std::vector<char>{ 'a', 'b', 'c' };

    auto it1 = std::begin(v);

    // evaluation
    assert((*it1) == 'a');

    // iteration
    while(it1 != std::end(v)) {
        std::cout << *it1 << "\n";
        ++it1;
    }

    // modification
    *it1 = 'm';
    assert((*it1) == 'm');

    // std::end returns iterator pointint to the first element past the last valid!
    auto it2 = std::end(v);
    assert((*(--it2)) == 'c');
}

// const iterators
// Container<T>::const_iterator
// std::cbegin(c) - Retrieves a const iterator to the first element in a specified container.
// std::cend(c) - Retrieves a const iterator to the element that follows the last element in the specified container.
void IteratorDemo::ConstBeginEndDemo() {
    auto v = std::vector<char>{ 'a', 'b', 'c' };

    auto it1 = std::cbegin(v);

    // evaluation
    assert((*it1) == 'a');

    // modification
    // error C3892: 'it1': you cannot assign to a variable that is const
    // *it1 = 'm';

    // assert((*it1) == 'm');

    // iteration
    while(it1 != std::cend(v)) {
        std::cout << *it1 << "\n";
        ++it1;
    }

    // omit first element
    // reset it1 first. It is our duty to ensure that the iterator doesn't run past end()!
    it1 = std::cbegin(v);
    ++it1;
    while(it1 != std::cend(v)) {
        std::cout << *it1 << "\n";
        ++it1;
    }
}