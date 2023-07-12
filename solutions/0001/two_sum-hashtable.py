class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        values = {num: i for (i, num) in enumerate(nums)}
        for i,n in enumerate(nums):
            m = target - n
            if m in values:
                j = values[m]
                if i != j: return [i, j]
