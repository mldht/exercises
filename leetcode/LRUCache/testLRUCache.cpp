#include  "lRUCache3.cpp"

int main(void)
{
/*	LRUCache *lc = new LRUCache(2);
	lc->put(2,1);
	lc->put(2,2);
	int ret = lc->get(2);
	lc->put(1,1);
	lc->put(4,1);
	ret = lc->get(2);*/

	LRUCache *lc = new LRUCache(2);
	lc->put(1,1);
	lc->put(2,2);
	int ret = lc->get(1);
	lc->put(3,3);
	lc->get(2);
	lc->put(4,4);
	lc->get(1);
	lc->get(3);
	lc->get(4);

/*	LRUCache *lc = new LRUCache(2);
	int ret = lc->get(2);
	lc->put(2,6);
	lc->get(1);
	lc->put(1,5);
	lc->put(1,2);
	lc->get(1);
	lc->get(2);
*/	return 0;
}
