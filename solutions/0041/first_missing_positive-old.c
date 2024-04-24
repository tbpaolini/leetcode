// Problem 41 - First Missing Positive
// https://leetcode.com/problems/first-missing-positive/description/

#include <stdlib.h>

static int compare_int(int* n1, int* n2)
{
    if (*n1 < *n2)
    {
        return -1;
    }
    else if (*n1 > *n2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int firstMissingPositive(int* nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), &compare_int);
    
    int i = 0;
    while (i < numsSize && nums[i] <= 0)
    {
        i++;
    }
    if (i == numsSize) return 1;
    
    int min_p = 1;
    int prev = nums[i];
    while (i < numsSize)
    {
        if ( (i+1 < numsSize) && (nums[i] == nums[i+1]) )
        {
            i++;
            continue;
        }
        
        if (nums[i++] != min_p)
        {
            return min_p;
        }
        else
        {
            min_p++;
        }
    }
    
    return min_p;
}
