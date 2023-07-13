from collections import Counter

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        
        start = 0
        size = len(s)
        seen = Counter()
        
        for char in s:
            seen.update(char)
            top_char = seen.most_common(1)[0][1]
            if top_char > 1:
                seen.subtract(s[start])
                start += 1
                
        return size - start
