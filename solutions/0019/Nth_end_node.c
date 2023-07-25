// Problem 19 - Remove Nth Node From End of List
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stddef.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode *node = head;
    struct ListNode *cache[31] = {0};
    int i = 0;
    
    while (node)
    {
        cache[i++] =  node;
        node = node->next;
    }

    int target = i - n;

    if (target != 0)
    {
        cache[target-1]->next = cache[target+1];
        return head;
    }
    else
    {
        return head->next;
    }
}