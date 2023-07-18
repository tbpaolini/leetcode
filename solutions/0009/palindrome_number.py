# Problem 9 - Palindrome Number
# https://leetcode.com/problems/palindrome-number/

from math import log10, ceil

class Solution:
    def isPalindrome(self, x: int) -> bool:
        if (x < 0): return False
        digits = ceil(log10(x+1))   # Amount of digits
        mask = 10**(digits-1)
        
        for _ in range(digits // 2):
            high = x // mask    # Most significant digit
            low = x % 10        # Least significant digit
            if high != low: return False
            x -= mask * high
            x //= 10
            mask //= 100
        
        return True