/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int helper(struct TreeNode *root, int sum, int *arr, int idx)
{
    if(!root)
    {
        return 0;
    }

    arr[idx] = root->val;

    int i;
    int tmp = 0;
    int cnt = 0;
    for(i = idx; i >= 0; --i)
    {
        tmp += arr[i];
        if(tmp == sum)
        {
            ++cnt;
        }
    }

    return cnt + helper(root->left, sum, arr, idx + 1) +
                helper(root->right, sum, arr, idx + 1);

}

int pathSum(struct TreeNode* root, int sum){
    int arr[1000];
    return helper(root, sum, arr, 0);
}


