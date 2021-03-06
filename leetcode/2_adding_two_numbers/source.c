#include <stdio.h> 
#include <stdlib.h>

struct ListNode {
      int val;
      struct ListNode *next;
  };


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);

int main(void)
{
	struct ListNode *l1 = 0;
	struct ListNode *l2 = 0;

	struct ListNode *iter = 0;
	iter = (struct ListNode*)malloc(sizeof(struct ListNode));
	iter->val = 2;
	iter->next = 0;
	l1 = iter;
	
	iter->next = (struct ListNode*)malloc(sizeof(struct ListNode));
	iter->next->val = 4;
	iter = iter->next;

	iter->next = (struct ListNode*)malloc(sizeof(struct ListNode));
	iter->next->val = 3;
	iter->next->next = 0;


	iter = 0;

	iter = (struct ListNode*)malloc(sizeof(struct ListNode));
	iter->val = 5;
	iter->next = 0;
	l2 = iter;
	
	iter->next = (struct ListNode*)malloc(sizeof(struct ListNode));
	iter->next->val = 6;
	iter = iter->next;

	iter->next = (struct ListNode*)malloc(sizeof(struct ListNode));
	iter->next ->val = 4;
	iter->next->next = 0;

	struct ListNode *ret = addTwoNumbers(l1,l2);

	return 0;

}
 
struct ListNode *g_pool = 0;
int g_size = 0;
int g_index = 0;
void initMem(int size)
{
	g_pool = (struct ListNode *)malloc(sizeof(struct ListNode) * size);
	g_size = size;
	g_index = 0;
}

struct ListNode *getNode(int val)
{
	if( g_index >= g_size)
	{
		g_pool = (struct ListNode *)realloc(g_pool, 2 * g_size);
		g_size *= 2;
	}
	struct ListNode *ret = g_pool + g_index++;
	ret->val = val;
	ret->next = 0;
	return ret;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){

	if(!l1)
	{
		return l2;
	}
	if(!l2)
	{
		return l1;
	}
	int adding = 0;
	initMem(1024);
	struct ListNode *head = getNode(-1);
	struct ListNode *iter = head;
	while(l1 && l2)
	{
		int val = 0;
		val += l1->val;
		val += l2->val;
		val += adding;

		adding = val/10;
		val = val %10;		

		struct ListNode *p = getNode(val);
	
		iter->next = p;
		iter = p;
		l1 = l1->next;
		l2 = l2->next;
	}

	while(l1)
	{
		int val = 0;
		val += l1->val;	
		val += adding;

		adding = val/10;
		val = val %10;	

		struct ListNode *p = getNode(val);
	
		iter->next = p;
		iter = p;
		l1 = l1->next;			
	}

	while(l2)
	{
		int val = 0;
		val += l2->val;	
		val += adding;

		adding = val/10;
		val = val %10;	

		struct ListNode *p = getNode(val);
	
		iter->next = p;
		iter = p;
		l2 = l2->next;			
	}	

	if(adding)
	{
		struct ListNode *p = getNode(1);
		iter->next = p;
		adding = 0;
	}
	return head->next;
}

