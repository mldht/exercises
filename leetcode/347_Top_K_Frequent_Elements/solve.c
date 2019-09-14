#include <stdlib.h>

static int getNextPrime (int N)
{
	if (N % 2 == 0)
	{
		++N;
	}

	int i;
	for (; ; N += 2)
	{
		char found = 1;
		for (i = 3; i*i <= N; i+=2)
		{
			if (N % i == 0)
			{
				found  = 0;
				break;
			}
		}

		if(found == 1)
		{
			return N;
		}
    	}
}


int getHash(int d, int numsSize)
{
	if (d < 0)
	{
		d = -d;
	}
	return d % numsSize;
}

struct hashInfo
{
	int d;
	int count;
	struct hashInfo *next;
};

struct hashInfo** g_maxQueue;
int g_maxQueueSize;

void push(struct hashInfo* p)
{
	int i = g_maxQueueSize++;
	while (i > 0)
	{
		int parent = (i - 1) / 2;
		if (g_maxQueue[parent]->count >= p->count)
		{
			break;
		}

		g_maxQueue[i] = g_maxQueue[parent];
		i = parent;
	}

	g_maxQueue[i] = p;
}


int pop(void)
{
	int ret = g_maxQueue[0]->d;
	struct hashInfo* temp = g_maxQueue[--g_maxQueueSize];

	int i = 0;
	while (2 * i + 1 < g_maxQueueSize)
	{
		int a = 2 * i + 1;
		int b = 2 * i +2;
		if (b < g_maxQueueSize && g_maxQueue[b]->count > g_maxQueue[a]->count)
		{
			a = b;
		}

		if (g_maxQueue[a]->count <= temp->count)
		{
			break;
		}

		g_maxQueue[i] = g_maxQueue[a];
		i = a;
	}

	g_maxQueue[i] = temp;

	return ret;
}



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {

	int* ret = (int*)malloc(sizeof(int) * k);
	
	if(numsSize == 1)
	{
		*returnSize = 1;
		*ret = *nums;
		return ret;
	}


	int nextPrime = getNextPrime(numsSize);

	struct hashInfo** pHashInfo = (struct hashInfo**)malloc(sizeof(struct hashInfo *) * nextPrime);

	struct hashInfo *pInfoPool = (struct hashInfo*)malloc(sizeof(struct hashInfo) *numsSize);
	int nIndex = 0;
	int i;
	for (i = 0; i < nextPrime; ++i)
	{
		pHashInfo[i] = 0;
	}

	for (i = 0; i < numsSize; ++i)
	{
		int hash = getHash(nums[i], nextPrime);
	
		struct hashInfo *iter = pHashInfo[hash];
		while(iter)
		{
			if(iter->d == nums[i])
			{
				++iter->count;
				break;
			}

			iter = iter->next;
		}			

		if(!iter)
		{
			struct hashInfo *p = pInfoPool + nIndex++;
			p->d = nums[i];
			p->count = 1;

			p->next = pHashInfo[hash];
			pHashInfo[hash] = p;
		}
		
	}


	g_maxQueue = (struct hashInfo **)malloc(sizeof(struct hashInfo*) * numsSize);

	g_maxQueueSize = 0;

	for (i = 0; i < nextPrime; ++i)
	{
		struct hashInfo *iter = pHashInfo[i];
		while(iter)
		{
			push(iter);
			iter = iter->next;
		}
	}


	int n = 0;
	while (n < k)
	{
		ret[n] = pop();
		++n;
	}

	free(pInfoPool);
	free(pHashInfo);
	free(g_maxQueue);

	*returnSize = k;
	return ret;
}


