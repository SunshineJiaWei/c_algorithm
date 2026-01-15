#include <stdio.h>

/**
 * leetcode.206-反转链表
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* cur = head;
    struct ListNode* pre = NULL;
    struct ListNode* temp = NULL;
    
    while (cur)
    {
        temp = cur->next;
        cur->next = pre;

        pre = cur;
        cur = temp;
    }
    return pre;
}
