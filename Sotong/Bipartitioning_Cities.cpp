#include <stdio.h>

#define MAX_N 1005
int N, E;
const int T = 2;
bool marked[MAX_N];
bool color[MAX_N];
bool isTwoColorable;

int **adj;
int adjlen[MAX_N];

void allocmem()
{
	adj = new int *[MAX_N];
	for (int i = 0; i < MAX_N;i++)
	{
		adj[i] = new int[MAX_N];
	}
}

void init()
{
	for (int i = 0; i < MAX_N;i++)
	{
		adjlen[i] = 0;
		for (int j = 0; j < MAX_N;j++)
		{
			adj[i][j] = 0;
		}

		marked[i] = false;
		color[i] = false;
	}
	isTwoColorable = true;
}

void dfs(int v)
{
	marked[v] = true;
	for (int w = 0; w < adjlen[v];w++)
	{
		if (!marked[w])
		{
			color[w] = !color[v];
			dfs(w);
		}
		else if (color[w] == color[v])
		{
			isTwoColorable = false;
		}
	}
}

void solve()
{
	for (int v = 0; v < N;v++)
	{
		if (!marked[v])
		{
			dfs(v);
		}
	}
}

int main()
{
	freopen("Bipartitioning_Cities.txt", "r", stdin);
	for (int t = 1; t <= T;t++)
	{
		scanf("%d%d\n", &N, &E);
		for (int i = 0; i < E;i++)
		{
			int v1, v2;
			scanf("%d%d", &v1, &v2);
			adj[v1][adjlen[v1]++] = v2;
			adj[v2][adjlen[v2]++] = v1;
		}
		init();
		solve();
		if (isTwoColorable==false)
		{
			printf("#%d -1\n",t);
		}
		else
		{
			printf("#%d ", t);
			int numColored = 0;
			for (int v = 1; v <= N; v++)
			{
				if (color[v] == true)
				{
					numColored++;
				}
			}
			for (int v = 1,num=0; v <= N;v++)
			{
				if (color[v]==true)
				{
					num++;
					printf("%d%s", v, num == numColored ? "\n" : " ");
				}
			}
		}
	}
	return 0;
}