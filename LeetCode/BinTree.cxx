/**
 * There are two kinds of binary tree traversal,
 *     depth-first traversal
 *     breath-first traversal
 * There are three kinds of depth-first traversal,
 *     root-first traversal that is root-left-right or root-right-left
 *     root-last traversal that is left-right-root or right-left-root
 *     root-in-middle traversal that is left-root-right or right-root-left
 * For depth-first traversal, there're following solutions to do it,
 *     recursive traversal: Space O(n), Time O(n)
 *     stacked iterative traversal: Space O(n), Time O(n)
 *     Morris iterative traversal: Space O(1), Time O(n)
 * For breath-first traversal, there're following solutions to do it,
 *     queued iterative traversal: Space O(n), Time O(n)
 * */

#define DYNAMIC_ASSERT_EXCEPTION
#include "Common/assert.h" //liuzan::DynamicAssert<>()
#include <iostream>
#include <string>
#include <functional> //std::function<>
#include <stack> //std::stack<>
#include <queue> //std::queue<>
#include <deque> //std::deque<>

#include <gtest/gtest.h>

template<typename DataType>
class BinaryTreeNode
{
public:
    BinaryTreeNode *mLeft;
    BinaryTreeNode *mRight;
    DataType *mData;

public:
    BinaryTreeNode()
        : mLeft(nullptr), mRight(nullptr), mData(nullptr)
    {}

    BinaryTreeNode(BinaryTreeNode * inLeft, BinaryTreeNode * inRight, DataType * inData)
        : mLeft(inLeft), mRight(inRight), mData(inData)
    {}

    ~BinaryTreeNode()
    {
        delete mData;
        if (mLeft != nullptr)
        {
            delete mLeft;
            mLeft = nullptr;
        }
        if (mRight != nullptr)
        {
            delete mRight;
            mRight = nullptr;
        }
    }
};

template<typename DataType>
void RecursivePreorderTraversal(BinaryTreeNode<DataType> * inRoot,
                                std::function<void(DataType *, void *)> const & inFuncObj,
                                void * ioFuncArg)
{
    if (inRoot == nullptr) return;

    inFuncObj(inRoot->mData, ioFuncArg);
    if (inRoot->mLeft != nullptr) RecursivePreorderTraversal(inRoot->mLeft, inFuncObj, ioFuncArg);
    if (inRoot->mRight != nullptr) RecursivePreorderTraversal(inRoot->mRight, inFuncObj, ioFuncArg);
}

template<typename DataType>
void StackedPreorderTraversal(BinaryTreeNode<DataType> * inRoot,
                              std::function<void(DataType *, void *)> const & inFuncObj,
                              void * ioFuncArg)
{
    if (nullptr == inRoot) return;

    std::stack<BinaryTreeNode<DataType> *> vAuxStack;

    inFuncObj(inRoot->mData, ioFuncArg);
    if (inRoot->mRight != nullptr) vAuxStack.push(inRoot->mRight);
    if (inRoot->mLeft != nullptr) vAuxStack.push(inRoot->mLeft);
    while (!vAuxStack.empty())
    {
        BinaryTreeNode<DataType> * vNode = vAuxStack.top();
        vAuxStack.pop();

        inFuncObj(vNode->mData, ioFuncArg);
        if (vNode->mRight != nullptr) vAuxStack.push(vNode->mRight);
        if (vNode->mLeft != nullptr) vAuxStack.push(vNode->mLeft);
    }
}

template<typename DataType>
void MorrisPreorderTraversal(BinaryTreeNode<DataType> * inRoot,
                             std::function<void(DataType *, void *)> const & inFuncObj,
                             void * ioFuncArg)
{
    BinaryTreeNode<DataType> * vCur = inRoot;

    while (vCur != nullptr)
    {
        if (nullptr == vCur->mLeft)
        {
            inFuncObj(vCur->mData, ioFuncArg);
            vCur = vCur->mRight;
        }
        else
        {
            //Find the prevous node in order.
            BinaryTreeNode<DataType> * vNode = vCur->mLeft;
            while (vNode->mRight != nullptr && vNode->mRight != vCur)
            {
                vNode = vNode->mRight;
            }

            if (nullptr == vNode->mRight)
            { //Touch the previous node in order first time. Record me as its right child for going back.
                inFuncObj(vCur->mData, ioFuncArg);
                vNode->mRight = vCur;
                vCur = vCur->mLeft;
            }
            else
            { //Touch the previous node second time during going back. Reset its right child.
                vNode->mRight = nullptr;
                vCur = vCur->mRight;
            }
        }
    }
}

template<typename DataType>
void RecursiveMidorderTraversal(BinaryTreeNode<DataType> * inRoot,
                                std::function<void(DataType *, void *)> const & inFuncObj,
                                void * ioFuncArg)
{
    if (nullptr == inRoot) return;

    if (inRoot->mLeft != nullptr) RecursiveMidorderTraversal(inRoot->mLeft, inFuncObj, ioFuncArg);
    inFuncObj(inRoot->mData, ioFuncArg);
    if (inRoot->mRight != nullptr) RecursiveMidorderTraversal(inRoot->mRight, inFuncObj, ioFuncArg);
}

template<typename DataType>
void StackedMidorderTraversal(BinaryTreeNode<DataType> * inRoot,
                              std::function<void(DataType *, void *)> const & inFuncObj,
                              void * ioFuncArg)
{
    if (nullptr == inRoot) return;

    std::stack<BinaryTreeNode<DataType> *> vAuxStack;

    if (inRoot->mRight != nullptr)
    {
        vAuxStack.push(inRoot->mRight);
    }
    if (inRoot->mLeft != nullptr)
    {
        vAuxStack.push(inRoot);
        vAuxStack.push(nullptr);
        vAuxStack.push(inRoot->mLeft);
    }
    else
    {
        inFuncObj(inRoot->mData, ioFuncArg);
    }
    while (!vAuxStack.empty())
    {
        BinaryTreeNode<DataType> * vTop = vAuxStack.top();
        vAuxStack.pop();

        if (nullptr == vTop)
        {
            vTop = vAuxStack.top();
            vAuxStack.pop();
            inFuncObj(vTop->mData, ioFuncArg);
            continue;
        }

        if (vTop->mRight != nullptr)
        {
            vAuxStack.push(vTop->mRight);
        }
        if (vTop->mLeft != nullptr)
        {
            vAuxStack.push(vTop);
            vAuxStack.push(nullptr);
            vAuxStack.push(vTop->mLeft);
        }
        else
        {
            inFuncObj(vTop->mData, ioFuncArg);
        }
    }
}

template<typename DataType>
void MorrisMidorderTraversal(BinaryTreeNode<DataType> * inRoot,
                             std::function<void(DataType *, void *)> const & inFuncObj,
                             void * ioFuncArg)
{
    BinaryTreeNode<DataType> * vCur = inRoot;

    while (vCur != nullptr)
    {
        if (nullptr == vCur->mLeft)
        {
            inFuncObj(vCur->mData, ioFuncArg);
            vCur = vCur->mRight;
        }
        else
        {
            BinaryTreeNode<DataType> * vNode = vCur->mLeft;
            while (vNode->mRight != nullptr && vNode->mRight != vCur) vNode = vNode->mRight;

            if (nullptr == vNode->mRight)
            {
                vNode->mRight = vCur;
                vCur = vCur->mLeft;
            }
            else
            {
                inFuncObj(vCur->mData, ioFuncArg);
                vNode->mRight = nullptr;
                vCur = vCur->mRight;
            }
        }
    }
}

template<typename DataType>
void RecursivePostorderTraversal(BinaryTreeNode<DataType> * inRoot,
                                 std::function<void(DataType *, void *)> const & inFuncObj,
                                 void * ioFuncArg)
{
    if (nullptr == inRoot) return;

    if (inRoot->mLeft != nullptr) RecursivePostorderTraversal(inRoot->mLeft, inFuncObj, ioFuncArg);
    if (inRoot->mRight != nullptr) RecursivePostorderTraversal(inRoot->mRight, inFuncObj, ioFuncArg);
    inFuncObj(inRoot->mData, ioFuncArg);
}

template<typename DataType>
void StackedPostorderTraversal(BinaryTreeNode<DataType> * inRoot,
                               std::function<void(DataType *, void *)> const & inFuncObj,
                               void * ioFuncArg)
{
    if (nullptr == inRoot) return;

    std::stack<BinaryTreeNode<DataType> *> vAuxStack;

    vAuxStack.push(inRoot);
    vAuxStack.push(nullptr);
    if (inRoot->mRight != nullptr) vAuxStack.push(inRoot->mRight);
    if (inRoot->mLeft != nullptr) vAuxStack.push(inRoot->mLeft);
    while (!vAuxStack.empty())
    {
        BinaryTreeNode<DataType> * vNode = vAuxStack.top();

        if (nullptr == vNode) {
            vAuxStack.pop();
            vNode = vAuxStack.top();
            vAuxStack.pop();
            inFuncObj(vNode->mData, ioFuncArg);
            continue;
        }
        else
        {
            vAuxStack.push(nullptr);
            if (vNode->mRight != nullptr) vAuxStack.push(vNode->mRight);
            if (vNode->mLeft != nullptr) vAuxStack.push(vNode->mLeft);
        }
    }
}

template<typename DataType>
void MorrisPostorderTraversal(BinaryTreeNode<DataType> * inRoot,
                              std::function<void(DataType *, void *)> const & inFuncObj,
                              void * ioFuncArg)
{
    liuzan::DynamicAssert(false,
        "Morris traversal isn't suitable to postorder traversal due to no recording space guarantee.\n"
        "In postorder traversel, the prevous/next node in order is the root of subtree.");
}

template<typename DataType>
void RightwardHierarchicalTraversal(BinaryTreeNode<DataType> * inRoot,
                                    std::function<void(DataType *, void *)> const & inFuncObj,
                                    void * ioFuncArg)
{
    if (nullptr == inRoot) return;

    std::queue<BinaryTreeNode<DataType> *> vQueue;

    inFuncObj(inRoot->mData, ioFuncArg);
    if (inRoot->mLeft != nullptr) vQueue.push(inRoot->mLeft);
    if (inRoot->mRight != nullptr) vQueue.push(inRoot->mRight);
    while (!vQueue.empty())
    {
        BinaryTreeNode<DataType> * vNode = vQueue.front();
        vQueue.pop();
        inFuncObj(vNode->mData, ioFuncArg);
        if (vNode->mLeft != nullptr) vQueue.push(vNode->mLeft);
        if (vNode->mRight != nullptr) vQueue.push(vNode->mRight);
    }
}

template<typename DataType>
void ZwardHierarchicalTraversal(BinaryTreeNode<DataType> * inRoot,
                                std::function<void(DataType *, void *)> const & inFuncObj,
                                void * ioFuncArg)
{
    if (nullptr == inRoot) return;

    std::deque<BinaryTreeNode<DataType> *> vAuxDeque;

    vAuxDeque.push_back(inRoot);
    vAuxDeque.push_back(nullptr);
    BinaryTreeNode<DataType> * vNode = nullptr;
    bool vRightward = true;
    while (!vAuxDeque.empty())
    {
        if (vRightward)
        {
            vNode = vAuxDeque.front();
            vAuxDeque.pop_front();
        }
        else
        {
            vNode = vAuxDeque.back();
            vAuxDeque.pop_back();
        }

        if (nullptr == vNode)
        {
            if (!vAuxDeque.empty())
            {
                vRightward = !vRightward;
                if (vRightward) vAuxDeque.push_back(nullptr);
                else vAuxDeque.push_front(nullptr);
            }
        }
        else
        {
            inFuncObj(vNode->mData, ioFuncArg);
            if (vRightward)
            {
                if (vNode->mLeft != nullptr) vAuxDeque.push_back(vNode->mLeft);
                if (vNode->mRight != nullptr) vAuxDeque.push_back(vNode->mRight);
            }
            else
            {
                if (vNode->mRight != nullptr) vAuxDeque.push_front(vNode->mRight);
                if (vNode->mLeft != nullptr) vAuxDeque.push_front(vNode->mLeft);
            }
        }
    }
}

int TestBinaryTreeTraversal(void)
{
    BinaryTreeNode<std::string> * vBinTree = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("L0_0"));
    BinaryTreeNode<std::string> * vLeft = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("L1_0"));
    BinaryTreeNode<std::string> * vRight = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("L1_1"));
    vBinTree->mLeft = vLeft;
    vBinTree->mRight = vRight;

    BinaryTreeNode<std::string> * vSubRoot = vBinTree->mLeft;
    vLeft = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("L2_0"));
    vRight = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("L2_1"));
    vSubRoot->mLeft = vLeft;
    vSubRoot->mRight = vRight;

    vSubRoot = vBinTree->mRight;
    vLeft = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("L2_2"));
    vRight = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("L2_3"));
    vSubRoot->mLeft = vLeft;
    vSubRoot->mRight = vRight;

    std::function<void(std::string *, void *)> vFuncObj = [](std::string * vStr, void * vOtherArgs) {
        std::cout << *vStr << "->"; };

    std::cout << "===>Output of recursive preorder traversal<===" << std::endl;
    RecursivePreorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << "===>Output of stacked preorder traversal<===" << std::endl;
    StackedPreorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << "===>Output of Morris preorder traversal<===" << std::endl;
    MorrisPreorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "===>Output of recursive midorder traversal<===" << std::endl;
    RecursiveMidorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << "===>Output of stacked midorder traversal<===" << std::endl;
    StackedMidorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << "===>Output of Morris midorder traversal<===" << std::endl;
    MorrisMidorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "===>Output of recursive postorder traversal<===" << std::endl;
    RecursivePostorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << "===>Output of stacked postorder traversal<===" << std::endl;
    StackedPostorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << "===>Output of Morris postorder traversal<===" << std::endl;
    try {
        MorrisPostorderTraversal(vBinTree, vFuncObj, nullptr);
    } catch (LiuZan::AssertException const & e) {
        std::cout << e.what();
        std::cout << std::endl;
        std::cout << std::endl;
    }

    std::cout << "===>Output of rightward hierarchical traversal<===" << std::endl;
    RightwardHierarchicalTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "===>Output of zward hierarchical traversal<===" << std::endl;
    ZwardHierarchicalTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << std::endl;
    std::cout << std::endl;

    return 0;
}

TEST(LeetCode, BinTreeTest)
{
    TestBinaryTreeTraversal();
}
