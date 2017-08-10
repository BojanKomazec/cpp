#ifndef _MOVE_SEMANTICS_DEMO_H_  
#define _MOVE_SEMANTICS_DEMO_H_

template<typename T>
class MyBuffer;

template<typename T>
class MyBuffer2;

class MoveSemanticsDemo
{
public:
    void Demo();
private:
    void ConstructorDemo();
    void CopyConstructorDemo();
    void MoveConstructorDemo();
    void CopyElisionDemo();

    MyBuffer<char> CreateBuffer();
    MyBuffer2<char> CreateBuffer2();

    // The following two functions can call either copy or move c-tor. 
    // If copy c-tor is called: 
    //    functions work with the (deep) copy of the input argument and original object stays untouched.
    // If move c-tor is called:
    //    functions work with the object which performed shallow copy of the input object, becoming the sole owner of the data.
    // 
    // If class has move constructor and argument contains std::move (which casts lvalue to rvalue reference)
    // then move constructor is called.
    // std::move is typically called on arguments for which we'll not care once they are passed to the function - they can 
    // be modified (these are usually temporary objects).
    void UseBuffer(MyBuffer<char> buffer);
    void UseBuffer2(MyBuffer2<char> buffer);

    void UseBuffer(const MyBuffer<char>& buffer);
    void ModifyBuffer(MyBuffer<char>& buffer);

    void RValueReferenceDemo();

    // void Foo(int val);
    void Foo(int& val);
    void Foo(int&& val);

    void FooWithIntArg(int val);
    void FooWithLValRefArg(int& lval_ref);
    void FooWithRValRefArg(int&& rval_ref);
};

#endif // _MOVE_SEMANTICS_DEMO_H_