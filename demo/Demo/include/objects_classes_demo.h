#ifndef _OBJECTS_CLASSES_DEMO_H_
#define _OBJECTS_CLASSES_DEMO_H_

class MyString;

class ObjectsClassesDemo
{
public:
    void Demo();
private:
    struct S;
    void CopyOnReturnDemo();
    S ReturnS();
    void MyStringDemo();
    MyString ReturnMyString();
    void MyStringMoveCtorDemo();
    void MyStringMoveCtorDemo2();
    void RValueReferenceDemo();
};

#endif // _OBJECTS_CLASSES_DEMO_H_
