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

struct HashNode
{
	int key;
	struct Record *value;
	struct HashNode *next;	
public:
	HashNode(int key, struct Record* value);
};

HashNode::HashNode(int key, struct Record * value)
{
	this->key = key;
	this->value = value;
	this->next = NULL;
}

class HashMap
{
public:
	HashMap(int capacity );
	void Insert(int key, struct Record *value);
	void Delete(int key);
	struct HashNode * Find(int key);
private:
	struct HashNode **map;
	int capacity;
};

HashMap::HashMap(int capacity)
{
	map = new struct HashNode *[capacity];
	int i;
	for(i = 0; i < capacity; ++i)
	{
		map[i] = NULL;
	}

	this->capacity = capacity;	
}

struct HashNode * HashMap::Find(int key)
{
	int index = key % capacity;
	struct HashNode *iter = map[index];
	while(iter && iter->key != key)
	{
		iter = iter->next;
	}

	return iter;
}

void HashMap::Insert(int key, struct Record *value)
{
	struct HashNode *tmp = new HashNode(key, value);
	int index = key%capacity;
	if(map[index] == NULL)
	{
		map[index] = tmp;
	}
	else
	{
		struct HashNode * iter = map[index];
		while(iter->next)
		{
			iter = iter->next;
		}
	
		iter->next = tmp;
	}
}

void HashMap::Delete(int key)
{
	int index = key %capacity;
	struct HashNode *iter = map[index];
	if( iter && iter->key == key)
	{
		map[index] = map[index]->next;
		return;
	}
	while(iter->next && iter->next->key != key)
	{
		iter = iter->next;
	}

	if(iter->next)
	{
		iter->next = iter->next->next;
	}
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
//	std::unordered_map<int, struct Record *> hash_map;
	HashMap hash_map;
	MemoryPool *memPool;
};

Queue::Queue(int capacity):
hash_map(capacity)
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
	auto iter = hash_map.Find(key);
	if(iter != NULL)
	{
		struct Record * tmp = iter->value;
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
		hash_map.Delete(tmp->key);
		m_Unlink(tmp);
		tmp->key = key;
		tmp->value = value;
	}

	m_MoveToHead(tmp);
	//hash_map[key] = tmp;
	hash_map.Insert(key, tmp);
}

int Queue::Get(int key)
{
	auto iter = hash_map.Find(key);
	if( iter != NULL)
	{
		struct Record *item = iter->value;
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
