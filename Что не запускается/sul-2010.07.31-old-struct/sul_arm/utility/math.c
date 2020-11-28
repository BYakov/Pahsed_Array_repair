
#include "math.h"

//------------------------------------------------------------------------------
/// Returns the minimum value between two integers.
/// \param a  First integer to compare.
/// \param b  Second integer to compare.
//------------------------------------------------------------------------------
unsigned int min(unsigned int a, unsigned int b)
{ 
    if (a < b) {

        return a;
    }
    else {

        return b;
    }
}

//------------------------------------------------------------------------------
/// Returns the absolute value of an integer.
/// \param value  Integer value.
//------------------------------------------------------------------------------
// Do not call this function "abs", problem with gcc !
unsigned int absv(signed int value)
{
    if (value < 0) {

        return -value;
    }
    else {

        return value;
    }
}

//------------------------------------------------------------------------------
/// Computes and returns x power of y.
/// \param x  Value.
/// \param y  Power.
//------------------------------------------------------------------------------
unsigned int power(unsigned int x, unsigned int y)
{
    unsigned int result = 1;
    
    while (y > 0) {

        result *= x;
        y--;
    } 
    return result;
}

