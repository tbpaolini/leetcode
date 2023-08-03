// Problem 46 - Permutations
// https://leetcode.com/problems/permutations/

/* This solution is almost the same as permutations.c, except that this one
   does not use recursion at all.
   This solution runs a little slower than the other, but it also uses a little
   less memory. */

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
    
    size_t idx[n];  // Loop counter for each element in the array
    memset(idx, 0, sizeof(idx));

    append_solution(output, array);

    size_t i = 1;   // Stack pointer
    while (i < n)
    {
        if (idx[i] < i)
        {
            if (i % 2 == 0)
            {
                swap(array, 0, i);
            }
            else
            {
                swap(array, idx[i], i);
            }
            append_solution(output, array);
            idx[i]++;
            i = 1;
        }
        else
        {
            idx[i++] = 0;
        }
    }
    /* To be honest, I could not understand why above the loop produces the correct result.*/
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


int main(){
    // permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
    int nums[] = {1,2,3,4};
    int numsSize = sizeof(nums) / sizeof(int);
    int returnSize = 0;
    int *returnColumnSizes = NULL;
    int **perms = permute(nums, numsSize, &returnSize, &returnColumnSizes);
    return 0;
}