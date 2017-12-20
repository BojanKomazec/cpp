#include "include/smart_pointers_demo.h"

#include <memory>
#include <iostream> // g++ indirectly pulls in <string> but cl does not
#include <string> // required by cl
#include <cassert>

using std::cout;
using std::endl;
using std::shared_ptr;

struct S
{
    S() { std::cout << "S c-tor" << std::endl; }
    S(int i, std::string s) :  IntField(i), StrField(s) { std::cout << "S(int, string) c-tor" << std::endl; }
    ~S() { std::cout << "S d-tor" << std::endl; }

    int IntField;
    std::string StrField;
};

struct S2
{
    S2(int i) { std::cout << "S2 c-tor" << std::endl; }
    ~S2() { std::cout << "S2 d-tor" << std::endl; }
};

class SharedPointerHolder
{
public:
    std::shared_ptr<S> CreateS() {
        sp_ = std::shared_ptr<S>(new S());
        cout << "SharedPointerHolder::CreateS(): sp_.use_count = " << sp_.use_count() << endl;
        return sp_;
    }

        
    // a copy of pS is made and ref count increments; method can change S but NOT original shared_ptr
    void MethodWithSharedPtrPassedByValueAsArg(std::shared_ptr<S> pS, int newIntFieldValue, int newIntFieldValue2) {
        cout << "SharedPointerHolder::MethodWithSharedPtrPassedByValueAsArg()" << endl;
        cout << "pS.use_count = " << pS.use_count() << endl;

        pS->IntField = newIntFieldValue;
        assert(pS->IntField == newIntFieldValue);

        cout << "SharedPointerHolder::MethodWithSharedPtrPassedByValueAsArg(): reassigning pS..." << endl;
        pS = std::make_shared<S>(newIntFieldValue2, "");
        assert(pS->IntField == newIntFieldValue2);
    }

    // ref count does NOT increment; method can change S AND shared_ptr 
    void MethodWithSharedPtrPassedByRefAsArg(std::shared_ptr<S>& pS, int newIntFieldValue, int newIntFieldValue2) {
        cout << "SharedPointerHolder::MethodWithSharedPtrPassedByRefAsArg()" << endl;
        cout << "pS.use_count = " << pS.use_count() << endl;

        if (pS == nullptr) {
            cout << "WARNING: pS is nullptr." << endl;
        }
        else {
            pS->IntField = newIntFieldValue;
            assert(pS->IntField == newIntFieldValue);

            cout << "SharedPointerHolder::MethodWithSharedPtrPassedByRefAsArg(): reassigning pS..." << endl;
            pS = std::make_shared<S>(newIntFieldValue2, "");
            assert(pS->IntField == newIntFieldValue2);
        }
    }

private:
    std::shared_ptr<S> sp_;
};

void SmartPointersDemo::Demo()
{
    SharedPtrConstructionDemo();
    SharedPtrSwapDemo();
    SharedPtrDestructionDemo();
    MethodReturnsSharedPtrDemo();
    PassingSharedPtrByValueDemo();
    PassingSharedPtrByRefDemo();
}

void SmartPointersDemo::SharedPtrConstructionDemo()
{
    cout << "sp1 instantiated but not initialized" << endl;
    std::shared_ptr<int> sp1;

    // no need to use longer syntax: if (sp1 != nullptr)
    if (sp1)
    {
        cout << "*sp1 = " << *sp1 << endl;
    }
    else
    {
        cout << "sp1 is nullptr" << endl;
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

    // Using std::make_shared<T> when T's c-tor has arguments
    shared_ptr<S> sp7 = std::make_shared<S>(123, "test");
    cout << "*sp7.IntField = " << (*sp7).IntField << endl;
    cout << "*sp7.StrField = " << (*sp7).StrField << endl;

    // shared_ptr<S2> sp8 = std::make_shared<S2>(); // error:  note:   candidate expects 1 argument, 0 provided

    shared_ptr<int> sp9 = nullptr;
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

void SmartPointersDemo::SharedPtrDestructionDemo()
{
    cout << "SmartPointersDemo::SharedPtrDestructionDemo()" << endl;

    shared_ptr<S> sp1(new S());
    cout << "Created sp1. use_count = " << sp1.use_count() << endl;

    {
        shared_ptr<S> sp2(sp1);
        cout << "Created sp2. sp1.use_count = " << sp1.use_count() << endl;
        cout << "sp2.use_count = " << sp2.use_count() << endl;
    }

    cout << "sp2 destroyed (got out of the scope). use_count = " << sp1.use_count() << endl;

    sp1.reset();
    cout << "sp1 reset. use_count = " << sp1.use_count() << endl;
}

void SmartPointersDemo::MethodReturnsSharedPtrDemo()
{
    cout << "SmartPointersDemo::MethodReturnsSharedPtrDemo()" << endl;

    SharedPointerHolder sph;
    std::shared_ptr<S> s = sph.CreateS();
    cout << "s.use_count = " << s.use_count() << endl;
}

void SmartPointersDemo::PassingSharedPtrByValueDemo()
{
    cout << "SmartPointersDemo::PassingSharedPtrByValueDemo()" << endl;

    SharedPointerHolder sph;
    shared_ptr<S> pS = std::make_shared<S>(1, "one");

    sph.MethodWithSharedPtrPassedByValueAsArg(pS, 2, 3);
    assert(pS->IntField == 2);
}

void SmartPointersDemo::PassingSharedPtrByRefDemo()
{
    cout << "SmartPointersDemo::PassingSharedPtrByRefDemo()" << endl;

    SharedPointerHolder sph;
    shared_ptr<S> pS = std::make_shared<S>(1, "one");

    const int old_int_value = 2;
    const int new_int_value = 3;
    sph.MethodWithSharedPtrPassedByRefAsArg(pS, old_int_value, new_int_value);
    assert(pS->IntField == new_int_value);

    shared_ptr<S> pS2 = nullptr;
    sph.MethodWithSharedPtrPassedByRefAsArg(pS2, 0, 0);
}