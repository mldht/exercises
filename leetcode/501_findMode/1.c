/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


void helper(struct TreeNode *root, struct TreeNode **prev, int *maxCount, int *count, int *ret, int *idx)
{
    if(!root)
    {
        return 0;
    }

    helper(root->left, prev, maxCount, count, ret, idx);
    if(!*prev || (*prev)->val != root->val)
    {
        *count = 1;
    }
    else
    {
        ++(*count);
    }

    if(*maxCount == *count)
    {
        *idx+=1;
        ret[*idx] = root->val;
       // *maxCount = count;
    }
    else if( *maxCount < *count)
    {
        *idx = 0;
        ret[*idx] = root->val;
        *maxCount = *count;

    }

    *prev = root;
    helper(root->right, prev, maxCount, count, ret, idx);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMode(struct TreeNode* root, int* returnSize){

    int *ret = (int *)malloc(sizeof(int) * 10240);
    int maxCount = 0;
    *returnSize = 0;
    struct TreeNode *prev= NULL;
    int idx =0;
    int count = 0;
    helper(root, &prev, &maxCount, &count, ret,&idx );
    if(root)
    {
        *returnSize = idx + 1;
    }
    else{
        *returnSize = 0;
    }
    return ret;

}
