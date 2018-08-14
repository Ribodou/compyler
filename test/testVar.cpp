#include <iostream>
#include "Var.h"




bool test()
{
    Var a, b, c;
    a = 4;
    b = 5;
    a += b;
    return false;
}


int main()
{
    if (test())
    {
        std::cout << "Tests réussis.\n";
        return 0;
    }
    else
    {
        std::cout << "Tests échoués.\n";
        return -1;
    }
}
