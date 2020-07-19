/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    
    if(!root)
    {
        return NULL;
    }

    int min; 
    int max;
    if( p->val > q->val)
    {
        min = q->val;
        max = p->val;
    }
    else
    {
        min = p->val;
        max = q->val;
    }
    if(root->val > max)
    {
        return lowestCommonAncestor(root->left, p, q);
    }
    else if( root->val < min)
    {
        return lowestCommonAncestor(root->right, p, q);
    }
    else
    {
        return root;
    }
}
