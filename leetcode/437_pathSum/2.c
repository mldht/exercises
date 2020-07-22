/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int helper(struct TreeNode *root, int sum, int value)
{
    if(!root)
    {
        return 0;
    }
    int ret = 0;
    if(value + root->val == sum)
    {
        ret = 1;
    }

    return ret + helper(root->left, sum, value + root->val) + 
                helper(root->right, sum, value + root->val);

}

int pathSum(struct TreeNode* root, int sum){
    if(!root)
    {
        return 0;
    }
    return helper(root, sum, 0) + pathSum(root->left, sum) + pathSum(root->right, sum);
}


