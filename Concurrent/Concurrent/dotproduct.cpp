// dotproduct.cpp
// Compile with:
// g++ -std=c++11 -pthread dotproduct.cpp -o dotproduct
#include "dotproduct.h"

void dotproduct(bool atomic)
{
    int nr_elements = 10000000;

    // Fill two vectors with some values 
    Vector v1(nr_elements,1), v2(nr_elements,2);

    // Create Functor object
    DotProduct dp(v1, v2, atomic);

    // Print the result
    std::cout << dp() << std::endl;
}

