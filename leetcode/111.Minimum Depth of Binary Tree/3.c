/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */



int minDepth(struct TreeNode* root){

    struct TreeNode * queue[10000];
    int head = 0;
    int tail = 0;
    int size = 0;
    int ret = 0;
    if(root)
    {
        queue[tail++] = root;
        ++size;
     //   ++ret;
    }
    root = NULL;
    while( root || size > 0 )
    {
        ++ret;
        int oldSize = size;
        size = 0;
        while( oldSize > 0)
        {
            struct TreeNode * node = queue[head++];
            --oldSize;

            if(!node->left && !node->right)
            {
                return ret;
            }

            if(node->left)
            {
                queue[tail++] = node->left;
                ++size;
            }
            if(node->right)
            {
                queue[tail++] = node->right;
                ++size;
            }
        }
    }

    return 0;
}
