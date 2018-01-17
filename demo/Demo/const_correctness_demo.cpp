#include "include/const_correctness_demo.h"

namespace {

class C {
    int* const p_int_ = nullptr;

    // if we don't define it:
    // error LNK2001: unresolved external symbol "private: static int `anonymous namespace'::C::static_int_" (?static_int_@C@?A0x4f6f6bf0@@0HA)
    static int static_int_;
public:
    C() = default;
    C(int* p_int) : p_int_(p_int) {}

    // error C2166: l-value specifies const object
    // C(int* p_int) : p_int_(p_int) { p_int_ = new int(2); }

    // error C2789: an object of const-qualified type must be initialized
    // C(int* p_int) { p_int_ = p_int; }

    // 'const' does not affect static member variables
    void SetStaticInt(int n) const {
        C::static_int_ = n;
    }
};

int C::static_int_ = 0;

}

void ConstCorrectnessDemo::Demo() {
    ConstructorsDemo();
    StaticClassMemberDemo();
}

void ConstCorrectnessDemo::ConstructorsDemo() {
    int* p_int = new int(1);
    C c(p_int);
    delete p_int;
}

void ConstCorrectnessDemo::StaticClassMemberDemo(){
    C c;
    c.SetStaticInt(1);
}