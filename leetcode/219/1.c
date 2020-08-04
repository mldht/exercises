

int getPrime(int n)
{
    if(n <=3)
    {
        return n;
    }

    if(n%2 == 1)
    {
        ++n;
    }

    

    int i;
    for(i = 3; i * i < n; ++i)
    {
        if(n%i == 0)
        {
               n+=2;
               i = 2; 
        }
     }

     return n;
}

struct hash 
{
    int num;
    struct hash *next;
    struct hash *prev;
};


bool containsNearbyDuplicate(int* nums, int numsSize, int k){

    if(k == 0)
    {
        return false;
    }
    int table_size = getPrime(numsSize);

    struct hash *head = (struct hash *)malloc(sizeof(struct hash) * table_size);
    struct hash *tail = (struct hash *)malloc(sizeof(struct hash) * table_size);
  
    struct hash *pool = (struct hash*)malloc(sizeof(struct hash) * k );
    int pool_idx = -1;

    int i;
    for(i = 0; i < table_size; ++i)
    {
        head[i].next = &tail[i];
        head[i].prev = NULL;

        tail[i].prev = &head[i];
        tail[i].next = NULL;
    }

    int cnt = 0;
    for(i = 0; i < numsSize; ++i)
    {
        int hash_idx = nums[i] % table_size;
        if(hash_idx < 0)
        {
            hash_idx = -hash_idx;
        }
        pool_idx = (pool_idx+1) % k;
        struct hash *tmp = pool + pool_idx; 

        struct hash *iter = head[hash_idx].next;
        while(iter && iter->num != nums[i])
        {
            iter = iter->next;
        }

        if(iter)
        {
            return true;
        }

        if(cnt == k)
        {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            tmp->next = tmp->prev = NULL;
        }
        else
        {
            ++cnt;
        }

        tmp->num = nums[i];
        tmp->next = head[hash_idx].next;
        tmp->prev = &head[hash_idx];
        head[hash_idx].next->prev = tmp;
        head[hash_idx].next = tmp;
    }

    return false;
}


