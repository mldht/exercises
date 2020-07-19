/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int helper(struct TreeNode *root, bool isleft)
{
    if(!root)
    {
        return 0;
    }
    if(root->left == NULL && root->right == NULL)
    {
        return isleft ? root->val : 0;
    }

    return helper(root->left, true) + helper(root->right, false);
}

int sumOfLeftLeaves(struct TreeNode* root){
    if( !root)
    {
        return 0;
    }

    return helper(root, false);
}
