// Problem 7 - Reverse Integer
// https://leetcode.com/problems/reverse-integer/

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int reverse(int x){
    
    if (x == -2147483648) return 0;   // Edge case (max int32 is 2147483647)
    
    int64_t in = abs(x);
    int64_t out = 0;
    bool is_negative = (x < 0);

    while (in > 0)
    {
        out *= 10;
        out += (in % 10);
        in /= 10;
    }
    
    if (is_negative) out = -out;

    if (out < INT32_MIN || out > INT32_MAX)
    {
        out = 0;
    }
    
    return out;
}