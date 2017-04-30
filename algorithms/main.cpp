// compile this program with: g++ main.cpp
#include <iostream>
#include <assert.h>

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void swap_test()
{
    int a = 1;
    int b = 2;
    swap(a, b);
    assert(a == 2 && b == 1);
}

// gcd - Greatest Common Divisor
// Implementation based on Euclid's algorithm
// n - numerator
// d - denominator
// n - quotient
// d - remainder
int gcd(int n, int d) 
{
    if (n == 0 || d == 0)
        return 0;

    if (n < d)
        swap(n, d);

    int q, r = 0;

    while(true) {
        q = n/d;
        r = n - (d * q);
        if(r == 0)
            break;
        n = d;
        d = r;
    };  

    return d;  
}

void gcd_test()
{
    assert(gcd(0, 0) == 0);
    assert(gcd(0, 1) == 0);
    assert(gcd(1, 0) == 0);
    assert(gcd(1, 1) == 1);
    assert(gcd(2, 1) == 1);
    assert(gcd(1, 2) == 1);
    assert(gcd(24, 8) == 8);
    assert(gcd(6, 21) == 3);
    assert(gcd(34340544, 88393728) == 192); 
    assert(gcd(145578633, 82465690) == 233);
}

void gcd_demo()
{
    std::cout << "Enter first operand: " << std::endl;
    int op1;
    std::cin >> op1;
    std::cout << "Enter second operand: " << std::endl;
    int op2;
    std::cin >> op2;
    std::cout << "op1 = " << op1 << ", op2 = " << op2 << std::endl;
    std::cout << "Greatest common divisor is: " << gcd(op1, op2) << std::endl;
}

void run_unit_tests()
{
    swap_test();
    gcd_test();
}


int main()
{
    run_unit_tests();
    //gcd_demo();
    return 0;
}

