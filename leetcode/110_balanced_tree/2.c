/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool _isBalanced(struct TreeNode *root, int *height)
{
    if(!root)
    {
        *height = 0;
        return true;
    }

    int height1 = 0;
    int height2 = 0;
    bool left = _isBalanced(root->left, &height1);
    bool right = _isBalanced(root->right, &height2);
    if(!left || !right)
    {
        return false;
    }

    if( height1 - height2 >= -1 && height1 - height2 <= 1)
    {
        *height = (height1 > height2) ? (height1 + 1) : (height2 + 1); 
        return true;
    }
    else
    {
        return false;
    }
}


bool isBalanced(struct TreeNode* root){

    int height;

   return  _isBalanced(root, &height);

}
