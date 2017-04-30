#include "../include/stl/vector_demo.h"
#include <iostream>
#include <vector>

// http://en.cppreference.com/w/cpp/language/function_template
template<class T> void PrintAllElements(const std::vector<T>& v)
{
    for(auto it = v.begin(); it != v.end(); it++)
        std::cout <<  *it << std::endl;
}

void VectorDemo::Demo()
{
    PrintAllElementsDemo();
}

void VectorDemo::PrintAllElementsDemo()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    PrintAllElements<int>(v);
}