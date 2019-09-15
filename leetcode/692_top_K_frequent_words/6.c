#include <stdlib.h>

struct wordInfo
{
	int freq;
	char * word;
	struct wordInfo *next;
};

int hashing(char *word, int nHashTblSize)
{
	unsigned long long hash = 0;
	while(*word != '\0')
	{
		hash = hash * 131 + *word;
		++word; 
	}

	return hash % nHashTblSize;
}

int my_strlen(char *str)
{
	int i = 0;
	while( str[i++] != '\0');
	
	return i-1;
}

void my_strcpy(char *src, char *dst)
{
	while( (*dst++ = *src++) != '\0');
}

int my_strcmp(char *str1, char *str2)
{
	while( *str1 == *str2 && *str1 != '\0')
	{
		++str1;
		++str2;
	}

	return *str1 - *str2;
}

struct wordInfo ** maxQueue;
int maxQueueSize;

void push(struct wordInfo *p)
{
	int i = maxQueueSize++;
	while(i > 0)
	{
		int parent = (i-1) / 2;

		if( maxQueue[parent]->freq > p->freq || 
		maxQueue[parent]->freq == p->freq && my_strcmp(maxQueue[parent]->word, p->word) <= 0)
		{
			break;
		}	

		maxQueue[i] = maxQueue[parent];
		i = parent;
	}


	maxQueue[i] = p;
}

void init(void)
{
	maxQueueSize = 0;
}

struct wordInfo *pop(void)
{
	struct wordInfo *ret = maxQueue[0];
	struct wordInfo *tmp = maxQueue[--maxQueueSize];

	int i = 0;
	while( 2 * i + 1 < maxQueueSize)
	{
		int a = 2 * i + 1;
		int b = 2 * i + 2;

		if(b < maxQueueSize && (  maxQueue[b]->freq > maxQueue[a]->freq ||
					maxQueue[b]->freq == maxQueue[a]->freq && my_strcmp(maxQueue[b]->word, maxQueue[a]->word) < 0 ) )
		{
			a = b;
		}

		if( maxQueue[a]->freq < tmp->freq ||
		( maxQueue[a]->freq == tmp->freq && my_strcmp(maxQueue[a]->word, tmp->word) >= 0) )
		{
			break;
		}
	
		maxQueue[i] = maxQueue[a];
		i = a;
	}

	maxQueue[i] = tmp;
	
	return ret;	
}


int getNextPrime(int n)
{
	if(n%2 == 0)
	{
		++n;
	}

	for(;; n+= 2)
	{
		char found = 1;
		int i;
		for(i = 3; i * i <= n; ++i)
		{
			if(n%i == 0)
			{
				found = 0;
				break;
			}
		}

		if(found == 1)
		{
			return n;
		}
	}
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize){

	char ** ret = (char **)malloc(sizeof(char *) * wordsSize);
	if(wordsSize == 1)
	{
		int len = my_strlen(*words);
		char * str = (char *)malloc((len+1) * sizeof(char));
		my_strcpy(*words, str);
		*ret = str;
		*returnSize = 1;
		return ret;
	}

	init();
	struct wordInfo *pWordPool = (struct wordInfo *)malloc(sizeof(struct wordInfo) * wordsSize);
	int nPoolIdx = 0;

	int nHashTblSize = getNextPrime(wordsSize);
	struct wordInfo **pHash = (struct wordInfo **)malloc(sizeof(struct wordInfo *) * nHashTblSize); 

	maxQueue = (struct wordInfo **)malloc(sizeof(struct wordInfo *) * wordsSize);
	int i;
	for(i = 0; i < nHashTblSize; ++i)
	{
		pHash[i] = 0;
	}

	for(i = 0; i < wordsSize; ++i)
	{
		int hash = hashing(words[i], nHashTblSize);
		struct wordInfo *iter = pHash[hash];
		while(iter)
		{
			if( my_strcmp(iter->word, words[i]) == 0)
			{
				++iter->freq;
				break;
			}

			iter = iter->next;
		} 

		if(!iter)
		{
			struct wordInfo *p = pWordPool + nPoolIdx++;
			p->word = words[i];
			p->freq = 1;
			p->next = pHash[hash];
			pHash[hash] = p;	
		}	
	}


	for(i = 0; i < nHashTblSize; ++i)
	{
		struct wordInfo *iter = pHash[i];
		while(iter)
		{
			push(iter);
			iter = iter->next;
		}
	}
	
	i = 0;
	while(i < k)
	{
		struct wordInfo *p = pop();
		int len = my_strlen(p->word);
		ret[i] = (char *)malloc(len + 1);
		my_strcpy(p->word, ret[i]);
		++i;
	}

	free(pHash);
	free(pWordPool);
	free(maxQueue);
	*returnSize = k;
	return ret;
}

int main(void)
{

	char *words [] = {"i", "love", "leetcode", "i", "love", "coding"};
	int returnSize = 0;
	char ** ret = topKFrequent(words, sizeof(words)/sizeof(words[0]), 2, &returnSize);
	return 0;
}
