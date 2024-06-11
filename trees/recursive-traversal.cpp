#include <vector>
#include <iostream>
#include "binary_tree.h"


void preorderTraversal(TreeNode* root, std::vector<int>& result) {
    if(root)
    {
        result.push_back(root->val);
        preorderTraversal(root->left, result);
        preorderTraversal(root->right, result);
    }
}

void postorderTraversal(TreeNode* root, std::vector<int>& result) {
    if(root){
        postorderTraversal(root->left, result);
        postorderTraversal(root->right, result);
        result.push_back(root->val);
    }
}

void inorderTraversal(TreeNode* root, std::vector<int>& result) {
    if(root){
        inorderTraversal(root->left, result);
        result.push_back(root->val);
        inorderTraversal(root->right, result);
    }
}

int main(){
    std::vector<int> result_preorder;
    std::vector<int> tree = {1, 2, 4, NULL, NULL, NULL, 3, NULL, NULL};
    TreeNode *root = NULL;
    int idx = 0;
    buildBinaryTreeRecursive(&root, tree, idx);
    preorderTraversal(root, result_preorder);
    for(int i = 0; i < result_preorder.size(); i++)
    {
        std::cout << result_preorder[i] ;
    }

    std::vector<int> result_postorder;
    postorderTraversal(root, result_postorder);
    for(int i = 0; i < result_postorder.size(); i++)
    {
        std::cout << result_postorder[i] ;
    }
}