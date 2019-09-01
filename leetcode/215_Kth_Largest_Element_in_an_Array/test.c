#include <stdlib.h>

int * g_queue;
int g_size;

void init( int k)
{
	g_queue = malloc(k * sizeof(int));
	g_size = 0;
}

void push(int d)
{
	int i = g_size++;
	while( i > 0)
	{
		int p = (i-1)/2;
		if(g_queue[p] <= d)
		{
			break;
		}

		g_queue[i] = g_queue[p];
		i = p;
	}

	g_queue[i] = d;
}


int pop(void)
{
	int ret = g_queue[0];
	int check = g_queue[--g_size];
	int i = 0;
	while( 2 * i + 1 < g_size)
	{
		int a = 2 * i + 1;
		int b = 2 * i + 2;
		
		if(b < g_size && g_queue[b] < g_queue[a])
		{
			a = b;
		}

	
		if(g_queue[a] >= check)
		{
			break;
		}

		g_queue[i] = g_queue[a];
		i = a;
	}

	g_queue[i] = check;
}

int findKthLargest(int* nums, int numsSize, int k){
	
	init(k);

	int i;
	for(i = 0; i < k; ++i)
	{
		push(nums[i]);
	}

	for(i = k; i < numsSize; ++i)
	{
		if(g_queue[0] < nums[i])
		{
			pop();
			push(nums[i]);			
		}
	}

	return g_queue[0];

}

int main(void)
{
	int nums[] = {3,2,1,5,6,4};
	int ret = findKthLargest(nums, 6, 2);

	return 0;
}
