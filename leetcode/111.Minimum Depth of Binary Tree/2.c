/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int minDepth(struct TreeNode* root){

    if(!root)
    {
        return 0;
    }
    if(!root->left && !root->right)
    {
        return 1;
    }

    int left = ((unsigned int)1 << 31) -1;
    if(root->left)
     left = minDepth(root->left);
    int right = ((unsigned) 1 << 31) -1;
    if(root->right)
    {
     right = minDepth(root->right);
    }
    if( left > right)
    {
        left = right;
    }

    return left + 1;
}
