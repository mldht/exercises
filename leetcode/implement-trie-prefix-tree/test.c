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



/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);
 
 * bool param_2 = trieSearch(obj, word);
 
 * bool param_3 = trieStartsWith(obj, prefix);
 
 * trieFree(obj);
*/
