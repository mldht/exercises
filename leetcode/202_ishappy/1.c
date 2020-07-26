nt getPrime(int n)
{
    if(n <= 2)
    {
        return n;
    }

    int i;
    for(i = 2; i * i <= n; ++i)
    {
        if(n%i == 0)
        {
            ++n;
            i  = 2;
        }
    }

    return n;
}

struct hash 
{
    int num;
    struct hash *next;
};

int getSquaredSum(int n)
{
    int sum = 0;
    while(n)
    {
        int tmp = n%10;
        sum += tmp * tmp;
        n = n/10;
    }
    return sum;
}

bool isHappy(int n){

    int tableSize = getPrime(1000);
    struct hash pool[1000];
    struct hash **pRoot = (struct hash **)malloc(sizeof(struct hash *) * tableSize);
    int i;
    for(i = 0; i < tableSize; ++i)
    {
        pRoot[i] = NULL;
    }
    int pool_idx =0;

    while(1)
    {
        int sum = getSquaredSum(n);
        if(sum == 1)
        {
            return true;
        }

        int hash_idx = sum%tableSize;
        struct hash *iter = pRoot[hash_idx];
        while(iter && iter->num != sum)
        {
            iter = iter->next;
        }

        if(iter)
        {
            return false;
        }
        else
        {
            struct hash *item = &pool[pool_idx++];
            item->num = sum;
            item->next = NULL;
            item->next = pRoot[hash_idx];
            pRoot[hash_idx] = item;
        }
        n = sum;
    }
    return false;
}
