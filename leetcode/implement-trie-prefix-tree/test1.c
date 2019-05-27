#include "test.c"

int main(void)
{
	Trie * obj = trieCreate();
	trieInsert(obj, "sin");
//	bool ret = trieSearch(obj, "apple");
//	ret = trieSearch(obj, "app");
//	ret = trieStartsWith(obj, "app");
	trieInsert(obj, "sin");
//	trieSearch(obj, "app");

	trieInsert(obj, "single");
	trieInsert(obj, "single");
	trieInsert(obj, "single");
	trieInsert(obj, "singer");
	trieInsert(obj, "singer");
	trieInsert(obj, "singer");
	trieInsert(obj, "sincere");
	trieInsert(obj, "since");
	trieInsert(obj, "sinful");
	trieInsert(obj, "sinful");
	trieInsert(obj, "singly");

	char words[5][16];
	trieMatchPrefixWords( obj, "sin", words);	
	trieFree(obj);
	return 0;	
}
