/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *node1 = l1;
    struct ListNode *node2 = l2;
    int carry = 0;
    
    struct ListNode *out_list = calloc(1, sizeof(struct ListNode));
    struct ListNode *out_node = out_list;
    
    while (node1 || node2 || carry){
        const val1 = node1 ? node1->val : 0;
        const val2 = node2 ? node2->val : 0;
        const int res = carry + val1 + val2;
        out_node->val = res % 10;
        carry = res / 10;
        
        if (node1) node1 = node1->next;
        if (node2) node2 = node2->next;
        if (node1 || node2 || carry){
            out_node->next = calloc(1, sizeof(struct ListNode));
            out_node = out_node->next;
        }
    }
    
    return out_list;
}