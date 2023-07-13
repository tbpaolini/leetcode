# This finishes in about half of the time than the other Python solution

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        
        start = 0
        size = len(s)
        seen = bytearray(128)
        s = s.encode("ascii")
        
        for char in s:
            seen[char] += 1
            if max(seen) > 1:
                seen[s[start]] -= 1
                start += 1
                
        return size - start
