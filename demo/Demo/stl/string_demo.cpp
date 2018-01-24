#include "../include/stl/string_demo.h"
#include <iostream>
#include <string>
#include <cassert>

void StringDemo::Demo()
{
    // AssignAppendDemo();
    SubStringDemo();
}

void StringDemo::AssignAppendDemo()
{
    std::string str;
    str.assign("This is");
    str.append(": ");
    str.append("cat");
    assert(str == "This is: cat");
    str.append("dog");
    //assert(str == "This is: dog");
}

void StringDemo::SubStringDemo() {
    std::string s = { "Hey, you!" };

    // rfind returns the position of the first character of the last match.
    auto pos = s.rfind(',');
    assert(pos == 3);

    // The substring is the portion of the object that starts at character 
    // position pos and spans len characters (or until the end of the string, whichever comes first).
    auto s2 = s.substr(pos);
    assert(s2 == ", you!");

    ++pos;
    auto s3 = s.substr(pos);
    assert(s3 == " you!");

    auto pos_space = s3.find_first_not_of(' ');
    auto s4 = s3.substr(pos_space);
    assert(s4 == "you!");
}