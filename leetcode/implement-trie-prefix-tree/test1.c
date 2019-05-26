#include "test.c"

int main(void)
{
	Trie * obj = trieCreate();
	trieInsert(obj, "apple");
	bool ret = trieSearch(obj, "apple");
	ret = trieSearch(obj, "app");
	ret = trieStartsWith(obj, "app");
	trieInsert(obj, "app");
	trieSearch(obj, "app");
	
	trieFree(obj);
	return 0;	
}
