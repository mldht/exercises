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
	void Put(int key, int value);
	int Get(int key);
private:
	void m_Unlink(struct Record *item);
	void m_MoveToHead(struct Record *item);
private:

	struct Record * head;
	struct Record *tail;
	int capacity;
	int size;
	std::unordered_map<int, struct Record *> hash_map;
	MemoryPool *memPool;
};

Queue::Queue(int capacity)
{
	//head = tail = NULL;
	this->capacity = capacity;
	size = 0;
	memPool = new MemoryPool(capacity+2);
	head = memPool->Get(0, 0);
	tail = memPool->Get(0, 0);
	head->next = tail;
	tail->prev = head;
}

void Queue::m_Unlink( struct Record *item)
{
	struct Record *prev = item->prev;
	struct Record *next = item->next;
	prev->next = next;
	next->prev = prev;
	item->next = item->prev = NULL;
}

void Queue::m_MoveToHead(struct Record *item)
{
	item->next = head->next;
	item->prev = head;
	head->next->prev = item;
	head->next = item;	
}

void Queue::Put(int key, int value)
{
	auto iter = hash_map.find(key);
	if(iter != hash_map.end())
	{
		struct Record * tmp = iter->second;
		tmp->value = value;
		m_Unlink(tmp);
		m_MoveToHead(tmp);
		return;	
	}

	struct Record *tmp = NULL;
	if( memPool->FreeMemAvail())
	{
		tmp = memPool->Get( key, value);
	}
	else
	{
		tmp = tail->prev;
		m_Unlink(tmp);
		tmp->key = key;
		tmp->value = value;
	}

	m_MoveToHead(tmp);
	hash_map[key] = tmp;
}

int Queue::Get(int key)
{
	auto iter = hash_map.find(key);
	if( iter != hash_map.end())
	{
		struct Record *item = iter->second;
		m_Unlink(item);
		m_MoveToHead(item);
		return item->value;
	}
	return -1;
}

class LRUCache {
public:
    LRUCache(int capacity) {
        que = new Queue(capacity);
    }
    
    int get(int key) {
       return que->Get(key);
    }
    
    void put(int key, int value) {
        que->Put(key, value);
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
