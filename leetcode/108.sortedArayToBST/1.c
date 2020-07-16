/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void inorder(struct TreeNode *root, int *nums, int *idx)
{
    if(!root)
    {
        return;
    }

    inorder(root->left, nums, idx );
    root->val = nums[*idx];
    *idx = *idx + 1;
    inorder(root->right, nums, idx);
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){

    if(numsSize == 0)
    {
        return NULL;
    }

    struct TreeNode *pool = (struct TreeNode *)malloc(sizeof(struct TreeNode) * numsSize);

    struct TreeNode *queue[100000];
    int size = 0;
    int head = 0;
    int tail = 0;
    int pool_idx = 0;
    int pool_size = numsSize;
    struct TreeNode *root = &pool[pool_idx++];
    --pool_size;

    root->left = root->right = NULL;
    queue[tail++] = root;
    ++size;

    while(size > 0 && pool_size > 0)
    {
        struct TreeNode *p = queue[head++];
        --size;

        if(pool_size-- > 0)
        {
            p->left = &pool[pool_idx++];
            p->left->left = p->left->right = NULL;
            queue[tail++] = p->left;
            ++size;
        }
        if(pool_size-- > 0)
        {
            p->right = &pool[pool_idx++];
            queue[tail++] = p->right;
            p->right->left = p->right->right = NULL;
            ++size;
        }
    }

    int idx = 0;
    inorder(root, nums, &idx);
    return root;
}
