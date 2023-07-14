// Problem 8 - String to Integer (atoi)
// https://leetcode.com/problems/string-to-integer-atoi/

// Using the builtin function kinda goes against the spirit of the problem, in my opinion.
// So there is also a custom solution on the other .c file of this folder.

#include <stdint.h>

int myAtoi(char * s){
    
    int64_t num = atol(s);
    
    // Clamp to the bounds of a 32-bit signed integer
    if (num < INT32_MIN){
        num = INT32_MIN;
    }
    else if (num > INT32_MAX){
        num = INT32_MAX;
    }
    
    return num;
}