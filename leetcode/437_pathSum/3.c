/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct hash
{
    int number;
  //  int cnt;
    struct hash *next;
};

struct hash pool[1024];
int pool_idx;

struct hash * hash_root[1024];

void helper(struct TreeNode *root, int value, int sum, int *cnt)
{
    if(!root)
    {
        return;
    }
    int new_val = value + root->val;
    int tmp = new_val - sum;
    if(tmp < 0)
    {
        tmp = -tmp;
    }

    int idx = tmp &(1024-1);

    struct hash *iter = hash_root[idx];
    while(iter /*&& iter->number != new_val*/ )
    {
        if(new_val == sum + iter->number)
        {
            *cnt += 1;
        }
        iter = iter->next;
    }

    //if(iter)
   // {
   //     *cnt += 1;
   // }

    struct hash *item = &pool[pool_idx++];
    item->number = new_val;
    item->next = NULL;
    tmp = (new_val > 0) ? new_val : -new_val;
    int new_idx = tmp & (1024-1);
    if(hash_root[new_idx] == NULL)
    {
        hash_root[new_idx] = item;
    }
    else
    {
        item->next = hash_root[new_idx];
        hash_root[new_idx] = item;
    }

    helper(root->left, new_val, sum, cnt);
    helper(root->right, new_val, sum, cnt);

    iter = hash_root[new_idx];
    struct hash *prev = NULL;
    while(iter && iter != item)
    {
        iter = iter->next;
        prev= iter;
    }

    if(prev== NULL)
    {
        hash_root[new_idx] = iter->next;
    }
    else
    {
        prev->next = iter->next;
    }

}

int pathSum(struct TreeNode* root, int sum){
    int i;
    for(i = 0; i < 1000; ++i)
    {
        hash_root[i] = NULL;
    }
    pool_idx= 0;
    hash_root[0] = &pool[pool_idx++];
    hash_root[0]->number = 0;
    hash_root[0]->next = NULL;

    int cnt = 0;
    helper(root, 0, sum, &cnt);
    return cnt;
}

