// compile this program with: g++ main.cpp
#include <iostream>

// gcd - Greatest Common Divisor
// Implementation based on Euclid's algorithm
// n - numerator
// d - denominator
int gcd(int n, int d)
{
    if (n < d)
    {
        int temp = n;
        n = d;
        d = temp;
    }
    int q = 0; // quotient
    int r = 0; // remainder

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
    std::cout << "Enter first operand: " << std::endl;
    int op1;
    std::cin >> op1;
    std::cout << "Enter second operand: " << std::endl;
    int op2;
    std::cin >> op2;
    std::cout << "op1 = " << op1 << ", op2 = " << op2 << std::endl;
    std::cout << "Greatest common divisor is: " << gcd(op1, op2) << std::endl;
}


int main()
{
    gcd_test();
    return 0;
}

