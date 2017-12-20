#include "include/functional_demo.h"
#include <iostream>
#include <functional>

namespace functional_demo {
    typedef void (CallbackType)(int);
    void SetAndCallCallback(CallbackType* callback) {
        CallbackType* cb = callback;
        (*cb)(123);
    }

    void SetAndCallCallback2(std::function<void(int)> callback) {
        std::function<void(int)> cb = callback;
        cb(123);
    }

    class C {
        static C* pC_;
    public:
        C() {
            C::SetInstance(this);
        }

        void MyCallback(int n){
            std::cout << n << std::endl;
        }

        static void SetInstance(C* pC) {
            C::pC_ = pC;
        }

        // static member function does not have implicit 'this' argument so it matches the callback type
        static void MyStaticCallback(int n){
            std::cout << n << std::endl;
        }

        // if callback has to use object (non-static) members, we can call it via static callback wrapper
        static void MyStaticCallback2(int n){
            C::pC_->MyCallback(n);
        }

        void SetCallback(){
            // no need for static class if binding `this` and non-static member function into a function object
            auto my_callback = std::bind(&C::MyCallback, this, std::placeholders::_1);

            // error C2664: 
            // 'void functional_demo::SetAndCallCallback(functional_demo::CallbackType (__cdecl *))': 
            // cannot convert argument 1 from 
            // 'std::_Binder<std::_Unforced,void (__cdecl functional_demo::C::* )(int),functional_demo::C *,const std::_Ph<1> &> *' to 
            // 'functional_demo::CallbackType (__cdecl *)'
            // SetAndCallCallback(my_callback);

            SetAndCallCallback2(my_callback);
        }
    };

    C* C::pC_ = nullptr;
}

using namespace functional_demo;

void FunctionalDemo::Demo() {
    BindDemo();
}

void FunctionalDemo::BindDemo() {
    C c;
    SetAndCallCallback(&C::MyStaticCallback);
    SetAndCallCallback([](int n){
        C::MyStaticCallback(n);
    });

    auto my_callback = std::bind(&C::MyCallback, &c, std::placeholders::_1);

    // error C2664: 
    // 'void functional_demo::SetAndCallCallback(functional_demo::CallbackType (__cdecl *))': 
    // cannot convert argument 1 from 
    // 'std::_Binder<std::_Unforced,void (__cdecl functional_demo::C::* )(int),functional_demo::C *,const std::_Ph<1> &> *' to 
    // 'functional_demo::CallbackType (__cdecl *)'
    // SetAndCallCallback(&my_callback);

    SetAndCallCallback(&C::MyStaticCallback2);
}