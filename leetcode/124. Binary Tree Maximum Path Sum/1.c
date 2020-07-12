tion for a binary tree node.
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

    if( left < 0)
    {
        left = 0;
    }
    if(right < 0)
    {
        right = 0;
    }
    max = (left + right + root->val) > max ? (left+right + root->val): max;
    if(left < right)
    {
        left = right;
    }
    return left + root->val;
}

int maxPathSum(struct TreeNode* root){
    max = (int)((unsigned int )1 << 31);
    helper(root);
    return max;
}
