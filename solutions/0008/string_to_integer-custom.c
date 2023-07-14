// Problem 8 - String to Integer (atoi)
// https://leetcode.com/problems/string-to-integer-atoi/

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

int myAtoi(char * s){
    
    int64_t num = 0;
    bool is_negative = false;
    char *c = s;
    
    // Skip leading spaces
    while (*c && *c == ' '){
        c++;
    }
    
    if (!(*c)) return 0;
    
    // Check the sign
    if (*c == '-'){
        is_negative = true;
        c++;
    }
    else if (*c == '+'){
        c++;
    }
    
    // Keep reading until the end or if a non-digit, up to 10 digits
    size_t digits = 0;
    bool leading_zero = true;
    while (*c && isdigit(*c) && digits <= 10){
        // Convert char to digit, and append it to the right
        num *= 10;
        num += (*c - '0');
        if (*c != '0') leading_zero = false;
        if (!leading_zero) digits++;
        c++;
    }
    
    // Apply sign
    if (is_negative){
        num = -num;
    }
    
    // Clamp to the bounds of a 32-bit signed integer
    if (num < INT32_MIN){
        num = INT32_MIN;
    }
    else if (num > INT32_MAX){
        num = INT32_MAX;
    }
    
    return num;
}