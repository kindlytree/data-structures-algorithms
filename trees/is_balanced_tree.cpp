//后序递归求解
#include <vector>
#include <iostream>
#include "binary_tree.h"


bool nodeHeight(TreeNode* root, int& height)
{
    if(!root) 
    {
        height = 0;
        return true;
    }
    int left_height, right_height;
    if(!nodeHeight(root->left, left_height))return false;
    if(!nodeHeight(root->right, right_height))return false;
    int height_diff = abs(left_height-right_height);
    if(height_diff >= 2)
    {
        return false;
    }
    height = std::max(left_height, right_height) + 1;
    return true;
}

bool isBalanced(TreeNode* root) {
    int height;
    bool is_balanced = nodeHeight(root, height);
    return is_balanced; 
}

int main(){
    //std::vector<int> root = {1,2,3,4, NULL, NULL, 4, NULL, NULL,3,NULL, NULL, 2, NULL, NULL};
    std::vector<int> tree = {1, NULL, 2, NULL,3,NULL, NULL};
    TreeNode *root = NULL;
    int idx = 0;
    buildBinaryTreeRecursive(&root, tree, idx);
    bool is_balanced = isBalanced(root);
    std::cout << is_balanced << std::endl;
}