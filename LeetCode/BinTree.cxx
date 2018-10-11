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

#include <iostream>
#include <string>
#include <functional> //std::function<>
#include <stack> //std::stack<>
#include <LZAssert.h> //LiuZan::DynamicAssert<>()

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

int main(void)
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

    return 0;
}
