#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node
{
    int val;
    struct Node *next;
} ListNode;

ListNode* detectCycle(ListNode *head)
{
    ListNode *fast, *slow;

    fast = head;
    slow = head;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            // 有环
            ListNode *index1 = head; // 起始点
            ListNode *index2 = slow; // 相遇点

            while (index1 != index2)
            {
                index1 = index1->next;
                index2 = index2->next;
            }

            return index1;
        }
    }

    return NULL;
}

int main() {
    // 创建测试节点
    ListNode *node1 = (ListNode*)malloc(sizeof(ListNode));
    ListNode *node2 = (ListNode*)malloc(sizeof(ListNode));
    ListNode *node3 = (ListNode*)malloc(sizeof(ListNode));
    ListNode *node4 = (ListNode*)malloc(sizeof(ListNode));

    // 构建链表: 1 -> 2 -> 3 -> 4
    //              ^         |
    //              |_________|
    // 环入口是节点 2 (值为20)
    
    node1->val = 10; node1->next = node2;
    node2->val = 20; node2->next = node3;
    node3->val = 30; node3->next = node4;
    node4->val = 40; node4->next = node2; // 4 指向 2，形成环

    ListNode *cycleNode = detectCycle(node1);

    if (cycleNode != NULL) {
        printf("Detected cycle at node val: %d\n", cycleNode->val);
    } else {
        printf("No cycle detected.\n");
    }

    // 实际使用中记得处理释放内存逻辑（带环链表释放需要小心死循环）
    return 0;
}