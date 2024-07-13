// Problem 528 - Random Pick with Weight
// https://leetcode.com/problems/random-pick-with-weight/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/random.h>

typedef struct {
    uint64_t prng_state;    // Last generated pseudorandom number
    size_t length;          // Amount of elements in the array of weights 
    uint64_t weights[];     // Cumulative weights (sum of all weights up to an index)
} Solution;


// Generate a pseudorandom number in-place, using the xorshift64 algorithm
// https://en.wikipedia.org/wiki/Xorshift
static inline void xorshift64(uint64_t* n)
{
	*n ^= *n << 7;
	*n ^= *n >> 9;
}


Solution* solutionCreate(int* w, int wSize)
{
    Solution* obj = malloc(sizeof(Solution) + ((size_t)wSize * sizeof(obj->weights[0])));
    
    // Seed the pseudorandom number generator (PRNG)
    if ( getentropy(&obj->prng_state, sizeof(obj->prng_state)) != 0 )
    {
        perror("getentropy");
        exit(EXIT_FAILURE);
    }
    
    // Amount of elements
    obj->length = wSize;

    // Calculate and store the cumulative weights
    int total = 0;
    for (int i = 0; i < wSize; i++)
    {
        total += w[i];
        obj->weights[i] = total;
    }

    return obj;
}

int solutionPickIndex(Solution* obj)
{
    int64_t max_index = obj->length - 1;;
    
    // Generate a random number up to the total weight
    xorshift64(&obj->prng_state);
    const uint64_t target = obj->prng_state % obj->weights[max_index];

    // Find the position of the generated number on the array of weights
    // (Using binary search)
    int64_t left = 0;           // Lower index of the array's slice
    int64_t right = max_index;  // Upper index of the array's slice
    int64_t mid = -1;           // Middle index of the array's slice
    while (left <= right)
    {
        mid = (left + right) / 2;   // Slice the array in two halves
        
        // Range of weights that is being checked
        // Note: the lower point is considered to be zero if the upper point is at the beginning of the array
        const uint64_t upper = obj->weights[mid];    // Element at the middle point
        const uint64_t lower = (mid == 0) ? 0 : obj->weights[mid-1];  // Next element to the left of the middle point

        if (target >= lower && target < upper)
        {
            // Target value is within the range of the current element
            break;
        }
        else if (target >= upper)
        {
            // Target value is in the upper slice of the array
            left = mid + 1;
        }
        else // if (target < curr)
        {
            // Target value is in the lower slice of the array
            right = mid - 1;
        }
    }

    return mid; // Index of the chosen element
}

void solutionFree(Solution* obj)
{
    free(obj);
}

/**
 * Your Solution struct will be instantiated and called as such:
 * Solution* obj = solutionCreate(w, wSize);
 * int param_1 = solutionPickIndex(obj);
 
 * solutionFree(obj);
*/
