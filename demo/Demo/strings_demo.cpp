#include "include/strings_demo.h"
#include <iostream>

void StringsDemo::Demo()
{
    StringInversionDemo();
}

void StringsDemo::StringInversionDemo()
{
    std::string s = "abcdef";
    std::string res = Inverse(s);
    std::cout << "res = " << res << std::endl;
}

// inverse a string
std::string StringsDemo::Inverse(const std::string& s)
{
    std::string res;
    for(std::size_t i = 0, length = s.size(); i < length; i++)
    {
        res[i] = s[length - 1 - i];
        std::cout << "i = " << i << "; s[length - 1 - i] = " << s[length - 1 - i] << "; res[i] = " << res[i] << std::endl;
    }
    return res;
}