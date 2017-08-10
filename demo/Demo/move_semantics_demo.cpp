#include "include/move_semantics_demo.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <typeinfo>

namespace {
    int ReturnInt() { return 2; }
}

template<typename T>
class MyBuffer
{
public:
    explicit MyBuffer(std::size_t size) : size_(size), p_(nullptr){
        std::cout << "MyBuffer::MyBuffer()" << std::endl;
        p_ = new T[size_];
    }

    // Copy c-tor allocates new memory and copies all elements, one by one from 
    // the other object. At the end there are two MyBuffer objects, containing 
    // same elements (at different memory locations). 
    MyBuffer(const MyBuffer& other) : size_(other.size_), p_(nullptr) {
        std::cout << "MyBuffer::MyBuffer(const MyBuffer& other)" << std::endl;
        p_ = new T[size_];
        for (size_t i = 0; i < size_; ++i) {
            // *(p_ + i) = *(other.p_ + i);
            p_[i] = other.p_[i];
        }
    }

    ~MyBuffer() noexcept {
        std::cout << "MyBuffer::~MyBuffer()" << std::endl;
        if (p_) {
            delete[] p_;
            p_ = nullptr;
        }
    }

    std::size_t GetSize()
    {
        return size_;
    }

    void Append(const T& t) {

    }
private:
    std::size_t size_;
    T* p_;
};


// The only difference from MyBuffer is that this class has move constructor
template<typename T>
class MyBuffer2
{
public:
    explicit MyBuffer2(std::size_t size) : size_(size), p_(nullptr){
        std::cout << "MyBuffer2::MyBuffer2()" << std::endl;
        p_ = new T[size_];
    }

    // Copy c-tor allocates new memory and copies all elements, one by one from 
    // the other object. At the end there are two MyBuffer objects, containing 
    // same elements (at different memory locations). 
    // Copy c-tor is performing expensive deep copy
    MyBuffer2(const MyBuffer2& other) : size_(other.size_), p_(nullptr) {
        std::cout << "MyBuffer2::MyBuffer2(const MyBuffer2& other)" << std::endl;
        p_ = new T[size_];
        for (size_t i = 0; i < size_; i++) {
            *(p_ + i) = *(other.p_ + i);
        }
    }

    // Move c-tor is performing cheap shallow copy
    MyBuffer2(MyBuffer2&& other) noexcept : size_(other.size_), p_(other.p_) {
        std::cout << "MyBuffer2::MyBuffer2(MyBuffer2&& other)" << std::endl;
        other.size_ = 0;
        other.p_ = nullptr;
    }

    ~MyBuffer2() noexcept {
        std::cout << "MyBuffer2::~MyBuffer2()" << std::endl;
        if (p_) {
            delete[] p_;
            p_ = nullptr;
        }
    }

    std::size_t GetSize()
    {
        return size_;
    }

    void Append(const T& t) {

    }
private:
    std::size_t size_;
    T* p_;
};

// The only difference from MyBuffer2 is that this class has move assignment operator
template<typename T>
class MyBuffer3
{
public:
    explicit MyBuffer3(std::size_t size) : size_(size), p_(nullptr){
        std::cout << "MyBuffer3::MyBuffer3()" << std::endl;
        p_ = new T[size_];
    }

    // Copy c-tor allocates new memory and copies all elements, one by one from 
    // the other object. At the end there are two MyBuffer objects, containing 
    // same elements (at different memory locations). 
    // Copy c-tor is performing expensive deep copy
    MyBuffer3(const MyBuffer3& other) : size_(other.size_), p_(nullptr) {
        std::cout << "MyBuffer3::MyBuffer3(const MyBuffer3MyBuffer3& other)" << std::endl;
        p_ = new T[size_];
        for (size_t i = 0; i < size_; i++) {
            *(p_ + i) = *(other.p_ + i);
        }
    }

    // Move c-tor is performing cheap shallow copy
    MyBuffer3(MyBuffer3&& other) noexcept : size_(other.size_), p_(other.p_) {
        std::cout << "MyBuffer3::MyBuffer3(MyBuffer3&& other)" << std::endl;
        other.size_ = 0;
        other.p_ = nullptr;
    }

    // MyBuffer3& operator=()

    ~MyBuffer3() noexcept {
        std::cout << "MyBuffer3::~MyBuffer3()" << std::endl;
        if (p_) {
            delete[] p_;
            p_ = nullptr;
        }
    }

    std::size_t GetSize()
    {
        return size_;
    }

    void Append(const T& t) {

    }
private:
    std::size_t size_;
    T* p_;
};

void MoveSemanticsDemo::Demo()
{
    // RValueReferenceDemo();
    // CopyElisionDemo();
    // CopyConstructorDemo();
    MoveConstructorDemo();
}

// Note the cases where temporary objects are created.
void MoveSemanticsDemo::ConstructorDemo()
{
    // MyBuffer2<char> myBuff2(MyBuffer2<char>(100)); // single c-tor is called

    // error: call of overloaded ‘UseBuffer(MyBuffer<char>)’ is ambiguous
    // candidate: void MoveSemanticsDemo::UseBuffer(MyBuffer<char>)
    // candidate: void MoveSemanticsDemo::UseBuffer(const MyBuffer<char>&)
    // UseBuffer(MyBuffer<char>(100));

    UseBuffer2(MyBuffer2<char>(100));

    // Copy c-tor is NOT called
    // error: call of overloaded ‘UseBuffer(MyBuffer<char>)’ is ambiguous
    // candidate: void MoveSemanticsDemo::UseBuffer(MyBuffer<char>)
    // candidate: void MoveSemanticsDemo::UseBuffer(const MyBuffer<char>&)
    // UseBuffer(CreateBuffer());

    // Move c-tor is NOT called
    UseBuffer2(CreateBuffer2());

    srand (time(NULL));
    MyBuffer<char> myBuff((rand() % 2) ? MyBuffer<char>(2) :  MyBuffer<char>(1));
    MyBuffer<char> myBuff2 = (rand() % 2) ? MyBuffer<char>(2) :  MyBuffer<char>(1);

    MyBuffer2<char> buff3(3);

    // If MyBuffer2 doesn't have move assignment operator defined:
    // error: use of deleted function ‘constexpr MyBuffer2<char>& MyBuffer2<char>::operator=(const MyBuffer2<char>&)’
    // buff3 = (rand() % 2) ? MyBuffer2<char>(2) :  MyBuffer2<char>(1);
    
    //myBuff3 = CreateBuffer()

    // MyBuffer2<char> myBuff2(MyBuffer2<char>(100)); // single c-tor is called

    // error: conversion from ‘MoveSemanticsDemo::MoveConstructorDemo()::<lambda()>’ to non-scalar type ‘MyBuffer2<char>’ requested
    // reason: we are only declaring lambda here but not calling it
    // MyBuffer2<char> myBuff2 = []() { return MyBuffer2<char>(100); };

    //MyBuffer2<char> myBuff2 = []{ return MyBuffer2<char>(100); }(); // throws exception

    // OK
    // auto myBuff2 = []()-> MyBuffer2<char> { return MyBuffer2<char>(100); }();
    // std::cout << typeid(myBuff2).name() << std::endl;
    
    // OK
    // MyBuffer2<char>&& myBuff3 = []{ return MyBuffer2<char>(100); }(); 

    
    // ?? c-tor
    UseBuffer2((rand() % 2) ? MyBuffer2<char>(2) :  MyBuffer2<char>(1));
}

// Note the cases where temporary objects are created.
void MoveSemanticsDemo::CopyConstructorDemo()
{
    std::cout << "MoveSemanticsDemo::CopyConstructorDemo()" << std::endl;

    // MyBuffer<char> myBuffer(100); // c-tor is called
    // MyBuffer<char> myBuff2(myBuffer); // copy c-tor is called

    // MyBuffer<char> myBuffer(100); // c-tor is called
    // MyBuffer<char> myBuff2 = myBuffer; // copy c-tor is called

    // const MyBuffer<char>& myBuff = MyBuffer<char>(100); // c-tor is called
    // MyBuffer<char> myBuff2(myBuff); // copy c-tor is called

    //MyBuffer<char> myBuff3(100);
    // copy c-tor
    //UseBuffer(myBuff3);
}

void MoveSemanticsDemo::MoveConstructorDemo()
{
    std::cout << "MoveSemanticsDemo::MoveConstructorDemo()" << std::endl;

    // OK
    //MyBuffer2<char> buff(std::move(MyBuffer2<char>(1)));
    
    // OK - calls move c-tor indeed
    //MyBuffer2<char> buff = std::move(MyBuffer2<char>(1));

    // OK
    //MyBuffer2<char> buff(std::move(CreateBuffer2()));

    // OK - calls move c-tor indeed
    MyBuffer2<char> buff = std::move(CreateBuffer2());

    // OK
    //UseBuffer2(std::move(MyBuffer2<char>(1)));

    // OK
    //UseBuffer2(std::move(CreateBuffer2()));

    std::cout << "MoveSemanticsDemo::~MoveConstructorDemo()" << std::endl;
}

void MoveSemanticsDemo::CopyElisionDemo()
{
    // Copy elision. 
    // MyBuffer<char> myBuff2 = MyBuffer<char>(100); // single c-tor is called

    // Copy elision. 
    // MyBuffer<char> myBuff2(MyBuffer<char>(100)); // single c-tor is called
}

void MoveSemanticsDemo::RValueReferenceDemo()
{
    std::cout << "MoveSemanticsDemo::RValueReferenceDemo()" << std::endl;

    int i = 1;
    int& r1 = i;
    r1 = 2;

    // error: invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’
    // int& r2 = ReturnInt();
    
    const int& cr1 = i;

    // error: assignment of read-only reference ‘cr1’
    // cr1 = 3;

    // Even in C++03 we could bind rvalue to a reference but it was CONST one; we could not modify rvalue!
    const int& cr2 = ReturnInt();
    // error: assignment of read-only reference ‘cr2’
    // cr2 = 3;

    // error: cannot bind ‘int’ lvalue to ‘int&&’
    // int&& rr1 = i;

    // From C++11, we can bind rvalue to a non-const reference - rvalue reference, with which we can modify rvalue!
    int&& rr1 = ReturnInt();
    rr1 = 3;


    int val = 5;
    int& lval_ref = val;

    // error: cannot bind ‘int’ lvalue to ‘int&&’
    // int&& rvalRef = a; 

    int&& rval_ref = 5;

    int&& rval_ref1 = std::move(val);
    int&& rval_ref2 = std::move(lval_ref);
    int&& rval_ref3 = std::move(rval_ref);

    FooWithIntArg(val);
    FooWithIntArg(lval_ref);
    FooWithIntArg(rval_ref);
    FooWithIntArg(5);

    FooWithLValRefArg(val);
    FooWithLValRefArg(lval_ref);
    FooWithLValRefArg(rval_ref);

    // error: invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’
    // FooWithLValRefArg(5);

    // error: cannot bind ‘int’ lvalue to ‘int&&’
    // Values with a name, so-called lvalues, cannot be	passed to rvalue references.
    // FooWithRValRefArg(val);
    FooWithRValRefArg(std::move(val));

    // error: cannot bind ‘int’ lvalue to ‘int&&’
    // FooWithRValRefArg(lval_ref);
    FooWithRValRefArg(std::move(lval_ref));

    // (!) error: cannot bind ‘int’ lvalue to ‘int&&’ 
    // rval_ref is itself a lvalue!
    // FooWithRValRefArg(rval_ref);
    // Note	that an rvalue reference like int&& rval_ref is not an rvalue itself but an lvalue as
    // it possesses a name. If we wanted to pass rval_ref to another method that helps the move
    // constructor with the	data robbery, we would have to turn it into an rvalue again with the
    // standard	function std::move.
    FooWithRValRefArg(std::move(rval_ref));

    // 5 is rvalue
    FooWithRValRefArg(5);

    // error: call of overloaded ‘Foo(int&)’ is ambiguous
    // note: candidate: void MoveSemanticsDemo::Foo(int)
    // note: candidate: void MoveSemanticsDemo::Foo(int&)
    // Foo(val);
    Foo(lval_ref);
    Foo(rval_ref);
    Foo(5);
}

void MoveSemanticsDemo::FooWithIntArg(int val)
{
    std::cout << "val = " << val << std::endl;
}

void MoveSemanticsDemo::FooWithLValRefArg(int& lval_ref)
{
    std::cout << "lval_ref = " << lval_ref << std::endl;
}

void MoveSemanticsDemo::FooWithRValRefArg(int&& rval_ref)
{
    std::cout << "rval_ref = " << rval_ref << std::endl;
}

// void MoveSemanticsDemo::Foo(int val)
// {
//     std::cout << "MoveSemanticsDemo::Foo(): val = " << val << std::endl;
// }

void MoveSemanticsDemo::Foo(int& lval_ref)
{
    std::cout << "MoveSemanticsDemo::Foo(): lval_ref = " << lval_ref << std::endl;
}

void MoveSemanticsDemo::Foo(int&& rval_ref)
{
    std::cout << "MoveSemanticsDemo::Foo(): rval_ref = " << rval_ref << std::endl;
}

MyBuffer<char> MoveSemanticsDemo::CreateBuffer()
{
    return MyBuffer<char>(100);
}

MyBuffer2<char> MoveSemanticsDemo::CreateBuffer2()
{
    return MyBuffer2<char>(100);
}

void MoveSemanticsDemo::UseBuffer(MyBuffer<char> buffer)
{
    std::cout << "MoveSemanticsDemo::UseBuffer()" << std::endl;
    buffer.Append('a');
}

void MoveSemanticsDemo::UseBuffer2(MyBuffer2<char> buffer)
{
    std::cout << "MoveSemanticsDemo::UseBuffer2()" << std::endl;

    std::cout << "buffer size = " << buffer.GetSize() << std::endl;
    buffer.Append('a');

    std::cout << "MoveSemanticsDemo::~UseBuffer2()" << std::endl;
}

void MoveSemanticsDemo::UseBuffer(const MyBuffer<char>& buffer)
{

}

void vModifyBuffer(MyBuffer<char>& buffer)
{

}
