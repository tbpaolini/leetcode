// Problem 1137 - N-th Tribonacci Number
// https://leetcode.com/problems/n-th-tribonacci-number/

// Memoization table of already calculated values
// (`-1` means that it was not calculated yet)
static int trib_table[38] = {
    [0] = 0,
    [1] = 1,
    [2] = 1,
    [3 ... 37] = -1,
};

int tribonacci(int n){
    if (n < 0 || n > 37) __builtin_unreachable();   // It is guaranteed that `0 <= n <= 37`
    
    if (trib_table[n] >= 0)
    {
        // Return the value if it is on the table
        return trib_table[n];
    }
    else
    {
        // Calculate the value and insert it on the table
        trib_table[n] = tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3);
        return trib_table[n];
    }
}
