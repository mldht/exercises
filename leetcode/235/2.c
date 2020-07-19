/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool search(struct TreeNode *root, struct TreeNode *p)
{
    if(!root)
    {
        return false;
    }
    if( root->val == p->val)
    {
        return true;
    }
    else if( root->val > p->val)
    {
        return search(root->left, p);
    }
    else
    {
        return search(root->right, p);
    }
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    
        struct TreeNode * ret = NULL;
        bool r1 = search(root, p);
        bool r2 = search(root, q);
        if(r1 && r2)
        {
            ret =root;
        }
        else
        {
            return ret;
        }

        struct TreeNode * l1 = NULL;
        if(root->left)
        {
            l1= lowestCommonAncestor(root->left, p, q);
        }
        struct TreeNode *l2 = NULL;
        if(root->right)
        {
            l2= lowestCommonAncestor(root->right, p, q);
        }

        if(l1)
        {
            ret = l1;
        }
        if(l2)
        {
            ret = l2;
        }
        return ret;
}
