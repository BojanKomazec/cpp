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
}

void MiscDemo::Demo()
{
    FindNull1_Test();
    FindNull2_Test();
}