# Problem 14 - Longest Common Prefix
# https://leetcode.com/problems/longest-common-prefix/

from typing import List

class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        pref = strs[0]
        
        for s in strs[1:]:
            n = 0
            for a,b in zip(pref, s):
                if a == b:
                    n += 1
                else:
                    break
            pref = pref[:n]
            if not pref: return ""
        
        return pref