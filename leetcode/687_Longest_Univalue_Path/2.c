/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int max;

int helper(struct TreeNode *root, struct TreeNode *parent)
{
    if(!root)
    {
        return 0;
    }

    int left = helper(root->left, root);
    int right = helper(root->right, root);

    max = (left + right) > max ? (left + right) : max;
    if( parent && parent->val == root->val)
    {
        return (left + 1) > (right + 1) ? (left + 1): (right + 1);        
    }
    else
    {
        return 0;
    }
}

int longestUnivaluePath(struct TreeNode* root){
    max = 0;
    helper(root, NULL);
    return max;
}
