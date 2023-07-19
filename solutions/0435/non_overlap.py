# Problem 435 - Non-overlapping Intervals
# https://leetcode.com/problems/non-overlapping-intervals/

from typing import List

class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        intervals.sort(key = lambda x: x[1])
        removed = set()
        for i, line1 in enumerate(intervals, start=1):
            if id((line1)) in removed: continue
            for line2 in intervals[i:]:
                if id(line2) in removed: continue
                if (line2[0] < line1[1]):
                    removed.add(id(line2))
                else:
                    break
        return len(removed)