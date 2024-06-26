# Problem 432 - All O`one Data Structure
# https://leetcode.com/problems/all-oone-data-structure/

from collections import Counter

INFINITY = float("inf")

class AllOne:

    def __init__(self):
        self.counter:Counter = Counter()
        self.__minCache:str = ""
        self.__maxCache:str = ""
        self.__changed:bool = False

    def inc(self, key: str) -> None:
        self.counter.update( (key,) )
        self.__changed = True

    def dec(self, key: str) -> None:
        if self.counter[key] == 1:
            # Remove the key if there is only one left
            del self.counter[key]
        else:
            # Decrease the key's count if there is ore than one left
            self.counter.subtract( (key,) )
        self.__changed = True
    
    def updateMinMax(self) -> None:
        if not self.counter:
            self.__maxCache = self.__minCache = ""
        
        else:
            # Compare by the count, then return the key
            self.__maxCache = max( self.counter.items(), key = lambda x: x[1] )[0]
            self.__minCache = min( self.counter.items(), key = lambda x: x[1] )[0]
            self.__changed = False

    def getMaxKey(self) -> str:
        if self.__changed: self.updateMinMax()
        return self.__maxCache

    def getMinKey(self) -> str:
        if self.__changed: self.updateMinMax()
        return self.__minCache


# Your AllOne object will be instantiated and called as such:
# obj = AllOne()
# obj.inc(key)
# obj.dec(key)
# param_3 = obj.getMaxKey()
# param_4 = obj.getMinKey()