#include "../include/stl/iterator_demo.h"
#include <iterator>
#include <vector>
#include <cassert>
#include <iostream>

void IteratorDemo::Demo() {
    BeginEndDemo();
}

void IteratorDemo::BeginEndDemo() {
    auto v = std::vector<char>{ 'a', 'b', 'c' };

    auto it1 = std::begin(v);
    assert((*it1) == 'a');

    while(it1 != std::end(v)) {
        std::cout << *it1 << "\n";
        ++it1;
    }

    // std::end returns iterator pointint to the first element past the last valid!
    auto it2 = std::end(v);
    assert((*(--it2)) == 'c');
}