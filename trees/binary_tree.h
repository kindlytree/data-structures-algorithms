

#include<stack>
#include<queue>

#define INT_MAX ((int)(~0U>>1))
#define INT_MIN (-INT_MAX - 1)

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
}TreeNode;

//以先序的顺序递归构建一颗二叉树;
void buildBinaryTreeRecursive(TreeNode** root, std::vector<int>& tree, int& idx)
{
    *root = new TreeNode(tree[idx]);
    idx += 1;
    if(idx < tree.size()){
        int val = tree[idx];
        if(val != NULL)
        {
            buildBinaryTreeRecursive(&(*root)->left, tree, idx);
        }
    }
    idx +=1;
    if(idx < tree.size()){
        int val = tree[idx];
        if(val != NULL)
        {
            buildBinaryTreeRecursive(&(*root)->right, tree, idx);
        }
    }
}

//以层级顺序构建一颗二叉树
//如果为NULL其实为0，最好找出一个特殊的数字来表示空节点
TreeNode* buildBinaryTreeByLevelOrder(std::vector<int>& root)
{
    std::queue<TreeNode*>queue_;
    TreeNode* root_ = new TreeNode(root[0]);
    queue_.push(root_);
    int idx = 1;
    while(!queue_.empty() && idx < root.size())
    {
        int level_size_ = queue_.size();
        for(int i = 0; i < level_size_; i++)
        {
            TreeNode* node = queue_.front();
            queue_.pop();
            if(root[idx] != NULL)
            {
                TreeNode* new_node_ = new TreeNode(root[idx]);
                node->left = new_node_;
                queue_.push(new_node_);
            }
            idx++;
            if(root[idx] != NULL)
            {
                TreeNode* new_node_ = new TreeNode(root[idx]);
                node->right = new_node_;
                queue_.push(new_node_);
            }
            idx++;
        }
    }
    return root_;
}