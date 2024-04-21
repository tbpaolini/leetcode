// Problem 383 - Ranson Note
// https://leetcode.com/problems/ransom-note/description/

#include <stdlib.h>
#include <stdbool.h>

bool canConstruct(char* ransomNote, char* magazine) {
    size_t letters[26] = {0};
    
    while ( *magazine != '\0')
    {
        size_t char_id = (*magazine++) - 'a';
        letters[char_id] += 1;
    }
    
    while ( *ransomNote != '\0' )
    {
        size_t char_id = (*ransomNote++) - 'a';
        if (letters[char_id] > 0)
        {
            letters[char_id] -= 1;
        }
        else
        {
            return false;
        }
    }
    
    return true;
}
