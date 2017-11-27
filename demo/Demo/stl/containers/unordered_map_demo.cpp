#include "../../include/stl/containers/unordered_map_demo.h"

#include <string>
#include <unordered_map> 
#include <cassert>

void UnorderedMapDemo::Demo()
{
    IndexOperatorDemo();
}

void UnorderedMapDemo::IndexOperatorDemo()
{
    std::unordered_map<std::string, int> uomap;
    uomap["one"] = 1;
    auto value_1 = uomap["one"];
    assert(uomap.size() == 1);
    assert(value_1 == 1);

    // overwrite old value that belongs to the same key
    uomap["one"] = 11;

    // returns reference to a value if key exists
    value_1 = uomap["one"];
    assert(value_1 == 11);

    // operator[] inserts a new element if key does not exist
    auto value_2 = uomap["two"];
    assert(uomap.size() == 2);
    assert(value_2 == 0);
}