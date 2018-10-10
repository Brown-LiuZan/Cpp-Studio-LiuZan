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
                                std::function<void(DataType *, void *)> & inFuncObj,
                                void * ioFuncArg)
{
    if (inRoot == nullptr) return;

    inFuncObj(inRoot->mData, ioFuncArg);
    if (inRoot->mLeft != nullptr) RecursivePreorderTraversal(inRoot->mLeft, inFuncObj);
    if (inRoot->mRight != nullptr) RecursivePreorderTraversal(inRoot->mRight, inFuncObj);
}

template<typename DataType>
void StackedPreorderTraversal(BinaryTreeNode<DataType> * inRoot,
                              std::function<void(DataType *, void *)> & inFuncObj,
                              void * ioFuncArg)
{
    if (nullptr == inRoot) return;

    inFuncObj(inRoot->mData, ioFuncArg);

    std::stack<BinaryTreeNode<DataType> *> vAuxStack;
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
                             std::function<void(DataType *, void *)> & inFuncOjb,
                             void * ioFuncArg)
{
    BinaryTreeNode<DataType> * vCur = inRoot;
    BinaryTreeNode<DataType> * vPrev= nullptr;

    while (vCur != nullptr)
    {
        if (vCur->mLeft == nullptr)
        {
            inFuncObj(vCur->mData, nullptr);
        }
        else
        {
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
    
    std::function<void(std::string *)> vFuncObj = [](std::string * vStr, void * vOtherArgs) {
        std::cout << *vStr << std::endl; };

    std::cout << "===>Output of recursive preorder traversal<===" << std::endl;
    RecursivePreorderTraversal(vBinTree, vFuncObj, nullptr);
    std::cout << "===>Output of stacked preorder traversal<===" << std::endl;
    StackedPreorderTraversal(vBinTree, vFuncObj, nullptr);

    return 0;
}
