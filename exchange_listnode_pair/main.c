
/**
 * 题目：24. 两两交换链表中的节点
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
// 思路：定义一个dummyhead头节点，这个头节点始终指向两两交换节点的前一个节点
// 然后注意需要保存阶段，在修改指针指向的过程中，谁指针丢失了就保存谁。


struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode* dummyHead = malloc(sizeof(struct ListNode));
    dummyHead->next = head;

    struct ListNode* cur = dummyHead;

    while (cur->next && cur->next->next)
    {
        struct ListNode* temp1 = cur->next;
        struct ListNode* temp2 = cur->next->next->next;

        cur->next = cur->next->next; // 步骤1
        cur->next->next = temp1;     // 步骤2
        temp1->next = temp2;         // 步骤3
        cur = temp1;                 // 移动到需要两两交换节点的前一个结点
    }

    return dummyHead->next;
}