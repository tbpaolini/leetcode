# Problem 3 - Median of Two Sorted Arrays
# https://leetcode.com/problems/median-of-two-sorted-arrays/

# This solution actually runs faster than my other Python solution,
# in spite of this one to process all values and the other only half.

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        merged = sorted(nums1 + nums2)
        if len(merged) % 2 == 1:
            i = (len(merged) - 1) // 2
            return merged[i]
        else:
            i = (len(merged) // 2) - 1
            return (merged[i] + merged[i+1]) / 2