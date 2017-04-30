#include "include/objects_classes_demo.h"
#include <cstring>
#include <iostream>

class MyString {
public:
    MyString(){
        std::cout << "Before initialization: buffer = " << _buffer << std::endl;
        _buffer = nullptr;
    }

    MyString(const char* string) {
        std::cout << "MyString c-tor" << std::endl;
        auto len = strlen(string);
        _buffer = new char[len + 1];
        strncpy(_buffer, string, len);
        _buffer[len] = '\0';
    }

    // Copy constructor
    // Purpose:copied pointer members point not to the original but to copied content.
    MyString(const MyString& myString)
    {
        std::cout << "MyString COPY c-tor" << std::endl;
        auto len = strlen(myString.GetString());
        _buffer = new char[len + 1];
        strncpy(_buffer, myString.GetString(), len);
        _buffer[len] = '\0';
    }

    // Move c-tor
    // Copy c-tor creates copy of the data so new object can point to it while other object still 
    // contains and ponts to original data. Move c-tor makes new object to take ownership over the 
    // original data. It just rewires pointers: new object starts pointing to the same data and
    // old object gets completely unlinked from data. Data is not copied, ownership over it is moved.
    MyString(MyString&& myString)
    {
        std::cout << "MyString MOVE c-tor" << std::endl;
        _buffer = myString._buffer;
        myString._buffer = nullptr;
    }

    // http://stackoverflow.com/questions/11279715/nullptr-and-checking-if-a-pointer-points-to-a-valid-object
    // 1. checking whether _buffer is nullptr is not necessary as it is safe to delete nullptr
    // 2. setting deleted pointer to nullptr is an anti-pattern
    ~MyString() {
        delete _buffer;
    }

    // assignment operator can have argument of any type (not just const MyString&):
    MyString& operator=(const char* s)
    {
        if (s == nullptr)
            throw std::invalid_argument("nullptr argument");

        if (_buffer != nullptr)
            delete[] _buffer;

        auto len = strlen(s);
        _buffer = new char[len + 1];
        strncpy(_buffer, s, len);
        _buffer[len] = '\0';

        return *this;        
    }

    const char* GetString() const {
        return _buffer;
    }

private:
    char* _buffer;
};

struct ObjectsClassesDemo::S {
    // constructor
    S() {
        std::cout << "S c-tor" << std::endl;
    }

    // copy constructor
    S(const S& s) {
        std::cout << "S copy c-tor" << std::endl;
    }
};

void ObjectsClassesDemo::Demo() {
    CopyOnReturnDemo();
    MyStringDemo();
    MyStringMoveCtorDemo();
    MyStringMoveCtorDemo2();
    RValueReferenceDemo();
}

void ObjectsClassesDemo::CopyOnReturnDemo() {
    ObjectsClassesDemo::S s = ReturnS();
}

ObjectsClassesDemo::S ObjectsClassesDemo::ReturnS() {
    return ObjectsClassesDemo::S();
}

MyString ObjectsClassesDemo::ReturnMyString() {
    std::cout << "ObjectsClassesDemo::ReturnMyString()" << std::endl;
    return MyString("String from ReturnMyString");
}

void ObjectsClassesDemo::MyStringDemo() {
    std::cout << "ObjectsClassesDemo::MyStringDemo()" << std::endl;

    MyString s1("abcdef");

    {
        //MyString s2 = s1;    
        MyString s2(s1);
        std::cout << "s2 string = " << s2.GetString() << std::endl;
    }

    // If there is only implicitly generated copy-ctor
    // s2 d-tor deletes _buffer so s1 can't dereference it anymore =>
    // Error in `./demo.out': double free or corruption (fasttop)
    // This can be solved by introducing custom copy c-tor.

    std::cout << "s1 string = " << s1.GetString() << std::endl;
}

void ObjectsClassesDemo::MyStringMoveCtorDemo() {
    std::cout << "ObjectsClassesDemo::MyStringMoveCtorDemo()" << std::endl;
    //MyString s1(ReturnMyString());
    MyString s1("test1");
    MyString s2 = std::move(s1);

    auto str1 = s1.GetString();
    if (str1 != nullptr)
        std::cout << "s1 string = " << s1.GetString() << std::endl;

    std::cout << "s2 string = " << s2.GetString() << std::endl;
}

void ObjectsClassesDemo::MyStringMoveCtorDemo2() {
    std::cout << "ObjectsClassesDemo::MyStringMoveCtorDemo2()" << std::endl;
    MyString s1(ReturnMyString());
    std::cout << "s1 string = " << s1.GetString() << std::endl;
}

void ObjectsClassesDemo::RValueReferenceDemo()
{
    std::cout << "ObjectsClassesDemo::RValueReferenceDemo()" << std::endl;
    MyString s1("test1");
    std::cout << "s1 = " << s1.GetString() << std::endl;
    MyString& s2 = s1;
    std::cout << "s2 = " << s1.GetString() << std::endl;
    MyString&& s3 = ReturnMyString();
    std::cout << "s3 = " << s1.GetString() << std::endl;

    // MyString&& s4 = s1; // error: cannot bind ‘MyString’ lvalue to ‘MyString&&’
}