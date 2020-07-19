#include <stdio.h>
#include <stdbool.h>

  struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
  };



bool search(struct TreeNode *root, struct TreeNode *p)
{
    if(!root || root->val != p->val)
    {
        return false;
    }
    if( root->val == p->val)
    {
        return true;
    }
    return search (root->left, p) || search (root->right, p);
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

int main(void)
{
	freopen("1.txt", "r", stdin);
	struct TreeNode pool[100000];
	int idx = 0;
	struct TreeNode *queue[10000];
	int head = 0;
	int tail = 0;
	int size = 0;
	int val, val2;
	char text[4];
	struct TreeNode *root = NULL;
	
	if(scanf("%d", &val) != EOF)
	{
		root = &pool[idx++];
		root->val = val;
		root->left = root->right = NULL;

		queue[tail++] = root;
		++size;

	}

	struct TreeNode *iter = NULL;
	while( size > 0)
	{
		iter = queue[head++];
		--size;
		char tmp;
		scanf("%c", &tmp);
		
		char empty[5];
		int r1 = scanf("%d", &val);
		if(r1 == 0)
		{
			r1 = scanf("%4s", empty);
			if( r1 == EOF)
			{
				break;
			}
		}
		else if(r1 > 0)
		{
			struct TreeNode *p = &pool[idx++];
			p->val = val;
			//printf("val: %d\n", val);
			iter->left = p;
			p->left = p->right = NULL;

			queue[tail++] = p;
			++size;
			
		}
		else 
		{
			break;
		}

		scanf("%c", &tmp);

		int r2 = scanf("%d", &val2);
		if(r2 == 0)
		{
			r2 = scanf("%4s", empty);
			if(r2 == EOF)
			{
				break;
			}
		}
		else if( r2 > 0)
		{
			struct TreeNode *p = &pool[idx++];
			p->val = val2;
			//printf("%d\n", val2);
			p->left = p->right = NULL;
			iter->right = p;

			queue[tail++] = p;
			++size;
		}
		else
		{
			break;
		}
	}


	struct TreeNode p, q;
	p.left= p.right = q.left = q.right = NULL;
	p.val = 2;
	q.val = 8;

	struct TreeNode *ret = lowestCommonAncestor(root, &p, &q);
	return 0;
}
