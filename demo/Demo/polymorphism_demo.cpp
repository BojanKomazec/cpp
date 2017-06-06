#include "include/polymorphism_demo.h"
#include <iostream>
using std::cout;
using std::endl;

void Base::Foo() const
{
    cout << "Base::Foo()" << endl;
}

void Derived1::Foo() const
{
    cout << "Derived1::Foo()" << endl;
}

void Derived2::Foo() const
{
    cout << "Derived2::Foo()" << endl;
}

void PolymorphismDemo::Demo()
{
    SlicingDemo();
}

void PolymorphismDemo::SlicingDemo()
{
    Base b;
    Derived1 d1;

    CallVirtualMethodOnBasePassedByValue(b);
    CallVirtualMethodOnBasePassedByValue(d1);
    CallVirtualMethodOnBasePassedByReference(b);
    CallVirtualMethodOnBasePassedByReference(d1);
}

// Slicing : When instance of derived type is passed by value to a method 
// which expects instance of the base class - object is sliced - only base
// part is passed.
void PolymorphismDemo::CallVirtualMethodOnBasePassedByValue(Base base)
{
    base.Foo();
}

void PolymorphismDemo::CallVirtualMethodOnBasePassedByReference(const Base& base)
{
    base.Foo();
}