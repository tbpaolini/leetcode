// Problem 14 - Longest Common Prefix
// https://leetcode.com/problems/longest-common-prefix/

#include <string.h>
#include <stddef.h>

char * longestCommonPrefix(char ** strs, int strsSize){
    char *pref = strs[0];
    for (size_t i = 1; i < strsSize; i++)
    {
        char *restrict my_str = strs[i];
        size_t j = 0;
        while ( (pref[j] &&  my_str[j]) && (pref[j] == my_str[j]) )
        {
            j++;
        }
        pref[j] = '\0';
        if (j == 0) break;
    }
    return pref;
}