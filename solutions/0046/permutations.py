# Problem 46 - Permutations
# https://leetcode.com/problems/permutations/

# Note: Using the built-in permutations() of Python feels like cheating.
#       So I am doing a "proper" solution in the permutations.c file.

from itertools import permutations
from typing import List

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        return tuple(permutations(nums))