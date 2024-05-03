// Problem 165 - Compare Version Numbers
// https://leetcode.com/problems/compare-version-numbers/

#include <stdlib.h>

int compareVersion(char* version1, char* version2)
{
    // Pointers to the next character after the conversion to numeric
    char* v1_end = version1;
    char* v2_end = version2;

    // Keep parsing the two version strings until we get to the end of both
    while (*v1_end || *v2_end)
    {
        // Convert the string to numeric until a dot is found
        unsigned long v1 = strtoul(version1, &v1_end, 10);
        unsigned long v2 = strtoul(version2, &v2_end, 10);

        // If the versions differ, return now
        if (v1 < v2)
        {
            return -1;
        }
        else if (v1 > v2)
        {
            return 1;
        }
        
        // Set the strint pointers to the first character after the dot
        // (but if we are at the end of the string, then we remain there)
        version1 = (*v1_end != '\0') ? (v1_end + 1) : v1_end;
        version2 = (*v2_end != '\0') ? (v2_end + 1) : v2_end;
    }

    // The versions do not differ
    return 0;
}
