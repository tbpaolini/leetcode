# Problem 3 - Median of Two Sorted Arrays
# https://leetcode.com/problems/median-of-two-sorted-arrays/

def merged(nums1, nums2):
    
    max1 = len(nums1) - 1
    max2 = len(nums2) - 1
    pos1 = 0
    pos2 = 0
    
    while (pos1 <= max1 and pos2 <= max2):
        val1 = nums1[pos1]
        val2 = nums2[pos2]
        if val1 <= val2:
            pos1 += 1
            yield val1
        else:
            pos2 += 1
            yield val2
    
    for val in nums1[pos1:]:
        yield val
    
    for val in nums2[pos2:]:
        yield val

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        
        size = len(nums1) + len(nums2)
        is_even = (size % 2 == 0)
        target = (size // 2) - 1 if is_even else ((size+1) // 2) - 1
        
        sorted_vals = merged(nums1, nums2)
        for _ in range(target):
            next(sorted_vals)
        
        if is_even:
            return (next(sorted_vals) + next(sorted_vals)) / 2
        else:
            return next(sorted_vals)