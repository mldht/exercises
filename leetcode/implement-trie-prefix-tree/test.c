#include <stdio.h>
#include <stdlib.h>

#ifndef  __cplusplus
typedef int  bool;
#define true 1
#define false 0
#endif


typedef struct  tagTrie {
	 struct tagTrie * next[26];
	int is_word;
	int freq;  
	char c;
} Trie;

/** Initialize your data structure here. */

 Trie* trieCreate() {
	Trie * obj = malloc(sizeof(Trie));
	obj->c = '\0';
	obj->is_word = 0;
	
	int i;
	for(i = 0; i < 26; ++i)
	{
		obj->next[i] = NULL;
	}

	return obj;
}

Trie * alloc_Trie( int c )
{
	Trie *obj = malloc(sizeof(Trie));
	obj->c = c;
	obj->is_word = 0;
	obj->freq = 0;

	int i;
	for(i = 0; i < 26; ++i)
	{
		obj->next[i] = NULL;
	}
	return obj;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char * word) {
  
	while( *word != '\0')
	{
		int idx = *word - 'a';
		if(obj->next[idx] == NULL)
		{
			obj->next[idx] = alloc_Trie(*word);
		}

		if( *(word+1) == '\0')
		{
			obj->next[idx]->is_word = 1;
			++obj->next[idx]->freq;
		}
		++word;
		obj = obj->next[idx];
	}
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word) {

	while( *word != '\0')
	{
		int idx = *word - 'a';
		if(obj->next[idx] == NULL)
		{
			return false;
		}

		++word;
		obj = obj->next[idx];
	}  

	return obj->is_word == 1;	
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix) {
  
	while( *prefix != '\0')
	{
		int idx = *prefix - 'a';	
		if(obj->next[idx] == NULL)
		{
			return false;
		}

		obj = obj->next[idx];
		++prefix;
	} 

	return true;
}

void trieFree(Trie* obj) {

	int i;
	for(i = 0; i < 26; ++i)
	{
		if( obj->next[i])
		{
			trieFree(obj->next[i]);
		}
	}

	free(obj);   
}

//////////////////////////////////////////////////////////////////////

#define MAX_WORD_LEN	15

int mystrcpy(char *source, char *dest)
{
	int i = 0;
	while( i < MAX_WORD_LEN -1 && *source != '\0')
	{
		dest[i++] = *(source++);
	}
	dest[i] = '\0';

	return i;
}

int mystrcmp( char *str1, char *str2)
{
	while(*str1 != '\0' && *str2 != '\0')
	{
		if( *str1 > *str2)
		{
			return 1;
		}
		else if( *str1 < *str2)
		{
			return -1;
		}
		else
		{
			++str1;
			++str2;
		}
	}

	return *str1 - *str2;
}

struct word
{
	char *word;
	int freq;
};

struct word g_queue[100];
int size;

void pushWords(char *word, int freq)
{
	int idx = size -1;
	while(idx >= 0)
	{
		if(g_queue[idx].freq < freq ||g_queue[idx].freq == freq && mystrcmp(g_queue[idx].word, word) < 0)
		{
			g_queue[idx+1] = g_queue[idx];
			--idx;
		}
		else
		{
			break;
		}
	}	

	g_queue[idx+1].word = word;
	g_queue[idx+1].freq = freq;
	++size;
}

void FindMatchedWords(Trie *obj, char *prefix)
{
	int i;
	for(i = 0; i < 26; ++i)
	{
		if(obj->next[i] != NULL)
		{
			char tmp[MAX_WORD_LEN+1];
			int len = mystrcpy(prefix, tmp);
			tmp[len] = obj->next[i]->c;
			tmp[len+1] = '\0';	
			FindMatchedWords(obj->next[i], tmp);
		}
	}

	if(obj->is_word)
	{
		char *tmp = malloc(MAX_WORD_LEN);
		mystrcpy(prefix, tmp);
		pushWords(tmp, obj->freq);
	}
}


int trieMatchPrefixWords(Trie * obj, char *prefix, char words[5][MAX_WORD_LEN+1])
{
	char *str = prefix;
	while(*str != '\0')
	{
		int idx = *str - 'a';
		if(obj->next[idx] == NULL)
		{
			return 0;
		}

		++str;
		obj = obj->next[idx];
	}

	FindMatchedWords(obj, prefix);

	int count = size > 5 ? 5: size;
	int i;	
	for(i = 0; i < count; ++i)
	{
		mystrcpy(g_queue[i].word, words[i]);
	}

	return count;
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/
