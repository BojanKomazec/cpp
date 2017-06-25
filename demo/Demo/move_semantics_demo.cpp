#include "include/move_semantics_demo.h"
#include <cstddef>
#include <iostream>


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
        for (size_t i = 0; i < size_; i++) {
            *(p_ + i) = *(other.p_ + i);
        }
    }

    ~MyBuffer() noexcept {
        std::cout << "MyBuffer::~MyBuffer()" << std::endl;
        if (p_) {
            delete[] p_;
            p_ = nullptr;
        }
    }

    void Append(const T& t) {

    }
private:
    std::size_t size_;
    T* p_;
};

void MoveSemanticsDemo::Demo()
{
    // MyBuffer<char> myBuffer(100); // c-tor is called
    // MyBuffer<char> myBuff2(myBuffer); // copy c-tor is called

    // MyBuffer<char> myBuffer(100); // c-tor is called
    // MyBuffer<char> myBuff2 = myBuffer; // copy c-tor is called

    MyBuffer<char> myBuff2 = MyBuffer<char>(100);

    // const MyBuffer<char>& myBuff = MyBuffer<char>(100); // c-tor is called
    // MyBuffer<char> myBuff2(myBuff); // copy c-tor is called

    //MyBuffer<char> myBuff2(MyBuffer<char>(100)); // single c-tor is called


    //MyBuffer<char>* myBuffer = new MyBuffer<char>(100);

    // MyBuffer<char>(); // error: no matching function for call to ‘MyBuffer<char>::MyBuffer()’
    // MyBuffer<char>(100); // OK

    // try
    // {
    //     MyBuffer<char> myBuff(MyBuffer<char>(11));
    // }
    // catch(const std::exception& exc)
    // {
    //     std::cout << "MoveSemanticsDemo::Demo() caught exception: " << exc.what()  << std::endl;
    // }
    
}