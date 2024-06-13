
//中序遍历，列出所有可能的path
// 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
// 路径和 是路径中各节点值的总和。
// 给你一个二叉树的根节点 root ，返回其 最大路径和 。

// 示例 1：
// 输入：root = [1,2,3]
// 输出：6
// 解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
// 示例 2：


// 输入：root = [-10,9,20,null,null,15,7]
// 输出：42
// 解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
 

// 提示：
// 树中节点数目范围是 [1, 3 * 104]
// -1000 <= Node.val <= 1000
// 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
// 路径和 是路径中各节点值的总和。
// 给你一个二叉树的根节点 root ，返回其 最大路径和 。

 

// 示例 1：
// 输入：root = [1,2,3]
// 输出：6
// 解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
// 示例 2：


// 输入：root = [-10,9,20,null,null,15,7]
// 输出：42
// 解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
 

// 提示：
// 树中节点数目范围是 [1, 3 * 104]
// -1000 <= Node.val <= 1000


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    int candidate_paths(TreeNode* root, std::vector<int>&candidate_sum_max)
    {
        int max_left, max_right;
        if(!root){
            return 0;
        }
        if(root && !root->left && !root->right){
            return root->val;
        }
        else if(root && root->left && !root->right){
            max_left = candidate_paths(root->left, candidate_sum_max);
            candidate_sum_max.push_back(max_left);
            candidate_sum_max.push_back(root->val);
            //return max_left + root->val;
            if(max_left  > 0){
                return max_left + root->val;
            }else{
                return root->val;
            }
        }else if(root && !root->left && root->right){
            max_right = candidate_paths(root->right, candidate_sum_max);
            candidate_sum_max.push_back(max_right);
            candidate_sum_max.push_back(root->val);
            if(max_right  > 0){
                return max_right + root->val;
            }else{
                return root->val;
            }
        }else{
            max_left = candidate_paths(root->left, candidate_sum_max);
            max_right = candidate_paths(root->right, candidate_sum_max);
            //三个可能的值;
            int max_max = std::max(max_left, max_right);
            int candidate = max_left + root->val + max_right;
            candidate_sum_max.push_back(candidate);
            candidate_sum_max.push_back(max_max);
            //candidate_sum_max.push_back(root->val);
            //return max_max + root->val;
            if(max_max > 0){
                return max_max + root->val;
            }else{
                return root->val;
            }
        }
    }


    int maxPathSum(TreeNode* root) {
        std::vector<int> max_candidate;
        int max_ret = candidate_paths(root, max_candidate);
        for(int i = 0; i < max_candidate.size(); i++){
            if(max_ret < max_candidate[i]){
                max_ret = max_candidate[i];
            }
        }
        return max_ret;
    }
};