# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        
        list_head = ListNode()
        node = list_head
        carry = 0
        
        while l1 or l2 or carry:
            
            if l1 is not None:
                val1 = l1.val
                l1 = l1.next
            else:
                val1 = 0
            
            if l2 is not None:
                val2 = l2.val
                l2 = l2.next
            else:
                val2 = 0
            
            res = carry + val1 + val2
            
            node.next = ListNode()
            node = node.next
            node.val = res % 10
            carry = res // 10
        
        return list_head.next