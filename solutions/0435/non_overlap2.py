# Problem 435 - Non-overlapping Intervals
# https://leetcode.com/problems/non-overlapping-intervals/

# This solution is based on the more efficient official solution.
# The non_overlap.py file has the solution that I came up before looking at the official.

from typing import List

class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[1])
        out = 0
        end = -50000

        for s,e in intervals:
            if s < end:
                out += 1
            else:
                end = e
        
        return out