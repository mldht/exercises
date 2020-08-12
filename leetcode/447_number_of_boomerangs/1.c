struct hash
{
    int dist;
    int cnt;
    struct hash *next;
};

int getPrime(int n)
{
       // n = n * 2;
   // return 10;
    if(n < 4)
    {
        return n;
    }
    if(!(n & 1))
    {
        ++n;
    }
    int i;
    for(i = 3; i *i < n; i+=2)
    {
        if(n%i == 0)
        {
            n+=2;
            i = 1;
            continue;
        }
    }

    //return 5393;
    if (n > 987)
    {
        return 987;
    }
    return n;
}


int numberOfBoomerangs(int** points, int pointsSize, int* pointsColSize){

    if(pointsSize <= 2)
    {
        return 0;
    }
    int size = pointsSize * (pointsSize -1)/2;
    int hash_size = getPrime(size);

    struct hash *pool = (struct hash *)malloc(sizeof(struct hash) * pointsSize);
    struct hash *root = (struct hash *) malloc(sizeof(struct hash) * hash_size);

    int i;

    
    int sum = 0;
    for(i = 0; i < pointsSize; ++i)
    {
        int j;

        for(j = 0; j < hash_size; ++j)
        {
            root[j].next = NULL;
            root[j].cnt = 0;
        }
        int pool_idx = 0;        

        for(j = 0; j < pointsSize; ++j)
        {
            int dist = (points[i][0] - points[j][0]) *(points[i][0] - points[j][0]);
            dist += (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);

            int hash_idx = dist%hash_size;
            struct hash *iter = root[hash_idx].next;
            while(iter && iter->dist != dist)
            {
                iter = iter->next;
            }

            if(iter)
            {
                //
                ++iter->cnt;
                sum += (iter->cnt-1)*2;                
                
            }
            else
            {
                struct hash *tmp = pool + pool_idx++;
                tmp->dist = dist;
                tmp->cnt = 1;
                tmp->next = root[hash_idx].next;
                root[hash_idx].next = tmp;
            }

        }

       /* for(j = 0; j < hash_size; ++j)
        {
            struct hash *iter = root[j].next;
            while(iter)
            {
                sum += iter->cnt * (iter->cnt -1);
                iter = iter->next;
            }
        }*/
    }

    return sum;
}
