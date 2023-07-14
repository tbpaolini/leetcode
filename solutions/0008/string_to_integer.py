# Problem 8 - String to Integer (atoi)
# https://leetcode.com/problems/string-to-integer-atoi/

class Solution:
    def myAtoi(self, s: str) -> int:
        
        num = 0
        i = 0
        max_i = len(s) - 1
        if max_i < 0: return 0
        is_negative = False
        
        while i <= max_i and s[i] == " ":
            i += 1
        
        if i > max_i: return 0
        
        if s[i] == "-":
            is_negative = True
            i += 1
        elif s[i] == "+":
            i += 1
        
        while i <= max_i and s[i].isdecimal():
            num *= 10
            num += ord(s[i]) - ord("0")
            i += 1
        
        if is_negative: num = -num
        
        min_int32 = -2**31
        max_int32 = 2**31 - 1
        if num < min_int32: num = min_int32
        if num > max_int32: num = max_int32
        
        return num