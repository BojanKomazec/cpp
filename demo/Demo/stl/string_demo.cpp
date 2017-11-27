#include "../include/stl/string_demo.h"
#include <iostream>
#include <string>
#include <cassert>

void StringDemo::Demo()
{
    AssignAppendDemo();
}

void StringDemo::AssignAppendDemo()
{
    std::string str;
    str.assign("This is");
    str.append(": ");
    str.append("cat");
    assert(str == "This is: cat");
    str.append("dog");
    //assert(str == "This is: dog");
}