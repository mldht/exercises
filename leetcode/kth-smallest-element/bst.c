
  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };
 

int ret;
void inorder(struct TreeNode *root, int k, int *i)
{
	if( root->left)
	{
		inorder(root->left, k, i);
	}

	++*i;
	if(*i == k)
	{
		ret = root->val;
		return;
	}

	if(root->right)
	{
		inorder(root->right, k, i);
	}
}

int kthSmallest(struct TreeNode* root, int k){

	int i = 0;
	inorder(root, k, &i);
	return ret;

}

