// Problem 9 - Palindrome Number
// https://leetcode.com/problems/palindrome-number/

#include <stdbool.h>
#include <math.h>

bool isPalindrome(int x){
    if (x < 0 || x == __INT32_MAX__) return false;
    double digits = ceil(log10(x+1));   // Amount of digits
    int mask = pow(10.0, digits-1.0);
    int steps = (int)digits >> 1;

    for (int i = 0; i < steps; i++)
    {
        int high = x / mask;    // Most significant digit
        int low = x % 10;       // Least significant digit
        if (high != low) return false;
        x -= mask * high;
        x /= 10;
        mask /= 100;
    }
    
    return true;
}