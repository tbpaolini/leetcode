int firstMissingPositive(int* nums, int numsSize)
{
    /*  The solution space is represented by this array:
        {1, 2, 3, ..., numsSize - 1, numsSize}
        
        The nums[] array is going to be reordered so all the elements in the
        solution space get into their correct position.
        
        After that, the solution is the smallest element from the solution space
        that is missing on nums[].
    */
    
    for (int i = 0; i < numsSize; i++)
    {
        // While the current element falls in the range [1..numsSize],
        // swap it with the element on the correct position.
        while (
            (nums[i] >= 1 && nums[i] <= numsSize)
            && (nums[nums[i]-1] != nums[i])
        )
        {
            const int temp = nums[i];
            nums[i] = nums[temp-1];
            nums[temp-1] = temp;
        }
    }
    
    // Search the array for the first missing element from the solution space
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != i+1)
        {
            return i+1;
        }
    }

    // If no element is missing, return the next positive integer
    return numsSize + 1;
}
