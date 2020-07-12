/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int max;

int helper(struct TreeNode *root)
{
    if(!root)
    {
        return 0;
    }

    int left = helper(root->left);
    int right = helper(root->right);

  

    if( root->left && root->left->val == root->val)
    {
        ++left;
    }
    else
    {
        left = 0;
    }

    if(root->right && root->right->val == root->val)
    {
        ++right;
    }
    else
    {
        right = 0;
    }

  max = (left + right) > max ? (left + right) : max;    

    return (left > right) ? left : right;
}

int longestUnivaluePath(struct TreeNode* root){
    max = 0;
    helper(root);
    return max;
}
