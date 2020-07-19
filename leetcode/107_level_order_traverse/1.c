/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int depth(struct TreeNode *root)
{
    if(!root)
    {
        return 0;
    }

    int left = depth(root->left) + 1;
    int right = depth(root->right) + 1;

    return left < right ? right : left;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int d = depth(root);
    int **ret = (int **)malloc(sizeof(int *) * d);
    *returnSize = d;
    *returnColumnSizes = (int *)malloc(sizeof(int) * d);

    struct TreeNode *queue[10000];
    int head;
    int tail;
    int size;

    head = tail = size = 0;
    int idx = d -1;

    if(root)
    {
        queue[tail++] = root;
        ++size;
    }

    while( size > 0)
    {
        int oldSize = size;
        (*returnColumnSizes)[idx] = oldSize;
        ret[idx] = (int *)malloc(sizeof(int) * oldSize);
        size = 0;
        int i = 0;
        while(oldSize-- > 0)
        {
            struct TreeNode *temp = queue[head++];
            ret[idx][i++] = temp->val;

            if(temp->left)
            {
                queue[tail++] = temp->left;
                ++size;
            }

            if(temp->right)
            {
                queue[tail++] = temp->right;
                ++size;
            }
        }
        --idx;
    }

    return ret;
}
