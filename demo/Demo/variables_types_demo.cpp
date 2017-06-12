#include "include/variables_types_demo.h"
#include <iostream>
#include <limits>

// constexpr function
constexpr int f1() { return 0; }
constexpr int f2(int a, int b) { return a + b; }

void VariablesTypesDemo::Demo()
{
    NumericLimitsDemo();
    AutoDemo();
}

// unsigned long long: 0 -> 18446744073709551615
void VariablesTypesDemo::NumericLimitsDemo()
{
    std::cout << "VariablesTypesDemo::NumericLimitsDemo()" << std::endl;

    std::cout << "unsigned long long:"
            << "\n\t" << std::numeric_limits<unsigned long long>::lowest()
            << "\n\t" << std::numeric_limits<unsigned long long>::max() 
            << std::endl;
}

// http://www.stroustrup.com/C++11FAQ.html#auto
void VariablesTypesDemo::AutoDemo()
{
    std::cout << "VariablesTypesDemo::AutoDemo()" << std::endl;

    auto number = 155597374375995873326345038373738494;
    std::cout << "number = " << number << std::endl;

    auto number2 = std::numeric_limits<unsigned long long>::max();
    std::cout << "number2 = " << number2 << std::endl;

    auto number3 = std::numeric_limits<unsigned long long>::max() - 1;
    std::cout << "number3 = " << number3 << std::endl;

    const int& intRef = 123;
    auto& autoRef = intRef;
    std::cout << "autoRef = " << autoRef << std::endl;
}

// http://en.cppreference.com/w/cpp/language/constexpr
void VariablesTypesDemo::ConstExpressionDemo()
{
    // constexpr variable 
    constexpr auto v1 = 123;
    constexpr auto v2 = 1 + 2;
    constexpr auto v3 = "This is some string";    
}



