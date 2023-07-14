// Problem 4 - Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/

#include <stddef.h>
#include <stdbool.h>

// Container for an array
typedef struct MyArray {
    size_t pos;     // Current index
    size_t size;    // Amount of elements
    int *data;      // Array of integers
} MyArray;

// Get the next value from the sorted pair of arrays
int next_value(MyArray *array1, MyArray *array2){
    
    const size_t i = array1->pos;
    const size_t j = array2->pos;
    
    // Return the smallest among the current elements from both arrays
    if (array1->pos < array1->size && array2->pos < array2->size)
    {
        if (array1->data[i] <= array2->data[j])
        {
            array1->pos++;
            return array1->data[i];
        }
        else
        {
            array2->pos++;
            return array2->data[j];
        }
    }

    // If we got at the end of one array, return the current element of the other
    else if (array1->pos < array1->size)
    {
        array1->pos++;
        return array1->data[i];
    }
    
    else if (array2->pos < array2->size)
    {
        array2->pos++;
        return array2->data[j];
    }

    // Under the conditions of the problem, we are never going to get to the end of both arrays
    else
    {
        __builtin_unreachable();
        return __INT_MAX__;
    }
    
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    
    MyArray array1 = (MyArray){
        .pos = 0,
        .size = nums1Size,
        .data = nums1
    };

    MyArray array2 = (MyArray){
        .pos = 0,
        .size = nums2Size,
        .data = nums2
    };

    // Calculate the position of the median elements
    int total_size = nums1Size + nums2Size;
    bool is_even = (total_size % 2 == 0);
    size_t target = is_even ? (total_size / 2) - 1 : (total_size - 1) / 2;

    // Move until the element just before the median
    for (size_t i = 0; i < target; i++)
    {
        int dummy = next_value(&array1, &array2);
    }

    double median;
    
    // Get the median
    if (is_even)
    {
        const double val1 = next_value(&array1, &array2);
        const double val2 = next_value(&array1, &array2);
        median = (val1 + val2) / 2.0;
    }
    else
    {
        median = next_value(&array1, &array2);
    }

    return median;
}