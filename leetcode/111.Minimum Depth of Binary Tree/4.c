/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct myTreeNode
{
    struct TreeNode *node;
    int cnt;
};

struct myTreeNode pool[10000];
int pool_idx;

struct myTreeNode *queue[10000];
int head;
int tail;
int size;

int minDepth(struct TreeNode* root){
    head = tail = size = 0;

    if(root)
    {
        queue[tail] = &pool[pool_idx++];
        ++size;
        queue[tail]->cnt = 1;
        queue[tail]->node = root;
        ++tail;
    }
    root = NULL;
    int ret = 0;
    while( size > 0)
    {
        struct myTreeNode *node = queue[head++];
        --size;
        if(!node->node->left  && !node->node->right)
        {
            return node->cnt;
        }

        if(node->node->left)
        {
            queue[tail] = &pool[pool_idx++];
            queue[tail]->node = node->node->left;
            queue[tail]->cnt = node->cnt + 1;
            ++size;
            ++tail;
        }

        if(node->node->right)
        {
            queue[tail] = &pool[pool_idx++];
            queue[tail]->node = node->node->right;
            queue[tail]->cnt = node->cnt + 1;
            ++size;
            ++tail;
        }        
    }
    return 0;
}
