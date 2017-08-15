#include "../../include/stl/containers/array_demo.h"

#include <iostream>
#include <array>
#include <string>
#include <cassert>

#include "../../include/class_with_no_default_ctor.h"
#include "../../include/class_with_no_public_ctor.h"

void ArrayDemo::Demo()
{
    //PrintAllElementsTest();
    ConstructorsDemo();
    // InsertDemo();
}

void ArrayDemo::ConstructorsDemo()
{
    std::cout << "ArrayDemo::ConstructorsDemo()" << std::endl;

    const int kArraySize = 3;
    std::array<std::string, kArraySize> string_array = { "first", "second" };

    assert(string_array.size() == kArraySize);
    assert(string_array[0] == "first");
    assert(string_array[1] == "second");
    assert(string_array[2] == "");

    //
    // error C2073: 'std::array<ClassWithNoDefaultConstructor,3>::_Elems': 
    // elements of partially initialized array must have a default constructor
    //
    // std::array<ClassWithNoDefaultConstructor, kArraySize> array2 = { 
    //     ClassWithNoDefaultConstructor(1),
    //     ClassWithNoDefaultConstructor(2)
    // };

    //
    // error C2248: 'ClassWithNoPublicConstructor::ClassWithNoPublicConstructor'
    // : cannot access private member declared in class 
    // 'ClassWithNoPublicConstructor'
    //
    // std::array<ClassWithNoPublicConstructor, kArraySize> array2 = { 
    //     ClassWithNoPublicConstructor(),
    //     ClassWithNoPublicConstructor()
    // };
}