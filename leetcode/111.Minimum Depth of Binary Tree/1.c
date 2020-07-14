/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int min;

void helper(struct TreeNode *root, int cur)
{
    if(!root)
    {
        return;
    }

    if(!root->left && !root->right)
    {
        if(cur + 1  < min)
        {
            min = cur + 1;
        }
        return;
    }

    helper(root->left, cur + 1);
    helper(root->right, cur + 1);
}

int minDepth(struct TreeNode* root){
    if(!root)
    {
        return 0;
    }
    min =  ( (unsigned)1 << 31 ) -1;
    helper(root, 0);
    return min;
}
