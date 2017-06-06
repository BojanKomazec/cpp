#include "../../include/stl/containers/set_demo.h"
#include <set>
#include <cassert>
#include <iostream>

void SetDemo::Demo() {
    this->DemoImpl();
}

void SetDemo::DemoImpl() {
    std::set<int> set1;
    auto it = set1.insert(3);
}

