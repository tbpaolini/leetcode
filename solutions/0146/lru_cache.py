# Problem 146 - LRU Cache
# https://leetcode.com/problems/lru-cache/

from collections import OrderedDict

class LRUCache:

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.table = OrderedDict()

    def get(self, key: int) -> int:
        try:
            self.table.move_to_end(key)
            return self.table[key]
        except KeyError:
            return -1

    def put(self, key: int, value: int) -> None:
        if key in self.table:
            self.table.move_to_end(key)
        elif (len(self.table) == self.capacity):
            self.table.popitem(last=False)
        self.table[key] = value


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)