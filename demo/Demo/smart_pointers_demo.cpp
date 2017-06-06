#include "include/smart_pointers_demo.h"

#include <memory>
#include <iostream>
using std::cout;
using std::endl;

void SmartPointersDemo::Demo()
{
    SharedPtrDemo();
    SharedPtrSwapDemo();
}

void SmartPointersDemo::SharedPtrDemo()
{
    cout << "sp1 instantiated but not initialized" << endl;
    std::shared_ptr<int> sp1;

    // no need to use longer syntax: if (sp1 == nullptr)
    if (!sp1)
    {
        cout << "sp1 is nullptr" << endl;
    }
    else
    {
        cout << "*sp1 = " << *sp1 << endl;
    }
    
    cout << "sp2 instantiated and initialized with 'new'" << endl;
    std::shared_ptr<int> sp2(new int(123));
    cout << "*sp2 = " << *sp2 << endl;

    // error: conversion from ‘int*’ to non-scalar type ‘std::shared_ptr<int>’ requested
    // std::shared_ptr<int> sp3 = new int(123);
    // cout << "*sp3 = " << *sp3 << endl;

    cout << "sp3 instantiated and initialized from sp2 via copy c-tor" << endl;
    std::shared_ptr<int> sp3(sp2);
    cout << "*sp3 = " << *sp3 << endl;
    cout << "*sp2 = " << *sp2 << endl;

    cout << "sp4 instantiated and initialized from sp3 via assignment operator" << endl;
    std::shared_ptr<int> sp4 = sp3;
    cout << "*sp4 = " << *sp4 << endl;
    cout << "*sp3 = " << *sp3 << endl;

    cout << "sp5 instantiated and initialized via make_shared" << endl;
    std::shared_ptr<int> sp5 = std::make_shared<int>(456);
    cout << "*sp5 = " << *sp5 << endl;

    cout << "sp6 instantiated (but not initialized) via make_shared" << endl;
    std::shared_ptr<int> sp6 = std::make_shared<int>();
    cout << "*sp6 = " << *sp6 << endl;
}

void SmartPointersDemo::SharedPtrSwapDemo()
{
    cout << "SmartPointersDemo::SharedPtrSwapDemo()" << endl;

    std::shared_ptr<int> sp1(new int(123));
    std::shared_ptr<int> sp2(new int(456));

    cout << "Before swap: " << endl;
    cout << "*sp1 = " << *sp1 << endl;
    cout << "*sp2 = " << *sp2 << endl;
    
    std::swap(sp1, sp2);
    
    cout << "After swap: " << endl;
    cout << "*sp1 = " << *sp1 << endl;
    cout << "*sp2 = " << *sp2 << endl;

    sp1.swap(sp2);

    cout << "After another swap: " << endl;
    cout << "*sp1 = " << *sp1 << endl;
    cout << "*sp2 = " << *sp2 << endl;
}