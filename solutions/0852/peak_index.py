# Problem 852 - Peak Index in a Mountain Array
# https://leetcode.com/problems/peak-index-in-a-mountain-array/

from typing import List

class Solution:
    def peakIndexInMountainArray(self, arr: List[int]) -> int:
        l = 0               # Left index
        r = len(arr) - 1    # Right index
        m = r // 2          # Middle index

        while not (arr[m] > arr[m-1] and arr[m] > arr[m+1]):
            
            if arr[m] > arr[m-1] and arr[m] < arr[m+1]:
                l = m   # Ascending slope (cut the left half)
            else:
                r = m   # Descending slope (cut the right half)
            
            m = (l + r) // 2    # Middle point
        
        return m
