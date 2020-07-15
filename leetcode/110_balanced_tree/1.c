/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int get_height(struct TreeNode *root)
{
    if(!root)
    {
        return 0;
    }

    int left = get_height(root->left) + 1;
    int right = get_height(root->right) + 1;

    return left > right ? left : right;
}

bool _isBalanced(struct TreeNode* root){
    if( !root)
    {
        return true;
    }
    int left = get_height(root->left);
    int right = get_height(root->right);

    if( left - right <= 1 && left-right >= -1)
    {
        return true;
    }
    return false;
}

bool isBalanced(struct TreeNode* root){
    if( !root)
    {
        return true;
    }

    if(_isBalanced(root) == false )
    {
        return false;
    }
    bool ret1 = isBalanced(root->left);
    bool ret2 = isBalanced(root->right);
    if(!ret1 || !ret2)
    {
        return false;
    }

    return true;

}
