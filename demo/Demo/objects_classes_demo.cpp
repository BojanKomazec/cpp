#include "include/objects_classes_demo.h"
#include <cstring>
#include <iostream>
#include <cassert>
#include <vector>

class MyString {
public:
    // Default c-tor
    MyString() : size_(0){
        assert(buffer_ != nullptr);
    }

    // Converting c-tor
    MyString(const char* string) {
        std::cout << "MyString c-tor" << std::endl;
        //assert(buffer_ != nullptr);

        auto len = strlen(string);
        buffer_ = new char[len + 1];
        strncpy(buffer_, string, len);
        buffer_[len] = '\0';
        size_ = len;
    }

    // Copy c-tor
    // Purpose:copied pointer members point not to the original but to copied content.
    MyString(const MyString& myString)
    {
        std::cout << "MyString COPY c-tor" << std::endl;
        auto len = myString.Length();
        buffer_ = new char[len + 1];
        strncpy(buffer_, myString.GetString(), len);
        buffer_[len] = '\0';
        size_ = len;
    }

    // Move c-tor
    // Copy c-tor creates copy of the data so new object can point to it while other object still 
    // contains and ponts to original data. Move c-tor makes new object to take ownership over the 
    // original data. It just rewires pointers: new object starts pointing to the same data and
    // old object gets completely unlinked from data. Data is not copied, ownership over it is moved.
    MyString(MyString&& myString)
    {
        std::cout << "MyString MOVE c-tor" << std::endl;
        buffer_ = myString.buffer_;
        size_ = myString.Length();

        myString.buffer_ = nullptr;
        myString.size_ = 0;
    }

    // http://stackoverflow.com/questions/11279715/nullptr-and-checking-if-a-pointer-points-to-a-valid-object
    // 1. checking whether buffer_ is nullptr is not necessary as it is safe to delete nullptr
    // 2. setting deleted pointer to nullptr is an anti-pattern
    ~MyString() {
        delete[] buffer_;
        size_ = 0;
    }

    // assignment operator can have argument of any type (not just const MyString&):
    MyString& operator=(const char* s)
    {
        if (s == nullptr)
            throw std::invalid_argument("nullptr argument");

        if (buffer_ != nullptr)
            delete[] buffer_;

        auto len = strlen(s);
        buffer_ = new char[len + 1];
        strncpy(buffer_, s, len);
        buffer_[len] = '\0';
        size_ = len;

        return *this;        
    }

    // https://stackoverflow.com/questions/45959751/which-exception-to-throw-when-current-state-of-the-object-does-not-allow-attempt
    char operator[](size_t index)
    {
        if (size_ == 0)
            throw std::out_of_range("Collection is empty");

        if (index >= size_)
            throw std::out_of_range("Index is out of range");

        return buffer_[index];
    }

    const char* GetString() const {
        return buffer_;
    }

    size_t Length() const { return size_; }

private:
    char* buffer_;
    size_t size_; // number of characters in the buffer
};

class CWidget
{
public:
	CWidget() {}

	CWidget(const CWidget& rhs) {
      std::cout << "CWidget Copy c-tor" << std::endl;
    }
    
	CWidget(CWidget&& rhs) noexcept(true) {
      std::cout << "CWidget Move c-tor" << std::endl;
   }
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
    MyStringMoveCtorDemo3();
    LValueReferenceDemo();
    RValueReferenceDemo();
    StdMoveDemo();
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

MyString ObjectsClassesDemo::CopyMyString(const MyString& str) {
    std::cout << "ObjectsClassesDemo::CopyMyString()" << std::endl;
    return MyString(str.GetString());
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
    // s2 d-tor deletes buffer_ so s1 can't dereference it anymore =>
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

void ObjectsClassesDemo::MyStringMoveCtorDemo3() {
    std::cout << "ObjectsClassesDemo::MyStringMoveCtorDemo3()" << std::endl;
    MyString s1("test1");
    MyString s2(CopyMyString(s1));
    std::cout << "s2 = " << s2.GetString() << std::endl;
}

void ObjectsClassesDemo::LValueReferenceDemo()
{
    std::cout << "ObjectsClassesDemo::LValueReferenceDemo()" << std::endl;

    // direct initialization
    MyString s1("test1");
    std::cout << "s1 = " << s1.GetString() << std::endl;
    
    // non-const lvalue reference
    MyString& s2 = s1;
    std::cout << "s2 = " << s1.GetString() << std::endl;

    const MyString s3("test3");

    // error: binding ‘const MyString’ to reference of type ‘MyString&’ discards qualifiers
    // MyString& s4 = s3;

    // const lvalue reference
    const MyString& s4 = s3;

    // error: invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’
    // int& rInt = 5; 
}

void ObjectsClassesDemo::RValueReferenceDemo()
{
    std::cout << "ObjectsClassesDemo::RValueReferenceDemo()" << std::endl;

    // direct initialization
    MyString s1("test1");

    // error: cannot bind ‘MyString’ lvalue to ‘MyString&&’
    // This is because s1 is a variable so it is lvalue.
    // MyString&& s2 = s1; 

    // non-const rvalue reference
    MyString&& s3 = ReturnMyString();
    std::cout << "s3 = " << s3.GetString() << std::endl;

    // change temporary object via rvalue reference
    // error C2106: '=': left operand must be l-value
    // s3[0] = 'b';
    // It is possible to change temp object via rvalue reference!
    s3 = "best1";
    std::cout << "s3 = " << s3.GetString() << std::endl;

    // const rvalue reference
    const int& n1 = 5;
}

// Try this with CWidget move c-tor throwing/ not throwing exception; 
// If move c-tor can throw exception compiler choses copy c-tor.
void ObjectsClassesDemo::StdMoveDemo()
{
    std::cout << "ObjectsClassesDemo::StdMoveDemo()" << std::endl;

    std::cout << "push_back(widget): " << std::endl;

	std::vector<CWidget> vec1;

	for(int n = 0; n < 5; n++)
	{
		CWidget widget;
		vec1.push_back(widget); // move so we can see copy's easier
	}

    std::cout << "push_back(std::move(widget)): " << std::endl;

	std::vector<CWidget> vec2;

	for(int n = 0; n < 5; n++)
	{
		CWidget widget;
        vec2.push_back(std::move(widget));
	}
}