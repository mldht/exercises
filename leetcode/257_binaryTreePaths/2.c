/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int getNumberOfLeaves( struct TreeNode *root)
{
    if(!root)
    {
        return 0;
    }

    if(root->left == NULL && root->right == NULL)
    {
        return 1;
    }

    return getNumberOfLeaves(root->left) + getNumberOfLeaves(root->right);
}

int g_idx;
char **g_ret;

int getNumberString( int val, char *text)
{
    if(val == 0)
    {
        text[0] = '0';
        return 1;
    }
    int idx = 0;
    bool negative = false;
    if(val < 0)
    {
        *(text++) = '-';
        val = -val;
        negative = true;
    }
    while( val > 0)
    {
        text[idx++] = '0' + val%10;
        val = val/10;
    }

    int i;
    for(i = 0; i < idx/2; ++i)
    {
        char tmp = text[i];
        text[i] = text[idx - i - 1];
        text[idx-1-i] = tmp;
    }

    return  negative ? (idx+1) : idx;
}
void helper(struct TreeNode *root, char *buf, int idx)
{
    if(!root)
    {
        return;
    }

    if(idx != 0)
    {
        buf[idx++] = '-';
        buf[idx++] = '>';
    }

    int len = getNumberString(root->val, buf + idx);
    idx += len;

    g_ret[g_idx] = (char *)malloc(sizeof(char) * (idx+1));

    int i;
    for(i  = 0; i < idx; ++i)
    {
        g_ret[g_idx][i] = buf[i];
    }
    if(root->left == NULL && root->right == NULL)
    {
        g_ret[g_idx][i] = '\0';
        ++g_idx;
        return;
    }

    helper(root->left, buf, idx);
    helper(root->right, buf, idx);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** binaryTreePaths(struct TreeNode* root, int* returnSize){

    if(!root)
    {
        *returnSize = 0;
        return NULL;
    }

    int leaves = getNumberOfLeaves(root);

    g_ret = (char **)malloc(sizeof(char *) * leaves);

    *returnSize = leaves;

    g_idx = 0;

    char buffer[1000];
    helper(root, buffer, 0);

    return g_ret;

}
