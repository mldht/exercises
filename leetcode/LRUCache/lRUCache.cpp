#include <unordered_map>

struct Record
{
	int key;
	int value;
	struct Record *prev;
	struct Record *next;
};


class MemoryPool
{
public:
	MemoryPool(int capacity);
	struct Record *Get(int key, int value);
	bool FreeMemAvail(void) { return used < capacity; }
private:
	struct Record * recordPool;
	int capacity;
	int used;
};

MemoryPool::MemoryPool(int capacity)
{
	this->capacity = capacity;
	used = 0;
	recordPool = new Record[capacity * sizeof(struct Record)];
}

struct Record * MemoryPool::Get(int key, int value)
{
	if(used < capacity)
	{
		struct Record * rec = &recordPool[used++];
		rec->key = key;
		rec->value = value;
		rec->prev = rec->next = NULL;
		return rec;
	}

	return NULL;
}

class Queue
{
public:
	Queue(int capacity);
	void put(int key, int value);
	int get(int key);
private:
	MemoryPool *memPool;
	struct Record * head;
	struct Record * tail;
	int size;
	struct Record * queue;
	
	std::unordered_map<int, struct Record *> hash_map;	
};


Queue::Queue(int capacity)
{
	memPool = new MemoryPool(capacity);
	size = 0;
	head = tail = NULL;
	queue = NULL;
}

void Queue::put(int key, int value)
{
	if(queue == NULL)
	{
		queue = memPool->Get(key, value);
		head = tail = queue;
		++size;
		hash_map.insert(std::make_pair(key, queue));
	}
	else
	{
		std::unordered_map<int, struct Record *>::const_iterator ret = hash_map.find(key);
		
		if(ret == hash_map.end() && memPool->FreeMemAvail() )
		{
			struct Record * rec = memPool->Get(key, value);
			rec->next = head;
			head->prev = rec;
			head = rec;	
			hash_map.erase(key);
			hash_map.insert(std::make_pair(key, rec));
			++size;
		}
		else
		{
			struct Record *target = NULL;
			if(ret == hash_map.end())
			{
				target = tail;
			}
			else
			{
				target = ret->second;
			}

			
			hash_map.erase(target->key);
			target->key = key;
			target->value = value;
			if(target != head)
			{
				
				if(target->prev)
				{
					target->prev->next = target->next;
				}
				if(target->next)
				{
					target->next->prev = target->prev;
				}
			
				target->next = head;
				head->prev = target;
				head = target;
				if(tail == target)
				{
					tail = tail->prev;
					if(tail)
					{
						tail->next = NULL;
					}
					else
					{
						tail = head;	
					}
				}
			}
			hash_map.insert(std::make_pair(key, head));
		}
	}
}


int  Queue::get(int key)
{
	std::unordered_map<int, struct Record *>::const_iterator ret = hash_map.find(key);
	if(ret == hash_map.end())
	{
		return -1;
	}

	struct Record * rec = ret->second;
	if( size  == 1 || rec == head)
	{
		return rec->value;
	}

	if(rec == tail)
	{
		tail = rec->prev;
	}

	if(rec->prev)
	{
		rec->prev->next = rec->next;
	}

	if(rec->next)
	{
		rec->next->prev = rec->prev;
	}

	rec->next = rec->prev = NULL;

	rec->next = head;
	head->prev = rec;
	head = rec;
	tail->next = NULL;

	return rec->value;
}


class LRUCache {
public:
    LRUCache(int capacity) {
        que = new Queue(capacity);
    }
    
    int get(int key) {
       return que->get(key);
    }
    
    void put(int key, int value) {
        que->put(key, value);
    }

private:
	Queue * que;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
