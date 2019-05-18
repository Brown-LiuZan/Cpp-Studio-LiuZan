/****
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
****/

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode vDummy{-1};
        ListNode * vpSumCur = &vDummy;
        ListNode * vpL1Cur = l1;
        ListNode * vpL2Cur = l2;
        int vSum = 0;
        while (vpL1Cur != nullptr || vpL2Cur != nullptr)
        {
            if (vpL1Cur != nullptr)
            {
                vSum += vpL1Cur->val;
                vpL1Cur = vpL1Cur->next;
            }
            if (vpL2Cur != nullptr)
            {
                vSum += vpL2Cur->val;
                vpL2Cur = vpL2Cur->next;
            }
            vpSumCur->next = new ListNode{vSum % 10};
            vpSumCur = vpSumCur->next;
            vSum /= 10;
        }
        if (vSum == 1)
        {
            vpSumCur->next = new ListNode{1};
            vpSumCur = vpSumCur->next;
        }
        return vDummy.next;
    }
};
