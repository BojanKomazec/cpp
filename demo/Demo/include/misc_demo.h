#ifndef _MISC_DEMO_H_  
#define _MISC_DEMO_H_

#include <vector>

class MiscDemo
{
public:
    std::vector<int*>::const_iterator FindNull(const std::vector<int*>& vec);    
};

#endif // _MISC_DEMO_H_