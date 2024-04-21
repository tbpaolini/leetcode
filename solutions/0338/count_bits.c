// Problem 338 - Counting Bits
// https://leetcode.com/problems/counting-bits/

#include <stdlib.h>

int* countBits(int n, int* returnSize){
    int *ans = malloc((n+1) * sizeof(int));
    *returnSize = n+1;
    for (int i = 0; i <= n; i++){
        ans[i] = __builtin_popcount(i);
    }
    return ans;
}
