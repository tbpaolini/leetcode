# Problem 77 - Combinations
# https://leetcode.com/problems/combinations/

# Note: Using the built-in combinations() of Python feels like cheating.
#       So I am doing a "proper" solution in the combinations.c file.

from itertools import combinations
from typing import List

class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        return list(combinations(range(1, n+1), k))