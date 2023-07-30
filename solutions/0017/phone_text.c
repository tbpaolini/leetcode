// Problem 17 - Letter Combinations of a Phone Number
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct PhoneKey {
    size_t size;
    char letters[5];
} PhoneKey;

static const PhoneKey keys[] = {
    (PhoneKey){3,"abc"},
    (PhoneKey){3,"def"},
    (PhoneKey){3,"ghi"},
    (PhoneKey){3,"jkl"},
    (PhoneKey){3,"mno"},
    (PhoneKey){4,"pqrs"},
    (PhoneKey){3,"tuv"},
    (PhoneKey){4,"wxyz"},
};

static const char offset = '2';

char ** letterCombinations(char * digits, int* returnSize){
    size_t digits_len = strlen(digits);
    if (digits_len == 0)
    {
        *returnSize = 0;
        return (char**)NULL;
    }

    // Calculate the amount of strings on the output
    size_t out_len = 1;
    for (size_t i = 0; i < digits_len; i++)
    {
        const char digit = digits[i];
        out_len *= keys[digit - offset].size;
    }
    
    // Allocate the output array of strings
    char **out = malloc(out_len * sizeof(char*));
    for (size_t i = 0; i < out_len; i++)
    {
        out[i] = calloc(1, digits_len + 1);
    }
    *returnSize = out_len;

    const PhoneKey *my_keys[digits_len];
    for (size_t i = 0; i < digits_len; i++)
    {
        my_keys[i] = &keys[digits[i] - offset];
    }

    // The indices of the current letter for each digit
    // The array uses an "odometer-like" counter: when a value goes past its maximum,
    // it rolls over back to zero and incrments by one the value to the left
    size_t indices[digits_len];
    memset(indices, 0, sizeof(indices));

    // Position on the output array
    size_t pos = 0;

    while (true)
    {
        // Append to the output the string formed by using the current indices of each key
        for (size_t i = 0; i < digits_len; i++)
        {
            out[pos][i] = my_keys[i]->letters[indices[i]];
        }
        pos++;
        if (pos >= out_len) break;  // Exit if at the end of the output array

        // Increment the last index by one, in an "odometer-like" way
        // (if a value goes past its maximum, it becomes 0, then 1 is added
        // to the next value to the left)
        size_t next = digits_len-1;
        while (indices[next] >= my_keys[next]->size - 1)
        {
            indices[next] = 0;
            if (next == 0) goto exit_function;  // Exit if we rolled over back to all zeroes
            next--;
        }
        indices[next]++;
    }
    
    exit_function:
    return out;
}
