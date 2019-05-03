
#define R	100000
#define N	5000
#define D	5000

int g_N;
int g_R;

struct edge
{
	int to;
	int cost;
};

struct edge_list
{
	struct edge e;
	struct edge_list *next;
};

struct edge_list * g_edge_list[N];

struct vertice
{
	int id;
	int key;	
};

struct vertice g_vertice[R + 1];


void init(void)
{
	int i;
	for(i = 1; i < g_R; ++i)
	{
		g_vertice[i].id = i;
		g_vertice[i].key = D;
	}

	g_vertice[1].key = 0;
}
