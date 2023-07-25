// Problem 14 - Longest Common Prefix
// https://leetcode.com/problems/longest-common-prefix/

#include <string.h>
#include <stddef.h>

char * longestCommonPrefix(char ** strs, int strsSize){
    char *restrict pref = strs[0];
    size_t pref_len = strlen(pref);
    
    for (size_t i = 1; i < strsSize; i++)
    {
        char *restrict my_str = strs[i];
        size_t j;
        for (j = 0; (pref[j] == my_str[j]) && (j < pref_len); j++)
        {
            /* continue */
        }
        pref_len = j;
    }
    
    pref[pref_len] = '\0';
    return pref;
}