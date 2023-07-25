// Problem 852 - Peak Index in a Mountain Array
// https://leetcode.com/problems/peak-index-in-a-mountain-array/

#include <stdlib.h>
#include <stdbool.h>

int peakIndexInMountainArray(int* arr, int arrSize){
    int l = 0;              // left index
    int r = arrSize - 1;    // right index
    int m = r / 2;          // middle index

    while ( !(arr[m] > arr[m-1] && arr[m] > arr[m+1]) )
    {
        if (arr[m] > arr[m-1] && arr[m] < arr[m+1])
        {
            // Ascending slope (cut the left half)
            l = m;
        }
        else
        {
            // Descending slope (cut the right half)
            r = m;
        }

        // Middle point
        m = (l + r) / 2;
    }
    
    return m;
}

int main()
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9,8,7,6,5};
    peakIndexInMountainArray(arr, 14);
    return 0;
}