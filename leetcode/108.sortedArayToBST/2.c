tion for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void helper( struct TreeNode **root, int *nums, int s, int e)
{
    if(s > e)
    {
        return;
    }
    int mid = (e -s+1) / 2 + s;

    *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    (*root)->left = (*root)->right = NULL;
    (*root)->val = nums[ mid];

    helper(&(*root)->left, nums, s, mid-1);
    helper(&(*root)->right, nums, mid+1, e);
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){

    struct TreeNode *root = NULL;
    helper(&root, nums, 0, numsSize -1);
    return root;
}


