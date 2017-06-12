#include "../../include/stl/containers/set_demo.h"
#include <set>
#include <cassert>
#include <iostream>

void SetDemo::Demo() {
    this->DemoImpl();
}

void SetDemo::DemoImpl() {
    std::cout << "SetDemo::DemoImpl()" << std::endl;

    std::set<int> set1;

    set1.insert(3);
    set1.insert(1);
    set1.insert(6);
    set1.insert(2);

    std::cout << "Iterating through set members (classic iterator): " << std::endl;

    for (std::set<int>::iterator it = set1.begin(); it != set1.end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "Iterating through set members (range-based for loop - C++11): " << std::endl;
    for(const int& element : set1) {
        std::cout << element << std::endl;
    }

    std::cout << "Iterating through set members (range-based for loop - C++11, with auto): " << std::endl;
    for(const auto& element : set1) {
        std::cout << element << std::endl;
    }    
}

