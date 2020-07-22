/*Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void helper(struct TreeNode *root, int sum, int value, int *cnt)
{
    if(!root)
    {
        return;
    }

    if( value + root->val == sum)
    {
        *cnt += 1;
    }
    helper(root->left, sum, value + root->val, cnt);
    helper(root->right, sum, value + root->val, cnt);

}

void helper2(struct TreeNode *root, int sum, int *cnt)
{
    if(!root)
    {
        return;
    }

    helper(root, sum, 0, cnt);
    helper2(root->left, sum, cnt);
    helper2(root->right, sum, cnt);
}
int pathSum(struct TreeNode* root, int sum){

    int cnt = 0;
    helper2(root, sum, &cnt);
    return cnt;
}
