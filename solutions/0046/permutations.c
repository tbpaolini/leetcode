// Problem 46 - Permutations
// https://leetcode.com/problems/permutations/

#include <stdlib.h>
#include <string.h>

typedef struct MySolution {
    int **arrays;   // Array of arrays with each permutation
    size_t count;   // How many arrays are currently stored
    size_t size;    // Size in bytes of each array
} MySolution;

// In-place swap of the elements i and j from an array of integers
static inline void swap(int *array, size_t i, size_t j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

// Copy one solution to the array of solutions
static inline void append_solution(MySolution *output, int *array){
    memcpy(output->arrays[output->count++], array, output->size);
}

// Produce all permutations of an array involving only the first 'n' elements,
// while appending a copy of each permutation to 'output'.
// Heap's algorithm: https://en.m.wikipedia.org/wiki/Heap%27s_algorithm
static void heap_permutate(int *array, size_t n, MySolution *output){
    
    if (n == 1)
    {
        // Base case
        // Return the array itself if it has just a single element
        append_solution(output, array);
        return;
    }
    else
    {
        // General case
        // Permutate the first n-1 elements of the array
        heap_permutate(array, n-1, output);
    }

    // Iterate over the first n-1 elements
    for (size_t i = 0; i < n-1; i++)
    {
        if (n % 2 == 0)
        {
            // Swap the last element with the i-th element if the array has an even length
            swap(array, i, n-1);
        }
        else
        {
            // Swap the last element with the first element if the array has an odd length
            swap(array, 0, n-1);
        }
        
        // Permutate the first n-1 elements of the array
        heap_permutate(array, n-1, output);
    }
}

// Allocate a 2D array of integers
static int** alloc_2Darray_int(size_t columns, size_t rows){
    int **array = calloc(columns, sizeof(int*));
    for (size_t i = 0; i < columns; i++)
    {
        array[i] = calloc(rows, sizeof(int));
    }
    return array;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    
    // Calculate the amount of ermutations
    *returnSize = 1;
    for (size_t i = 2; i <= numsSize; i++)
    {
        *returnSize *= i;
    }
    
    // Allocate the array for the permutations
    MySolution output = {
        .arrays = alloc_2Darray_int(*returnSize, numsSize),
        .count = 0,
        .size = numsSize * sizeof(int),
    };

    // Set the size of each permutation
    *returnColumnSizes = calloc(*returnSize, sizeof(int));
    for (size_t i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = numsSize;
    }
    
    // Generate all the permutations
    heap_permutate(nums, numsSize, &output);

    return output.arrays;
}
