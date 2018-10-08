#include <iostream>
#include <string>
#include <functional>

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
void PreorderTraversalRecursive(BinaryTreeNode<DataType> * inRoot, std::function<void(DataType const &)> & inFuncObj)
{
    if (inRoot == nullptr) return;

    inFuncObj(*inRoot->mData);
    if (inRoot->mLeft != nullptr) PreorderTraversalRecursive(inRoot->mLeft, inFuncObj);
    if (inRoot->mRight != nullptr) PreorderTraversalRecursive(inRoot->mRight, inFuncObj);
}

int main(void)
{
    BinaryTreeNode<std::string> * vBinTree = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("Brown"));
    BinaryTreeNode<std::string> * vLeft = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("Liyan"));
    BinaryTreeNode<std::string> * vRight = new BinaryTreeNode<std::string>(nullptr, nullptr, new std::string("Henry"));
    vBinTree->mLeft = vLeft;
    vBinTree->mRight = vRight;

    std::function<void(std::string const &)> vFuncObj = [](std::string const & vStr) {
        std::cout << vStr << std::endl; };
    PreorderTraversalRecursive(vBinTree, vFuncObj);

    return 0;
}
