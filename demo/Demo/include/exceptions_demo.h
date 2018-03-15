#ifndef _EXCEPTIONS_DEMO_H_
#define _EXCEPTIONS_DEMO_H_

class ExceptionsDemo
{
public:
    void Demo();
private:
    void NoExceptDemo();
    void Function_Which_Throws_Exception();
    void Noexcept_Function_Which_Throws_Exception() noexcept;
    void Noexcept_Function_Which_Calls_Function_Which_Throws_Exception() noexcept;

    void Call_Noexcept_Function_Which_Throws_Exception();
    void Call_Noexcept_Function_Which_Calls_Function_Which_Throws_Exception();

    void MemberObjectsAreDestroyedIfConstructorThrows();
    void ExceptionHandlerFunctionDemo();
};

#endif // _EXCEPTIONS_DEMO_H_