#include "include/exceptions_demo.h"
#include <stdexcept>
#include <iostream>

void ExceptionsDemo::Demo()
{
    // Call_Noexcept_Function_Which_Throws_Exception();
    Call_Noexcept_Function_Which_Calls_Function_Which_Throws_Exception();
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