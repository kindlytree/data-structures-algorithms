/*
题目来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/delete-node-in-a-bst


给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

一般来说，删除节点可分为两个步骤：

首先找到需要删除的节点；
如果找到了，删除它。
 

示例 1:

输入：root = [5,3,6,2,4,NULL,7], key = 3
输出：[5,4,6,2,NULL,NULL,7]
解释：给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。
一个正确的答案是 [5,4,6,2,NULL,NULL,7], 如下图所示。
另一个正确答案是 [5,2,6,NULL,4,NULL,7]。


示例 2:

输入: root = [5,3,6,2,4,NULL,7], key = 0
输出: [5,3,6,2,4,NULL,7]
解释: 二叉树不包含值为 0 的节点
示例 3:

输入: root = [], key = 0
输出: []
 

提示:

节点数的范围 [0, 104].
-105 <= Node.val <= 105
节点值唯一
root 是合法的二叉搜索树
-105 <= key <= 105
 
进阶： 要求算法时间复杂度为 O(h)，h 为树的高度。
*/

#include <vector>
#include <iostream>
#include "binary-tree.h"
#include <queue>

//二叉搜索树是满足左子树比当前节点小，右子树比当前节点大的二叉树
//首先找到要删除的节点，然后再执行删除操作

TreeNode* deleteNode(TreeNode* root, TreeNode* parent, int key) {
    if(!root){return root;}
    if(root->val > key)
    {
        deleteNode(root->left, root, key);
    }else if(root->val < key)
    {
        deleteNode(root->right, root, key);
    }else{
        //特殊情况要记录parent节点；
        //删除的节点左子树为空（右子树不空）
        //直接将删除的节点的父节点的左子树根节点或右子树根节点的值赋为删除节点
        if(!root->left && root->right){
            parent->left == root ? parent->left = root->right:parent->right = root->right;
            TreeNode* temp = root;
            root = root->right;
            delete temp;
            temp = nullptr;
        }else if(root->left && !root->right)//如果右子树为空，左子树不为空
        {
            parent->left == root ? parent->left = root->left:parent->right = root->left;
            TreeNode* temp = root;
            root = root->left;
            delete temp;  
            temp = nullptr;       
        }else if(!root->left && !root->right)//如果左右子树均为空，直接删除节点
        {
            parent->left == root ? parent->left = nullptr: parent->right = nullptr;
            delete root;
            root = nullptr;       
        }
        else{
            TreeNode* temp = root->right;
            //删除节点的左右子树非空，从右边节点找到要补上来的点值
            //如果右子树的左子树根节点为空，则直接将右子树的右边补上
            //直接删除temp，将其右节点拼接上
            if(!temp->left && temp->right)
            {
                root->val = temp->val;
                TreeNode* to_be_deleted = temp;
                root->right = temp->right;
                delete to_be_deleted;
                return root;
            }//如果右节点左右孩子均为空，右节点直接补上
            else if(!temp->left && !temp->right)
            {
                root->val = temp->val;
                TreeNode* to_be_deleted = temp;
                root->right = nullptr;
                delete to_be_deleted;
                return root;
            }
            //否则迭代遍历右节点的左子树，将最后一个左孩子节点的值填充；
            while(temp->left->left)
            {
                temp = temp->left;
            }
            root->val = temp->left->val;
            TreeNode* to_be_deleted = temp->left;
            //emp->left->right不为空，则直接接过来
            temp->left = temp->left->right;
            delete to_be_deleted;
        }
    }
    return root;
}

// void  findReplacedNode(int key, TreeNode**current_Node, TreeNode**current_Node_child) {
//     if(key == (*current_Node)->val){
//         if((*current_Node)->left != nullptr){
//             findReplacedNode(key, &(*current_Node)->left, &((*current_Node)->left->right))

//         }
//     }else if(key > )

// }

// TreeNode* deleteNode(TreeNode* root, int key) {
//     if(!root){return root;}
//     if(root->val > key){
//         deleteNode(root->left, key);
//     }
//     else if(root->val < key)
//     {
//         deleteNode(root->right, key);
//     }else{

//     }
// }

//https://blog.csdn.net/qq_59957669/article/details/132167014
// 删除二叉搜索树中的节点
// 二叉搜索树（Binary Search Tree，简称BST）是一种常见的数据结构，它具有以下性质：

// 对于任意节点，其左子树中的所有节点的值都小于该节点的值。
// 对于任意节点，其右子树中的所有节点的值都大于该节点的值。
// 左子树和右子树也都是二叉搜索树。
// 在二叉搜索树中删除节点是一个常见的操作，我们需要保证删除节点后的树仍然满足二叉搜索树的性质。本文将介绍如何在二叉搜索树中删除节点的算法和实现。

// 算法思路
// 删除二叉搜索树中的节点可以分为以下几个步骤：

// 首先，我们需要找到要删除的节点。从根节点开始，比较要删除的节点的值与当前节点的值，根据二叉搜索树的性质，如果要删除的节点的值小于当前节点的值，则继续在左子树中查找；如果要删除的节点的值大于当前节点的值，则继续在右子树中查找；如果要删除的节点的值等于当前节点的值，则找到了要删除的节点。
// 如果找到了要删除的节点，我们需要考虑以下几种情况：
// 如果要删除的节点是叶子节点（没有左子树和右子树），直接将其删除即可。
// 如果要删除的节点只有一个子节点（左子树或右子树），将其子节点替换为要删除的节点。
// 如果要删除的节点有两个子节点，我们可以选择以下两种方法之一：
// 找到要删除节点右子树中的最小节点，将其值替换到要删除的节点上，然后递归地删除右子树中的最小节点。
// 找到要删除节点左子树中的最大节点，将其值替换到要删除的节点上，然后递归地删除左子树中的最大节点。
// 最后，返回更新后的二叉搜索树的根节点引用。


int main(){
    //std::vector<int> root = {3,5,6,NULL,NULL,2,7,NULL,NULL,4,NULL,NULL,1,0,NULL,NULL,8,NULL,NULL};
    //std::vector<int> root = {5,3,2,NULL,NULL,4,NULL,NULL,6,NULL,7,NULL,NULL};
    //std::vector<int> root = {3,1,NULL,2,NULL,NULL,4,NULL,NULL};
    //std::vector<int> root = {1};
    //std::vector<int> root = {3,2,NULL,NULL,5,4,NULL,NULL,10,8,7,NULL,NULL,NULL,15,NULL,NULL};
    //std::vector<int> root = {3,1,NULL,2,NULL,NULL,4,NULL,NULL};
    //std::vector<int> root = {2,1,33,NULL,2,25,40,NULL,NULL,11,31,34,45,10,18,29,32,NULL,36,43,46,4,NULL,12,24,26,30,NULL,NULL,35,39,42,44,NULL,48,3,9,NULL,14,22,NULL,NULL,27,NULL,NULL,NULL,NULL,38,NULL,41,NULL,NULL,NULL,47,49,NULL,NULL,5,NULL,13,15,21,23,NULL,28,37,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,8,NULL,NULL,NULL,17,19,NULL,NULL,NULL,NULL,NULL,NULL,NULL,7,NULL,16,NULL,NULL,20,6};
    //TreeNode* root_node_ = buildBinaryTree(root);
    //std::vector<int> root = {5,3,6,2,4,NULL,7};
    std::vector<int> root = {3, 1, 4, NULL, 2, NULL, NULL};
    TreeNode* root_node_ = buildBinaryTreeByLevelOrder(root);
    //int key = 33;
    int key = 1;
    TreeNode* root_node_after_ = deleteNode(root_node_, root_node_, key);
    printBinaryTreeByLevelOrder(root_node_after_);
    std::cout << std::endl;
}