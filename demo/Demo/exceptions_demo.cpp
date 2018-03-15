#include "include/exceptions_demo.h"
#include <stdexcept>
#include <iostream>


namespace {

class B
{
public: 
    B() : pChar_(nullptr){
        std::cout << "B::B()" << std::endl;
        pChar_ = new char[100];
    }

    ~B() {
        std::cout << "B::~B()" << std::endl;
        if (pChar_) {
            delete[] pChar_;
            pChar_ = nullptr;
        }
    }

private:
    char* pChar_;
};

class A
{
public: 
    A() {
        std::cout << "A::A()" << std::endl;
        std::cout << "A::A() is about to throw an exception..." << std::endl;
        throw 1;
    }

    ~A() {
        std::cout << "A::~A()" << std::endl;
    }
private:
    B b_;
};

void FunctionThatThrowsException() {
    throw std::exception("Exception from FunctionThatThrowsException.");
}

void ExceptionHandler(std::string& log) {
    try {
        throw;
    }catch(const std::exception& ex) {
        log = log + ex.what();
        std::cout << "Exception caught: " <<  ex.what() << std::endl;
    }
}

}

void ExceptionsDemo::Demo()
{
    // Call_Noexcept_Function_Which_Throws_Exception();
    // Call_Noexcept_Function_Which_Calls_Function_Which_Throws_Exception();
    // MemberObjectsAreDestroyedIfConstructorThrows();
    ExceptionHandlerFunctionDemo();
}

// try-catch is put here only for testing purposes; in production code would respect function's "noexcept" declaration
void ExceptionsDemo::Call_Noexcept_Function_Which_Throws_Exception()
{
    try
    {
        Noexcept_Function_Which_Throws_Exception();
    }
    catch(const std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }
}

// try-catch is put here only for testing purposes; in production code would respect function's "noexcept" declaration
void ExceptionsDemo::Call_Noexcept_Function_Which_Calls_Function_Which_Throws_Exception()
{
    try
    {
        Noexcept_Function_Which_Calls_Function_Which_Throws_Exception();
    }
    catch(const std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }
}

void ExceptionsDemo::Function_Which_Throws_Exception()
{
    std::cout << "ExceptionsDemo::FunctionWhichThrowsException()" << std::endl;
    throw std::runtime_error("Exception which is thrown from ExceptionsDemo::FunctionWhichThrowsException()");
}

// Exception specifier has to be present both in method declaration and definition.
// E.g. If 'noexcept' is omitted: 
// error: declaration of ‘void ExceptionsDemo::FunctionWhichThrowsException()’ has a different exception specifier
//
// If run, program is terminated once 'noexcept' method throws exception
// Program received signal SIGABRT, Aborted.
// 0x00007ffff74ab428 in __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:54
void ExceptionsDemo::Noexcept_Function_Which_Throws_Exception() noexcept
{
    std::cout << "ExceptionsDemo::NoexceptFunctionWhichThrowsException()" << std::endl;
    throw std::runtime_error("Exception which was not meant to be thrown from ExceptionsDemo::NoexceptFunctionWhichThrowsException()");
}

// If run, program is terminated once 'noexcept' method throws exception
// Program received signal SIGABRT, Aborted.
// 0x00007ffff74ab428 in __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:54
void ExceptionsDemo::Noexcept_Function_Which_Calls_Function_Which_Throws_Exception() noexcept
{
    std::cout << "ExceptionsDemo::NoexceptFunctionWhichCallsFunctionWhichThrowsException()" << std::endl;
    Function_Which_Throws_Exception();
}

// Just before body of A's c-tor is executed, B object is created.
// If A throws an exception, B's destructor will be called (but not A's as A object was never created).
// This is one of the RAII.
// If A() has to allocate some memory, it is best to use some smart pointer as A's member as in this case if
// A() throws, that smart pointer will be destroyed (just as B in the example above) and memory will be deallocated.
// If A() itself allocates memory and then throws, there will be a memory leak as ~A() is never called.
void ExceptionsDemo::MemberObjectsAreDestroyedIfConstructorThrows()
{
    try
    {
        A();
    }
    catch(...)
    {
    }
}

void ExceptionsDemo::ExceptionHandlerFunctionDemo() {
    std::string log;
    try {
        FunctionThatThrowsException();
    }catch(...) {
        ExceptionHandler(log);
    }

    std::cout << "Log: " << log.c_str() << std::endl;
}