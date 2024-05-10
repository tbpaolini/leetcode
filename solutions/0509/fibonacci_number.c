// Problem 509 - Fibonacci Number
// https://leetcode.com/problems/fibonacci-number/

// Memoization table of already calculated values
// (`-1` means that it was not calculated yet)
static int fib_table[31] = {
    [0] = 0,
    [1] = 1,
    [2 ... 30] = -1,
};

int fib(int n){
    if (n < 0 || n > 30) __builtin_unreachable();   // It is guaranteed that `0 <= n <= 30`
    
    if (fib_table[n] >= 0)
    {
        // Return the value if it is on the table
        return fib_table[n];
    }
    else
    {
        // Calculate the value and insert it on the table
        fib_table[n] = fib(n-1) + fib(n-2);
        return fib_table[n];
    }
}
