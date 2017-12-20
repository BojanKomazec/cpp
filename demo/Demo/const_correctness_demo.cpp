#include "include/const_correctness_demo.h"

namespace {

class C {
    int* const p_int_;
public:
    C(int* p_int) : p_int_(p_int) {}

    // error C2166: l-value specifies const object
    // C(int* p_int) : p_int_(p_int) { p_int_ = new int(2); }

    // error C2789: an object of const-qualified type must be initialized
    // C(int* p_int) { p_int_ = p_int; }
};

}

void ConstCorrectnessDemo::Demo() {
    int* p_int = new int(1);
    C c(p_int);
    delete p_int;
}