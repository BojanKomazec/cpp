// Write a function which takes vector of strings and returns iterator which points to the first element 
// which is null, or end() if such element does not exist.

#include "include/misc_demo.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

vector<int*>::const_iterator FindNull(const vector<int*>& vec)
{
    vector<int*>::const_iterator it;
    for(it = vec.begin(); it != vec.end(); ++it)
        if (*it == nullptr)
            break;

    return it;
}

void FindNull_Test()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    vector<int*> v = { &a, &b, &c, nullptr, &e };
    auto it = FindNull(v);
}



// Write a function which takes any container and returns iterator pointing to the element which contains null

//template<typename T>
//typename T::const_iterator findNull(T container) {
    //for 
//}