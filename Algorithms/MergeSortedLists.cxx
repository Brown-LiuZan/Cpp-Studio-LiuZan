#include <vector>
#include <limits>

/****
 Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

 Example:

 Input:
 [
   1->4->5,
   1->3->4,
   2->6
 ]
 Output: 1->1->2->3->4->4->5->6
 ****/

using namespace std;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
private:
    struct MPQNode
    {  
        int mListIndex;
        int mVal;
        ListNode const * mpListNode;

        MPQNode() : mListIndex{-1}, mVal{numeric_limits<int>::max()}, mpListNode{nullptr}
        {}
        
        MPQNode(int inListIndex, ListNode const * inpListNode)
            : mListIndex{inListIndex}, mVal{inpListNode->val}, mpListNode{inpListNode}
        {}
    };
    
    class MultiplexPriorityQueue
    {
    public:
        explicit MultiplexPriorityQueue(vector<ListNode*> const & inLists)
            : mBinaryHeap{inLists.size() + 1}, mpListsCursors{inLists.size()}, mHeapSize{0}
        {
            for (int i = inLists.size() - 1; i >= 0; --i)
            {
                if (inLists[i] == nullptr)
                {
                    mpListsCursors[i] = nullptr;
                }
                else
                {
                    mpListsCursors[i] = inLists[i];
                    InsertBySwim(MPQNode{i, mpListsCursors[i]});
                    mpListsCursors[i] = mpListsCursors[i]->next;
                }                                
            }
        }
        
        ListNode * PopMin()
        {
            if (mHeapSize == 0) return nullptr;
            
            ListNode * vpMinValNode = const_cast<ListNode *>(mBinaryHeap[1].mpListNode);
            if (vpMinValNode == nullptr) return vpMinValNode;
            
            int vListIndex = mBinaryHeap[1].mListIndex;            
            if (mpListsCursors[vListIndex] == nullptr)
            {
                InsertBySink(MPQNode{});
            }
            else
            {
                InsertBySink(MPQNode{vListIndex, mpListsCursors[vListIndex]});
                mpListsCursors[vListIndex] = mpListsCursors[vListIndex]->next;
            }            
            return vpMinValNode;
        }
    private:
        void InsertBySwim(MPQNode const & inNewNode)
        {
            //Used in constructor.
            int vTargetIndex = ++mHeapSize;
            int vParentIndex = vTargetIndex / 2; 
            while (vParentIndex > 0)
            {
                if (mBinaryHeap[vParentIndex].mVal > inNewNode.mVal)
                {
                    mBinaryHeap[vTargetIndex] = mBinaryHeap[vParentIndex];
                    vTargetIndex = vParentIndex;
                    vParentIndex = vTargetIndex / 2;
                }
                else
                {
                    mBinaryHeap[vTargetIndex] = inNewNode;
                    return;
                }
            }
            mBinaryHeap[vTargetIndex] = inNewNode;
        }
        
        void InsertBySink(MPQNode const & inNewNode)
        {
            //Used in PopMin(). The first item has consumed.
            int vTargetIndex = 1;
            int vLeftChildIndex = 2 * vTargetIndex;
            int vRightChildIndex = vLeftChildIndex + 1;
            while (vLeftChildIndex <= mHeapSize)
            {
                int vChosenIndex = vLeftChildIndex;
                if (vRightChildIndex <= mHeapSize)
                {
                    if (mBinaryHeap[vChosenIndex].mVal > mBinaryHeap[vRightChildIndex].mVal)
                    {
                        vChosenIndex = vRightChildIndex;                       
                    }                
                }
                
                if (inNewNode.mVal > mBinaryHeap[vChosenIndex].mVal)
                {
                    mBinaryHeap[vTargetIndex] = mBinaryHeap[vChosenIndex];
                    vTargetIndex = vChosenIndex;
                    vLeftChildIndex = 2 * vTargetIndex;
                    vRightChildIndex = vLeftChildIndex + 1;
                }
                else
                {                    
                    break;
                }
            }
            mBinaryHeap[vTargetIndex] = inNewNode;
        }
        
        vector<MPQNode> mBinaryHeap;
        vector<ListNode *> mpListsCursors;
        int mHeapSize;
    };
    
public:
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {       
        MultiplexPriorityQueue vMpq{lists};
        ListNode vDummy(-1);
        ListNode * vpMergedCur = &vDummy;
        for (ListNode * vpMin = vMpq.PopMin(); vpMin != nullptr; vpMin = vMpq.PopMin())
        {
            vpMergedCur->next = vpMin;
            vpMergedCur = vpMergedCur->next;
        }
        vpMergedCur->next = nullptr;
        return vDummy.next;
    }
};

