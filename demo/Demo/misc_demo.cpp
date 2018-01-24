// Write a function which takes vector of strings and returns iterator which points to the first element 
// which is null, or end() if such element does not exist.

#include "include/misc_demo.h"
#include <vector>
#include <string>
#include <cassert>

using std::vector;
using std::string;

namespace 
{
    // Given a vector of int*, return an iterator to the first null pointer
    // or the end iterator if none is found
    vector<int*>::const_iterator FindNull1(const vector<int*>& vec)
    {
        vector<int*>::const_iterator it;
        for(it = vec.begin(); it != vec.end(); ++it)
            if (*it == nullptr)
                break;

        return it;
    }

    void FindNull1_Test()
    {
        int a = 1, b = 2, c = 3, d = 4, e = 5;
        vector<int*> v = { &a, &b, &c, nullptr, &e };
        auto it = FindNull1(v);
        assert(*it == nullptr);
    }

    // Given a container of pointers, return an iterator to the first null 
    // pointer or the end iterator if none is found
    template<typename Container>
    typename Container::const_iterator FindNull2(const Container& vec)
    {
        typename Container::const_iterator it;
        for(it = vec.begin(); it != vec.end(); ++it)
            if (*it == nullptr)
                break;

        return it;
    }  

    void FindNull2_Test()
    {
        int a = 1, b = 2, c = 3, d = 4, e = 5;
        vector<int*> v = { &a, &b, &c, nullptr, &e };
        auto it = FindNull2<vector<int*>>(v);
        assert(*it == nullptr);
    }
    
    const char* FunctionWhichReturnsPointerToChar()
    {
        std::string s("test");
        return s.c_str();
    }

    std::string FunctionWhichReturnsString()
    {
        return std::string("test");
    }

    void TestObjectScope()
    {
        std::string s1(FunctionWhichReturnsPointerToChar());
        // This assertion fails:
        // assert(s == "test");
        std::string s2(FunctionWhichReturnsString());
        assert(s2 == "test");

        // std::string& s3 = FunctionWhichReturnsString();
        // assert(s3 == "test");
        // s3[0] = 'b';
        // assert(s3 == "best");

        std::string&& s4 = FunctionWhichReturnsString();
        assert(s4 == "test");
        s4[0] = 'b';
        assert(s4 == "best");
        
        std::string&& s5 = std::move(FunctionWhichReturnsString());
        // This assertion fails.
        // assert(s5 == "test");

        // error C2440: 'initializing': cannot convert from 'int' to 'int &'
        // int& int_ref = 3 + 4;

        const int& int_ref1 = 3 + 4;

        int&& int_ref2 = 3 + 4;
        int_ref2 = 8;

        const int&& int_ref3 = 3 + 4;
        // error C3892: 'int_ref3': you cannot assign to a variable that is const
        // int_ref3 = 8;

    }
}

void MiscDemo::Demo()
{
    //FindNull1_Test();
    //FindNull2_Test();
    //TestObjectScope();
}