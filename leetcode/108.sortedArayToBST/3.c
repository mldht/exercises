/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode * helper(int *nums, int s, int e)
{
    if(s > e)
    {
        return NULL;
    }
    int mid = (e -s+1) / 2 + s;

    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = nums[ mid];

    root->left = helper(nums, s, mid-1);
    root->right = helper(nums, mid+1, e);
    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){

    return helper(nums, 0, numsSize -1);
}


