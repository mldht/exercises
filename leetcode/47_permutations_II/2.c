eturn an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 
 int getPrime(int n)
 {
     if( n <4)
     {
         return n;
     }
     if(n & 1 == 0)
     {
         ++n;
     }

     int i;
     for(i = 3; i *i < n; i+=2)
     {
         if(n %i == 0)
         {
             n+=2;
             i = 1;
         }
     }

    return n;
 }

struct item
{
    int num;
    int cnt;
    struct item *next;
};


void backtrack(struct item **nums, int size, int unique_size, int idx, int **ret, int *retIdx, int *output)
{
    if(idx == size)
    {
        int k = *retIdx;
        int i;
        for(i = 0; i < size; ++i)
        {
            ret[k][i] = output[i];
        }
        *retIdx = k + 1;

        return;
    }

    int i;
    for(i = 0; i < unique_size; ++i)
    {
        if(idx > 0 && output[idx-1] == nums[i]->num)
        {
            continue;
        }

        int count = nums[i]->cnt;
        int j = 0;
        while(nums[i]->cnt > 0)
        {
            output[idx + j] = nums[i]->num;
            --nums[i]->cnt;
             backtrack(nums, size, unique_size, idx + j+1, ret, retIdx, output);
             ++j;
        }
        nums[i]->cnt = count;
    }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){

    int tableSize = getPrime(numsSize);

    struct item *root = (struct item *)malloc(sizeof(struct item) * tableSize);
    struct item *pool = (struct item *)malloc(sizeof(struct item) * numsSize);
    int i;
    for(i = 0; i < tableSize; ++i)
    {
        root[i].cnt = 0;
        root[i].next = NULL;
    }

    int pool_idx = 0;

    int unique_cnt = 0;
    for(i = 0; i < numsSize; ++i)
    {
        int hash_idx = nums[i]%tableSize;
        if(hash_idx < 0)
        {
            hash_idx = -hash_idx;
        }
        struct item *iter = root[hash_idx].next;
        while(iter && iter->num != nums[i])
        {
            iter = iter->next;
        }

        if(iter)
        {
            ++iter->cnt;
        }
        else
        {
            struct item *temp = pool + pool_idx++;
            temp->num = nums[i];
            temp->next = root[hash_idx].next;
            temp->cnt = 1;
            root[hash_idx].next = temp;
            ++unique_cnt;
        }
    }

    struct item **hash_nums = (struct item **)malloc(sizeof(struct item *) * unique_cnt);
    int j = 0;
    for(i = 0; i < tableSize; ++i)
    {
        struct item *iter = root[i].next;
        while(iter)
        {
            hash_nums[j++] = iter;
            iter = iter->next;
        }
    }

    int *output = (int *)malloc(sizeof(int) * numsSize);

    int tmpSize = 1;
    int tmp = numsSize;
    while(tmp > 1)
    {
        tmpSize *= tmp;
        --tmp;
    }
    int **ret = (int **)malloc(sizeof(int *) * tmpSize);
    int *buffer = (int *)malloc(sizeof(int ) * tmpSize * numsSize);

    for(i = 0; i < tmpSize;++i)
    {
        ret[i] = buffer + i * numsSize;
    }

    *returnSize = 0;

    backtrack(hash_nums, numsSize,unique_cnt, 0, ret, returnSize, output);

    *returnColumnSizes = (int *)malloc(sizeof(int) * tmpSize);
    for(i = 0; i < tmpSize; ++i)
    {
        (*returnColumnSizes)[i] = numsSize;
    }
    return ret;
}
