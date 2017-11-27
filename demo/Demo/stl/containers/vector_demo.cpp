#include "../../include/stl/containers/vector_demo.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <string>

// http://en.cppreference.com/w/cpp/language/function_template
template<class T> void PrintAllElements(const std::vector<T>& v)
{
    for(auto it = v.begin(); it != v.end(); it++)
        std::cout <<  *it << std::endl;
}

void VectorDemo::Demo()
{
    PrintAllElementsTest();
    ConstructorsDemo();
    InsertDemo();
    IndexOperatorDemo();
    AtDemo();
}

void VectorDemo::PrintAllElementsTest()
{
    std::cout << "VectorDemo::PrintAllElementsTest()" << std::endl;

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    PrintAllElements<int>(v1);
}

void VectorDemo::ConstructorsDemo()
{
    std::cout << "VectorDemo::ConstructorsDemo()" << std::endl;

    // construct vector with 3 empty strings
    const int kInitialCount = 3;
    std::vector<std::string> vector_empty_strings(kInitialCount);
    assert(vector_empty_strings.size() == kInitialCount);
    assert(vector_empty_strings.capacity() == kInitialCount);
    assert(vector_empty_strings[0].empty());
    assert(vector_empty_strings[1].empty());
    assert(vector_empty_strings[2].empty());
    PrintAllElements<std::string>(vector_empty_strings);

    // construct vector with 3 strings "abc"
    std::vector<std::string> vector_strings(kInitialCount, "abc");
    assert(vector_strings.size() == kInitialCount);
    assert(vector_strings[0] == "abc");
    assert(vector_strings[1] == std::string("abc"));
    assert(!vector_strings[2].empty());
    PrintAllElements<std::string>(vector_strings);
}


void VectorDemo::PushBackDemo()
{
    std::cout << "VectorDemo::PushBackDemo()" << std::endl;

    // construct vector with 3 empty strings
    // const int kInitialCount = 3;
    // std::vector<std::string> vector_empty_strings(kInitialCount);
    // assert(vector_empty_strings.size() == kInitialCount);
    // assert(vector_empty_strings[0].empty());
    // assert(vector_empty_strings[1].empty());
    // assert(vector_empty_strings[2].empty());
    // PrintAllElements<std::string>(vector_empty_strings);

    // // construct vector with 3 strings "abc"
    // std::vector<std::string> vector_strings(kInitialCount, "abc");
    // assert(vector_strings.size() == kInitialCount);
    // assert(vector_strings[0] == "abc");
    // assert(vector_strings[1] == std::string("abc"));
    // assert(!vector_strings[2].empty());
    // PrintAllElements<std::string>(vector_strings);
}


void VectorDemo::InsertDemo()
{
    std::cout << "VectorDemo::InsertDemo()" << std::endl;

    const int kInitialCount = 3;

    // construct vector with 3 strings "abc"
    std::vector<std::string> vector_strings(kInitialCount, "abc");
    assert(vector_strings.size() == kInitialCount);
    assert(vector_strings.capacity() == kInitialCount);
    PrintAllElements<std::string>(vector_strings);

    // insert some new string before the existing first element
    auto it = vector_strings.insert(vector_strings.begin(), "inserted1");

    // after inserting one element, size grows by 1
    assert(vector_strings.size() == kInitialCount + 1);

    // capacity growth is compiler-dependent
#ifdef _MSC_VER
    assert(vector_strings.capacity() == kInitialCount + 1);
#else // GCC
    // if insertion requires resizing, vector usually doubles the capacity
    // (before inserton)
    assert(vector_strings.capacity() == kInitialCount * 2);
#endif

    // insertion shifts all subsequent elements one place towards the end
    assert(vector_strings[0] == "inserted1");
    assert(vector_strings[1] == std::string("abc"));
    assert(vector_strings[2] == "abc");
    assert(vector_strings[3] == std::string("abc"));

    // insert() returns iterator which points to the inserted element
    assert(*it == "inserted1");

    std::cout << "Elements after insertion: " << std::endl;
    PrintAllElements<std::string>(vector_strings);

    // Now size iz 4 and capacity is 6. If we add 3 more items:
    // capacity:
    //    gcc: will double before insertion and should be 12
    //   msvc: TODO: find out the rule how MSVC compiler increases capacity
    // size:
    //    7 (after insertion)
    vector_strings.insert(vector_strings.begin(), "inserted2");
    vector_strings.insert(vector_strings.begin(), "inserted3");
    vector_strings.insert(vector_strings.begin(), "inserted4");

    assert(vector_strings.size() == kInitialCount + 1 + 3);

#ifdef _MSC_VER
    auto cap = vector_strings.capacity();
    // assert(vector_strings.capacity() == ???);
#else  // GCC
    assert(vector_strings.capacity() == kInitialCount * 2 * 2);
#endif

    std::cout << "Elements after insertion: " << std::endl;
    PrintAllElements<std::string>(vector_strings);
}

// http://www.cplusplus.com/reference/vector/vector/operator[]/
void VectorDemo::IndexOperatorDemo()
{
    std::cout << "VectorDemo::IndexOperatorDemo()" << std::endl;

    std::vector<int> v;

    try
    {
        // MSVC: undefined behaviour; VSCode just reexecutes this line
        // auto val_0 = v[0];
    }
    catch(const std::exception& exc)
    {
        std::cerr << "Excepton caught: " << exc.what() << std::endl;
    }
}

void VectorDemo::AtDemo()
{
    std::cout << "VectorDemo::AtDemo()" << std::endl;

    std::vector<int> v;

    try
    {
        auto val_0 = v.at(0);
    }
    catch(const std::exception& exc)
    {
        // for MSVC the output is: "invalid vector<T> subscript"
        std::cerr << "Excepton caught: " << exc.what() << std::endl;
    }
}