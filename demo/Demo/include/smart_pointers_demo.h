#ifndef _SMART_POINTERS_DEMO_H_
#define _SMART_POINTERS_DEMO_H_

class SmartPointersDemo
{
public:
    void Demo();
private:
    void SharedPtrConstructionDemo();
    void SharedPtrSwapDemo();
    void SharedPtrDestructionDemo();
    void MethodReturnsSharedPtrDemo();
    void PassingSharedPtrByValueDemo();
    void PassingSharedPtrByRefDemo();
};

#endif //_SMART_POINTERS_DEMO_H_