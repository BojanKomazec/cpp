#ifndef _STRINGS_DEMO_H_
#define _STRINGS_DEMO_H_

#include <string>

class StringsDemo
{
public:
    void Demo();
    void StringInversionDemo();
private:
    // todo: inverse a sentence
    // todo: reverse in place
    std::string Inverse(const std::string& s);
};

#endif // _STRINGS_DEMO_H_