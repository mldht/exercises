
int helper(struct TreeNode *root, struct TreeNode **prev)
{
    int min = ((unsigned int) 1 << 31) -1;
    if(root->left)
    {
        int left = helper(root->left, prev);
        if(left < min)
        {
            min = left;
        }
    }

    if(*prev)
    {
        min = min > ( root->val - (*prev)->val ) ? (root->val - (*prev)->val ) : min; 
    }
    
   *prev = root;
    if(root->right)
    {
        int right = helper(root->right, prev);
        if(right < min)
        {
            min = right;
        }
    }


    return min;
}

int getMinimumDifference(struct TreeNode* root){

    if(!root)
    {
        return 0;
    }

    struct TreeNode *prev = NULL;
    return helper(root, &prev);
}

