# Problem 7 - Reverse Integer
# https://leetcode.com/problems/reverse-integer/

class Solution:
    def reverse(self, x: int) -> int:
        
        inp = abs(x)
        out = 0
        is_negative = (x < 0)

        while inp > 0:
            out *= 10
            out += (inp % 10)
            inp //= 10
        
        if is_negative: out = -out

        max_int32 = 2**31 - 1
        min_int32 = -2**31

        if not (min_int32 < out < max_int32):
            out = 0
        
        return out