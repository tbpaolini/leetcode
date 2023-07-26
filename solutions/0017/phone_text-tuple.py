# Problem 17 - Letter Combinations of a Phone Number
# https://leetcode.com/problems/letter-combinations-of-a-phone-number/

from itertools import product
from typing import List

letters = (None, None, 'abc', 'def', 'ghi', 'jkl', 'mno', 'pqrs', 'tuv', 'wxyz')
off = ord('0')

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if not digits: return []
        return ["".join(txt) for txt  in product(*(letters[ord(n) - off] for n in digits))]