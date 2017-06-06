#include "include/enum_demo.h" 
#include <iostream>

using std::cout;
using std::endl;

// conventional (traditional, classic, unscoped) enum
enum Colour
{
    Red,
    Blue,
    Green
};

// it is possible to define enum's underlying type
enum Vehicle : signed int
{
    Aeroplane,
    Bicycle,
    Car
};

// Classic enumeration type exports enumerators to the surrounding scope.
// Two classic enumeration types can't contain same enumerator - this leads to name clashes.
// enum Colour2
// {
//     Red,  // error: redeclaration of ‘Red’
//     Blue, // error: redeclaration of ‘Blue’
//     Green // error: redeclaration of ‘Green’
// };

// scoped enum (from C++11)
enum class Fruit
{
    Apples,
    Bananas,
    Clementines
};

enum class Fruit2
{
    Apples,
    Bananas,
    Clementines,
    Dates
};

// it is possible to define enum class' underlying type
enum class Vegetable : signed long
{
    Asparagus,
    Broccoli,
    Carrot
};

void EnumDemo::Demo()
{
    ConventionalEnumDemo();
    EnumClassDemo();
}

void EnumDemo::ConventionalEnumDemo()
{
    cout << "EnumDemo::ConventionalEnumDemo()" << endl;
    
    // classic enum can implicitly be converted to int 
    int i = Red;
    int j = Colour::Red;

    Colour colour = Red;
    // classic enums are implicitly convertible to int 
    cout << "colour = " << colour << endl;
}

void EnumDemo::EnumClassDemo()
{
    cout << "EnumDemo::EnumClassDemo()" << endl;

    // enum class can't implicitly be converted to int
    // int i = Fruit::Apples; // error: cannot convert ‘Fruit’ to ‘int’ in initialization

    Fruit fruit = Fruit::Apples;

    // Enum class enumerators reqiire enum type specifier
    // auto fruit2 = Apples;   // error: ‘Apples’ was not declared in this scope
    // Fruit2 fruit2 = Apples; // error: ‘Apples’ was not declared in this scope
    // Fruit2 fruit2 = Dates;  // error: ‘Dates’ was not declared in this scope

    // scoped enums are not implicitly convertible to int
    // cout << "fruit = " << fruit << endl; // mismatched types ‘const std::__cxx11::basic_string<_CharT, _Traits, _Alloc>’ and ‘Fruit’
    
    // it is possible to explicitly cast enum class to int (which can be then sent to cout)
    cout << "fruit = " << static_cast<int>(fruit) << endl;

    // even if underlying type is not int, enum class can be casted to int
    auto vegetable = Vegetable::Asparagus;
    cout << "vegetable = " << static_cast<int>(vegetable) << endl;
}