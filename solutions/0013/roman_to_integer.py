# Problem 13 - Roman to Integer
# https://leetcode.com/problems/roman-to-integer/

class Solution:
    def romanToInt(self, s: str) -> int:
        roman_num = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
        prev_val = 0
        out = 0
        
        # Iterate over the reversed string
        for char in s[::-1]:
            val = roman_num[char]
            if val < prev_val:
                out -= val
            else:
                out += val
            prev_val = val
        
        return out