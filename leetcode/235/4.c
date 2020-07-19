tion for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    
    struct TreeNode * iter = root;
    while( iter)
    {
        if( iter->val > p->val && iter->val > q->val)
        {
            iter = iter->left;
        }
        else if( iter->val < p->val && iter->val < q->val)
        {
            iter = iter->right;
        }
        else
        {
            return iter;
        }
    }
    return NULL;
}
